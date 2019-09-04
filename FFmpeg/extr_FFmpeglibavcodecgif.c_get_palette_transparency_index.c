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
typedef  int uint32_t ;

/* Variables and functions */
 unsigned int AVPALETTE_COUNT ; 

__attribute__((used)) static int get_palette_transparency_index(const uint32_t *palette)
{
    int transparent_color_index = -1;
    unsigned i, smallest_alpha = 0xff;

    if (!palette)
        return -1;

    for (i = 0; i < AVPALETTE_COUNT; i++) {
        const uint32_t v = palette[i];
        if (v >> 24 < smallest_alpha) {
            smallest_alpha = v >> 24;
            transparent_color_index = i;
        }
    }
    return smallest_alpha < 128 ? transparent_color_index : -1;
}