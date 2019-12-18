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
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */

__attribute__((used)) static void premultiply8yuv(const uint8_t *msrc, const uint8_t *asrc,
                            uint8_t *dst,
                            ptrdiff_t mlinesize, ptrdiff_t alinesize,
                            ptrdiff_t dlinesize,
                            int w, int h,
                            int half, int shift, int offset)
{
    int x, y;

    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            dst[x] = ((((msrc[x] - 128) * (((asrc[x] >> 1) & 1) + asrc[x]))) >> 8) + 128;
        }

        dst  += dlinesize;
        msrc += mlinesize;
        asrc += alinesize;
    }
}