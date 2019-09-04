#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_5__ {TYPE_1__* content; } ;
struct TYPE_4__ {int* data; int data_size; int data_bit_start; int /*<<< orphan*/  header; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_1__ MPEG2RawSlice ;
typedef  TYPE_2__ CodedBitstreamUnit ;
typedef  int /*<<< orphan*/  CodedBitstreamContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_RB32 (int*) ; 
 int /*<<< orphan*/  ENOSPC ; 
 int MAX_UINT_BITS (int) ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int cbs_mpeg2_write_slice_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_put_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,size_t) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  put_bits32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int put_bits_count (int /*<<< orphan*/ *) ; 
 int put_bits_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_bits_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_put_bytes (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int cbs_mpeg2_write_slice(CodedBitstreamContext *ctx,
                                 CodedBitstreamUnit *unit,
                                 PutBitContext *pbc)
{
    MPEG2RawSlice *slice = unit->content;
    int err;

    err = cbs_mpeg2_write_slice_header(ctx, pbc, &slice->header);
    if (err < 0)
        return err;

    if (slice->data) {
        size_t rest = slice->data_size - (slice->data_bit_start + 7) / 8;
        uint8_t *pos = slice->data + slice->data_bit_start / 8;

        av_assert0(slice->data_bit_start >= 0 &&
                   8 * slice->data_size > slice->data_bit_start);

        if (slice->data_size * 8 + 8 > put_bits_left(pbc))
            return AVERROR(ENOSPC);

        // First copy the remaining bits of the first byte
        if (slice->data_bit_start % 8)
            put_bits(pbc, 8 - slice->data_bit_start % 8,
                     *pos++ & MAX_UINT_BITS(8 - slice->data_bit_start % 8));

        if (put_bits_count(pbc) % 8 == 0) {
            // If the writer is aligned at this point,
            // memcpy can be used to improve performance.
            // This is the normal case.
            flush_put_bits(pbc);
            memcpy(put_bits_ptr(pbc), pos, rest);
            skip_put_bytes(pbc, rest);
        } else {
            // If not, we have to copy manually:
            for (; rest > 3; rest -= 4, pos += 4)
                put_bits32(pbc, AV_RB32(pos));

            for (; rest; rest--, pos++)
                put_bits(pbc, 8, *pos);

            // Align with zeros
            put_bits(pbc, 8 - put_bits_count(pbc) % 8, 0);
        }
    }

    return 0;
}