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

__attribute__((used)) static inline void yvu9_to_yuy2_c(const uint8_t *src1, const uint8_t *src2,
                                  const uint8_t *src3, uint8_t *dst,
                                  int width, int height,
                                  int srcStride1, int srcStride2,
                                  int srcStride3, int dstStride)
{
    int x, y;
    int w = width / 2;
    int h = height;

    for (y = 0; y < h; y++) {
        const uint8_t *yp = src1 + srcStride1 *  y;
        const uint8_t *up = src2 + srcStride2 * (y >> 2);
        const uint8_t *vp = src3 + srcStride3 * (y >> 2);
        uint8_t *d        = dst  + dstStride  *  y;
        for (x = 0; x < w; x++) {
            const int x2 = x << 2;
            d[8 * x + 0] = yp[x2];
            d[8 * x + 1] = up[x];
            d[8 * x + 2] = yp[x2 + 1];
            d[8 * x + 3] = vp[x];
            d[8 * x + 4] = yp[x2 + 2];
            d[8 * x + 5] = up[x];
            d[8 * x + 6] = yp[x2 + 3];
            d[8 * x + 7] = vp[x];
        }
    }
}