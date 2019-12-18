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
 int FFMIN (int const,int) ; 

__attribute__((used)) static void unpremultiply8(const uint8_t *msrc, const uint8_t *asrc,
                           uint8_t *dst,
                           ptrdiff_t mlinesize, ptrdiff_t alinesize,
                           ptrdiff_t dlinesize,
                           int w, int h,
                           int half, int max, int offset)
{
    int x, y;

    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            if (asrc[x] > 0 && asrc[x] < 255)
                dst[x] = FFMIN(msrc[x] * 255 / asrc[x], 255);
            else
                dst[x] = msrc[x];
        }

        dst  += dlinesize;
        msrc += mlinesize;
        asrc += alinesize;
    }
}