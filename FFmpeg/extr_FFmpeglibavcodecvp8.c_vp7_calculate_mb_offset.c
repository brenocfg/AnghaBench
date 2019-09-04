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

/* Variables and functions */

__attribute__((used)) static int vp7_calculate_mb_offset(int mb_x, int mb_y, int mb_width,
                                   int xoffset, int yoffset, int boundary,
                                   int *edge_x, int *edge_y)
{
    int vwidth = mb_width + 1;
    int new = (mb_y + yoffset) * vwidth + mb_x + xoffset;
    if (new < boundary || new % vwidth == vwidth - 1)
        return 0;
    *edge_y = new / vwidth;
    *edge_x = new % vwidth;
    return 1;
}