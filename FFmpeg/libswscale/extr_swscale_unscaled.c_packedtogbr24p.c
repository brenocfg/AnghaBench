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

/* Variables and functions */

__attribute__((used)) static void packedtogbr24p(const uint8_t *src, int srcStride,
                           uint8_t *dst[], int dstStride[], int srcSliceH,
                           int alpha_first, int inc_size, int width)
{
    uint8_t *dest[3];
    int x, h;

    dest[0] = dst[0];
    dest[1] = dst[1];
    dest[2] = dst[2];

    if (alpha_first)
        src++;

    for (h = 0; h < srcSliceH; h++) {
        for (x = 0; x < width; x++) {
            dest[0][x] = src[0];
            dest[1][x] = src[1];
            dest[2][x] = src[2];

            src += inc_size;
        }
        src     += srcStride - width * inc_size;
        dest[0] += dstStride[0];
        dest[1] += dstStride[1];
        dest[2] += dstStride[2];
    }
}