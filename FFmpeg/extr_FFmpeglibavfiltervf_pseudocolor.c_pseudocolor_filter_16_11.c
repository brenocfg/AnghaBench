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
typedef  size_t uint16_t ;
typedef  int ptrdiff_t ;

/* Variables and functions */

__attribute__((used)) static void pseudocolor_filter_16_11(int max, int width, int height,
                                     const uint8_t *iindex,
                                     const uint8_t *ssrc,
                                     uint8_t *ddst,
                                     ptrdiff_t ilinesize,
                                     ptrdiff_t slinesize,
                                     ptrdiff_t dlinesize,
                                     float *lut)
{
    const uint16_t *index = (const uint16_t *)iindex;
    const uint16_t *src = (const uint16_t *)ssrc;
    uint16_t *dst = (uint16_t *)ddst;
    int x, y;

    ilinesize /= 2;
    dlinesize /= 2;
    slinesize /= 2;

    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            int v = lut[index[(y << 1) * ilinesize + (x << 1)]];

            if (v >= 0 && v <= max) {
                dst[x] = v;
            } else {
                dst[x] = src[x];
            }
        }
        src += slinesize;
        dst += dlinesize;
    }
}