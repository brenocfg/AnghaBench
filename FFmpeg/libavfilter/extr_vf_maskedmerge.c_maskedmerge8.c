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

__attribute__((used)) static void maskedmerge8(const uint8_t *bsrc, const uint8_t *osrc,
                         const uint8_t *msrc, uint8_t *dst,
                         ptrdiff_t blinesize, ptrdiff_t olinesize,
                         ptrdiff_t mlinesize, ptrdiff_t dlinesize,
                         int w, int h,
                         int half, int shift)
{
    int x, y;

    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            dst[x] = bsrc[x] + ((msrc[x] * (osrc[x] - bsrc[x]) + 128) >> 8);
        }

        dst  += dlinesize;
        bsrc += blinesize;
        osrc += olinesize;
        msrc += mlinesize;
    }
}