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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */

__attribute__((used)) static void pseudocolor_filter(int max, int width, int height,
                               const uint8_t *index,
                               const uint8_t *src,
                               uint8_t *dst,
                               ptrdiff_t ilinesize,
                               ptrdiff_t slinesize,
                               ptrdiff_t dlinesize,
                               float *lut)
{
    int x, y;

    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            int v = lut[index[x]];

            if (v >= 0 && v <= max) {
                dst[x] = v;
            } else {
                dst[x] = src[x];
            }
        }
        index += ilinesize;
        src += slinesize;
        dst += dlinesize;
    }
}