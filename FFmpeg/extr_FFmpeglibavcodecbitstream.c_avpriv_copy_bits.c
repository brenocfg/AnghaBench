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
typedef  int /*<<< orphan*/  PutBitContext ;

/* Variables and functions */
 int AV_RB16 (int const*) ; 
 scalar_t__ CONFIG_SMALL ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  flush_put_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int const*,int) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int const) ; 
 int put_bits_count (int /*<<< orphan*/ *) ; 
 int put_bits_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_bits_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_put_bytes (int /*<<< orphan*/ *,int) ; 

void avpriv_copy_bits(PutBitContext *pb, const uint8_t *src, int length)
{
    int words = length >> 4;
    int bits  = length & 15;
    int i;

    if (length == 0)
        return;

    av_assert0(length <= put_bits_left(pb));

    if (CONFIG_SMALL || words < 16 || put_bits_count(pb) & 7) {
        for (i = 0; i < words; i++)
            put_bits(pb, 16, AV_RB16(src + 2 * i));
    } else {
        for (i = 0; put_bits_count(pb) & 31; i++)
            put_bits(pb, 8, src[i]);
        flush_put_bits(pb);
        memcpy(put_bits_ptr(pb), src + i, 2 * words - i);
        skip_put_bytes(pb, 2 * words - i);
    }

    put_bits(pb, bits, AV_RB16(src + 2 * words) >> (16 - bits));
}