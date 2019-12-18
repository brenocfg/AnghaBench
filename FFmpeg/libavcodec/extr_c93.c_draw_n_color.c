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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static inline void draw_n_color(uint8_t *out, int stride, int width,
         int height, int bpp, uint8_t cols[4], uint8_t grps[4], uint32_t col)
{
    int x, y;
    for (y = 0; y < height; y++) {
        if (grps)
            cols[0] = grps[3 * (y >> 1)];
        for (x = 0; x < width; x++) {
            if (grps)
                cols[1]= grps[(x >> 1) + 1];
            out[x + y*stride] = cols[col & ((1 << bpp) - 1)];
            col >>= bpp;
        }
    }
}