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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */

__attribute__((used)) static inline void codec37_mv(uint8_t *dst, const uint8_t *src,
                              int height, int stride, int x, int y)
{
    int pos, i, j;

    pos = x + y * stride;
    for (j = 0; j < 4; j++) {
        for (i = 0; i < 4; i++) {
            if ((pos + i) < 0 || (pos + i) >= height * stride)
                dst[i] = 0;
            else
                dst[i] = src[i];
        }
        dst += stride;
        src += stride;
        pos += stride;
    }
}