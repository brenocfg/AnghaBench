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

__attribute__((used)) static void jpg_unescape(const uint8_t *src, int src_size,
                         uint8_t *dst, int *dst_size)
{
    const uint8_t *src_end = src + src_size;
    uint8_t *dst_start = dst;

    while (src < src_end) {
        uint8_t x = *src++;

        *dst++ = x;

        if (x == 0xFF && !*src)
            src++;
    }
    *dst_size = dst - dst_start;
}