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

void rgb24to32(const uint8_t *src, uint8_t *dst, int src_size)
{
    int i;

    for (i = 0; 3 * i < src_size; i++) {
#if HAVE_BIGENDIAN
        /* RGB24 (= R, G, B) -> BGR32 (= A, R, G, B) */
        dst[4 * i + 0] = 255;
        dst[4 * i + 1] = src[3 * i + 0];
        dst[4 * i + 2] = src[3 * i + 1];
        dst[4 * i + 3] = src[3 * i + 2];
#else
        dst[4 * i + 0] = src[3 * i + 2];
        dst[4 * i + 1] = src[3 * i + 1];
        dst[4 * i + 2] = src[3 * i + 0];
        dst[4 * i + 3] = 255;
#endif
    }
}