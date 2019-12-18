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

__attribute__((used)) static void gbr24ptopacked32(const uint8_t *src[], int srcStride[],
                             uint8_t *dst, int dstStride, int srcSliceH,
                             int alpha_first, int width)
{
    int x, h, i;
    for (h = 0; h < srcSliceH; h++) {
        uint8_t *dest = dst + dstStride * h;

        if (alpha_first) {
            for (x = 0; x < width; x++) {
                *dest++ = 0xff;
                *dest++ = src[0][x];
                *dest++ = src[1][x];
                *dest++ = src[2][x];
            }
        } else {
            for (x = 0; x < width; x++) {
                *dest++ = src[0][x];
                *dest++ = src[1][x];
                *dest++ = src[2][x];
                *dest++ = 0xff;
            }
        }

        for (i = 0; i < 3; i++)
            src[i] += srcStride[i];
    }
}