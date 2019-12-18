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
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,int const*,int) ; 

__attribute__((used)) static int xan_huffman_decode(uint8_t *dest, int dest_len,
                              const uint8_t *src, int src_len)
{
    uint8_t byte = *src++;
    uint8_t ival = byte + 0x16;
    const uint8_t * ptr = src + byte*2;
    int ptr_len = src_len - 1 - byte*2;
    uint8_t val = ival;
    uint8_t *dest_end = dest + dest_len;
    uint8_t *dest_start = dest;
    int ret;
    GetBitContext gb;

    if ((ret = init_get_bits8(&gb, ptr, ptr_len)) < 0)
        return ret;

    while (val != 0x16) {
        unsigned idx;
        if (get_bits_left(&gb) < 1)
            return AVERROR_INVALIDDATA;
        idx = val - 0x17 + get_bits1(&gb) * byte;
        if (idx >= 2 * byte)
            return AVERROR_INVALIDDATA;
        val = src[idx];

        if (val < 0x16) {
            if (dest >= dest_end)
                return dest_len;
            *dest++ = val;
            val = ival;
        }
    }

    return dest - dest_start;
}