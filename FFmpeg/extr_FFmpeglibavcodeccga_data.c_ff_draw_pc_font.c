#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;

/* Variables and functions */

void ff_draw_pc_font(uint8_t *dst, int linesize, const uint8_t *font, int font_height, int ch, int fg, int bg)
{
    int char_y, mask;
    for (char_y = 0; char_y < font_height; char_y++) {
        for (mask = 0x80; mask; mask >>= 1) {
            *dst++ = font[ch * font_height + char_y] & mask ? fg : bg;
        }
        dst += linesize - 8;
    }
}