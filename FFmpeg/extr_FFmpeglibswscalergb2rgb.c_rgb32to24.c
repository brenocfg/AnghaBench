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

void rgb32to24(const uint8_t *src, uint8_t *dst, int src_size)
{
    int i, num_pixels = src_size >> 2;

    for (i = 0; i < num_pixels; i++) {
#if HAVE_BIGENDIAN
        /* RGB32 (= A,B,G,R) -> BGR24 (= B,G,R) */
        dst[3 * i + 0] = src[4 * i + 1];
        dst[3 * i + 1] = src[4 * i + 2];
        dst[3 * i + 2] = src[4 * i + 3];
#else
        dst[3 * i + 0] = src[4 * i + 2];
        dst[3 * i + 1] = src[4 * i + 1];
        dst[3 * i + 2] = src[4 * i + 0];
#endif
    }
}