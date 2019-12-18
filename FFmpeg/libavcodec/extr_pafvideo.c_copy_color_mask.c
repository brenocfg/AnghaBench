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

__attribute__((used)) static void copy_color_mask(uint8_t *dst, int width, uint8_t mask, uint8_t color)
{
    int i;

    for (i = 0; i < 4; i++) {
        if (mask & (1 << 7 - i))
            dst[i] = color;
        if (mask & (1 << 3 - i))
            dst[width + i] = color;
    }
}