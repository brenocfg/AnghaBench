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
typedef  int ssize_t ;

/* Variables and functions */

__attribute__((used)) static int copy_emulation_prev(const uint8_t *src,
                               size_t         src_size,
                               uint8_t       *dst,
                               ssize_t        dst_offset,
                               size_t         dst_size)
{
    int zeros = 0;
    int wrote_bytes;
    uint8_t* dst_start;
    uint8_t* dst_end = dst + dst_size;
    const uint8_t* src_end = src + src_size;
    int start_at = dst_offset > 2 ? dst_offset - 2 : 0;
    int i;
    for (i = start_at; i < dst_offset && i < dst_size; i++) {
        if (!dst[i])
            zeros++;
        else
            zeros = 0;
    }

    dst += dst_offset;
    dst_start = dst;
    for (; src < src_end; src++, dst++) {
        if (zeros == 2) {
            int insert_ep3_byte = *src <= 3;
            if (insert_ep3_byte) {
                if (dst < dst_end)
                    *dst = 3;
                dst++;
            }

            zeros = 0;
        }

        if (dst < dst_end)
            *dst = *src;

        if (!*src)
            zeros++;
        else
            zeros = 0;
    }

    wrote_bytes = dst - dst_start;

    if (dst > dst_end)
        return -wrote_bytes;

    return wrote_bytes;
}