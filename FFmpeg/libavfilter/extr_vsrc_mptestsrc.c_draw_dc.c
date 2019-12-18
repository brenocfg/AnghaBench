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

__attribute__((used)) static void draw_dc(uint8_t *dst, int dst_linesize, int color, int w, int h)
{
    int x, y;

    for (y = 0; y < h; y++)
        for (x = 0; x < w; x++)
            dst[x + y*dst_linesize] = color;
}