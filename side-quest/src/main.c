#include <gb/gb.h>
#include <gb/cgb.h>
#include <gb/metasprites.h>
#include <stdint.h>
#include "common.h"
#include "link.h"
#include "moblin.h"
#include "graphics/palettes.h"

void main(void)
{
    SHOW_SPRITES;
    SPRITES_8x16;
    DISPLAY_ON;

    set_sprite_palette(0, palettes_PALETTE_COUNT, palettes_palettes);

    SetupLink();
    SetupMoblin();

    // Loop forever
    while(1) {

        // Save the current state of the joypad
        // it's important NOT to call the joypad function more than once
        joypadCurrent=joypad();

        UpdateTwoFrameCounter();

        uint8_t lastSprite=0;
        lastSprite += UpdateLink();
        lastSprite += UpdateMoblin(lastSprite);

        // Hide any extra sprites
        // Without this, extra "leftover" sprites may linger around.
        hide_sprites_range(lastSprite,40);

		// Done processing, yield CPU and wait for start of next frame
        wait_vbl_done();
    }
}
