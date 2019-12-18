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
typedef  int uint16_t ;
typedef  int ptrdiff_t ;

/* Variables and functions */
 int FFMIN (int const,int) ; 

__attribute__((used)) static void unpremultiply16(const uint8_t *mmsrc, const uint8_t *aasrc,
                            uint8_t *ddst,
                            ptrdiff_t mlinesize, ptrdiff_t alinesize,
                            ptrdiff_t dlinesize,
                            int w, int h,
                            int half, int max, int offset)
{
    const uint16_t *msrc = (const uint16_t *)mmsrc;
    const uint16_t *asrc = (const uint16_t *)aasrc;
    uint16_t *dst = (uint16_t *)ddst;
    int x, y;

    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            if (asrc[x] > 0 && asrc[x] < max)
                dst[x] = FFMIN(msrc[x] * (unsigned)max / asrc[x], max);
            else
                dst[x] = msrc[x];
        }

        dst  += dlinesize / 2;
        msrc += mlinesize / 2;
        asrc += alinesize / 2;
    }
}