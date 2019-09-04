#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int* index; } ;
typedef  TYPE_1__ Palette ;

/* Variables and functions */
 unsigned int pixel_color7_slow (TYPE_1__*,unsigned int) ; 

__attribute__((used)) static int update_palette_index(Palette * palette)
{
    int r, g, b;
    unsigned int bgr, c15, index;
    for (r = 4; r < 256; r += 8) {
        for (g = 4; g < 256; g += 8) {
            for (b = 4; b < 256; b += 8) {
                bgr = b | (g << 8) | (r << 16);
                c15 = (b >> 3) | ((g & 0xf8) << 2) | ((r & 0xf8) << 7);
                index = pixel_color7_slow(palette, bgr);

                palette->index[c15] = index;
            }
        }
    }
    return 0;
}