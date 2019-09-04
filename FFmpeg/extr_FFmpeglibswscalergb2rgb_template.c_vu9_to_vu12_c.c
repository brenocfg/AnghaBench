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

__attribute__((used)) static inline void vu9_to_vu12_c(const uint8_t *src1, const uint8_t *src2,
                                 uint8_t *dst1, uint8_t *dst2,
                                 int width, int height,
                                 int srcStride1, int srcStride2,
                                 int dstStride1, int dstStride2)
{
    int x, y;
    int w = width  / 2;
    int h = height / 2;

    for (y = 0; y < h; y++) {
        const uint8_t *s1 = src1 + srcStride1 * (y >> 1);
        uint8_t *d        = dst1 + dstStride1 *  y;
        for (x = 0; x < w; x++)
            d[2 * x] = d[2 * x + 1] = s1[x];
    }
    for (y = 0; y < h; y++) {
        const uint8_t *s2 = src2 + srcStride2 * (y >> 1);
        uint8_t *d        = dst2 + dstStride2 *  y;
        for (x = 0; x < w; x++)
            d[2 * x] = d[2 * x + 1] = s2[x];
    }
}