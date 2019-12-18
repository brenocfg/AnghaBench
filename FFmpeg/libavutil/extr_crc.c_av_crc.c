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
typedef  size_t uint8_t ;
typedef  int uint32_t ;
typedef  int AVCRC ;

/* Variables and functions */
 int av_le2ne32 (int const) ; 

uint32_t av_crc(const AVCRC *ctx, uint32_t crc,
                const uint8_t *buffer, size_t length)
{
    const uint8_t *end = buffer + length;

#if !CONFIG_SMALL
    if (!ctx[256]) {
        while (((intptr_t) buffer & 3) && buffer < end)
            crc = ctx[((uint8_t) crc) ^ *buffer++] ^ (crc >> 8);

        while (buffer < end - 3) {
            crc ^= av_le2ne32(*(const uint32_t *) buffer); buffer += 4;
            crc = ctx[3 * 256 + ( crc        & 0xFF)] ^
                  ctx[2 * 256 + ((crc >> 8 ) & 0xFF)] ^
                  ctx[1 * 256 + ((crc >> 16) & 0xFF)] ^
                  ctx[0 * 256 + ((crc >> 24)       )];
        }
    }
#endif
    while (buffer < end)
        crc = ctx[((uint8_t) crc) ^ *buffer++] ^ (crc >> 8);

    return crc;
}