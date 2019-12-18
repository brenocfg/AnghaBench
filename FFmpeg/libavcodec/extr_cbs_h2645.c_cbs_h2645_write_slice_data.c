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
typedef  int /*<<< orphan*/  CodedBitstreamContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_RB32 (int const*) ; 
 int /*<<< orphan*/  ENOSPC ; 
 int const MAX_UINT_BITS (int) ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int ff_ctz (int const) ; 
 int /*<<< orphan*/  flush_put_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int const*,size_t) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int const) ; 
 int /*<<< orphan*/  put_bits32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int put_bits_count (int /*<<< orphan*/ *) ; 
 size_t put_bits_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_bits_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_put_bytes (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int cbs_h2645_write_slice_data(CodedBitstreamContext *ctx,
                                      PutBitContext *pbc, const uint8_t *data,
                                      size_t data_size, int data_bit_start)
{
    size_t rest  = data_size - (data_bit_start + 7) / 8;
    const uint8_t *pos = data + data_bit_start / 8;

    av_assert0(data_bit_start >= 0 &&
               8 * data_size > data_bit_start);

    if (data_size * 8 + 8 > put_bits_left(pbc))
        return AVERROR(ENOSPC);

    if (!rest)
        goto rbsp_stop_one_bit;

    // First copy the remaining bits of the first byte
    // The above check ensures that we do not accidentally
    // copy beyond the rbsp_stop_one_bit.
    if (data_bit_start % 8)
        put_bits(pbc, 8 - data_bit_start % 8,
                 *pos++ & MAX_UINT_BITS(8 - data_bit_start % 8));

    if (put_bits_count(pbc) % 8 == 0) {
        // If the writer is aligned at this point,
        // memcpy can be used to improve performance.
        // This happens normally for CABAC.
        flush_put_bits(pbc);
        memcpy(put_bits_ptr(pbc), pos, rest);
        skip_put_bytes(pbc, rest);
    } else {
        // If not, we have to copy manually.
        // rbsp_stop_one_bit forces us to special-case
        // the last byte.
        uint8_t temp;
        int i;

        for (; rest > 4; rest -= 4, pos += 4)
            put_bits32(pbc, AV_RB32(pos));

        for (; rest > 1; rest--, pos++)
            put_bits(pbc, 8, *pos);

    rbsp_stop_one_bit:
        temp = rest ? *pos : *pos & MAX_UINT_BITS(8 - data_bit_start % 8);

        av_assert0(temp);
        i = ff_ctz(*pos);
        temp = temp >> i;
        i = rest ? (8 - i) : (8 - i - data_bit_start % 8);
        put_bits(pbc, i, temp);
        if (put_bits_count(pbc) % 8)
            put_bits(pbc, 8 - put_bits_count(pbc) % 8, 0);
    }

    return 0;
}