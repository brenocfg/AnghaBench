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

__attribute__((used)) static inline void planar2x_c(const uint8_t *src, uint8_t *dst, int srcWidth,
                              int srcHeight, int srcStride, int dstStride)
{
    int x, y;

    dst[0] = src[0];

    // first line
    for (x = 0; x < srcWidth - 1; x++) {
        dst[2 * x + 1] = (3 * src[x] + src[x + 1]) >> 2;
        dst[2 * x + 2] = (src[x] + 3 * src[x + 1]) >> 2;
    }
    dst[2 * srcWidth - 1] = src[srcWidth - 1];

    dst += dstStride;

    for (y = 1; y < srcHeight; y++) {
        const int mmxSize = 1;

        dst[0]         = (src[0] * 3 + src[srcStride]) >> 2;
        dst[dstStride] = (src[0] + 3 * src[srcStride]) >> 2;

        for (x = mmxSize - 1; x < srcWidth - 1; x++) {
            dst[2 * x + 1]             = (src[x + 0] * 3 + src[x + srcStride + 1]) >> 2;
            dst[2 * x + dstStride + 2] = (src[x + 0] + 3 * src[x + srcStride + 1]) >> 2;
            dst[2 * x + dstStride + 1] = (src[x + 1] + 3 * src[x + srcStride])     >> 2;
            dst[2 * x + 2]             = (src[x + 1] * 3 + src[x + srcStride])     >> 2;
        }
        dst[srcWidth * 2 - 1]             = (src[srcWidth - 1] * 3 + src[srcWidth - 1 + srcStride]) >> 2;
        dst[srcWidth * 2 - 1 + dstStride] = (src[srcWidth - 1] + 3 * src[srcWidth - 1 + srcStride]) >> 2;

        dst += dstStride * 2;
        src += srcStride;
    }

    // last line
    dst[0] = src[0];

    for (x = 0; x < srcWidth - 1; x++) {
        dst[2 * x + 1] = (src[x] * 3 + src[x + 1]) >> 2;
        dst[2 * x + 2] = (src[x] + 3 * src[x + 1]) >> 2;
    }
    dst[2 * srcWidth - 1] = src[srcWidth - 1];
}