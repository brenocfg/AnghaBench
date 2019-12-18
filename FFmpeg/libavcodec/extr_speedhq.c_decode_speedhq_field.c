#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  last_alpha ;
struct TYPE_8__ {int* linesize; int height; int width; int /*<<< orphan*/ ** data; } ;
struct TYPE_7__ {scalar_t__ alpha_type; scalar_t__ subsampling; } ;
typedef  TYPE_1__ SHQContext ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AV_RL24 (int /*<<< orphan*/  const*) ; 
 scalar_t__ SHQ_DCT_ALPHA ; 
 scalar_t__ SHQ_NO_ALPHA ; 
 scalar_t__ SHQ_RLE_ALPHA ; 
 scalar_t__ SHQ_SUBSAMPLING_420 ; 
 scalar_t__ SHQ_SUBSAMPLING_444 ; 
 int decode_alpha_block (TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int decode_dct_block (TYPE_1__ const*,int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ *,int) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int decode_speedhq_field(const SHQContext *s, const uint8_t *buf, int buf_size, AVFrame *frame, int field_number, int start, int end, int line_stride)
{
    int ret, slice_number, slice_offsets[5];
    int linesize_y  = frame->linesize[0] * line_stride;
    int linesize_cb = frame->linesize[1] * line_stride;
    int linesize_cr = frame->linesize[2] * line_stride;
    int linesize_a;

    if (s->alpha_type != SHQ_NO_ALPHA)
        linesize_a = frame->linesize[3] * line_stride;

    if (end < start || end - start < 3 || end > buf_size)
        return AVERROR_INVALIDDATA;

    slice_offsets[0] = start;
    slice_offsets[4] = end;
    for (slice_number = 1; slice_number < 4; slice_number++) {
        uint32_t last_offset, slice_len;

        last_offset = slice_offsets[slice_number - 1];
        slice_len = AV_RL24(buf + last_offset);
        slice_offsets[slice_number] = last_offset + slice_len;

        if (slice_len < 3 || slice_offsets[slice_number] > end - 3)
            return AVERROR_INVALIDDATA;
    }

    for (slice_number = 0; slice_number < 4; slice_number++) {
        GetBitContext gb;
        uint32_t slice_begin, slice_end;
        int x, y;

        slice_begin = slice_offsets[slice_number];
        slice_end = slice_offsets[slice_number + 1];

        if ((ret = init_get_bits8(&gb, buf + slice_begin + 3, slice_end - slice_begin - 3)) < 0)
            return ret;

        for (y = slice_number * 16 * line_stride; y < frame->height; y += line_stride * 64) {
            uint8_t *dest_y, *dest_cb, *dest_cr, *dest_a;
            int last_dc[4] = { 1024, 1024, 1024, 1024 };
            uint8_t last_alpha[16];

            memset(last_alpha, 255, sizeof(last_alpha));

            dest_y = frame->data[0] + frame->linesize[0] * (y + field_number);
            if (s->subsampling == SHQ_SUBSAMPLING_420) {
                dest_cb = frame->data[1] + frame->linesize[1] * (y/2 + field_number);
                dest_cr = frame->data[2] + frame->linesize[2] * (y/2 + field_number);
            } else {
                dest_cb = frame->data[1] + frame->linesize[1] * (y + field_number);
                dest_cr = frame->data[2] + frame->linesize[2] * (y + field_number);
            }
            if (s->alpha_type != SHQ_NO_ALPHA) {
                dest_a = frame->data[3] + frame->linesize[3] * (y + field_number);
            }

            for (x = 0; x < frame->width; x += 16) {
                /* Decode the four luma blocks. */
                if ((ret = decode_dct_block(s, &gb, last_dc, 0, dest_y, linesize_y)) < 0)
                    return ret;
                if ((ret = decode_dct_block(s, &gb, last_dc, 0, dest_y + 8, linesize_y)) < 0)
                    return ret;
                if ((ret = decode_dct_block(s, &gb, last_dc, 0, dest_y + 8 * linesize_y, linesize_y)) < 0)
                    return ret;
                if ((ret = decode_dct_block(s, &gb, last_dc, 0, dest_y + 8 * linesize_y + 8, linesize_y)) < 0)
                    return ret;

                /*
                 * Decode the first chroma block. For 4:2:0, this is the only one;
                 * for 4:2:2, it's the top block; for 4:4:4, it's the top-left block.
                 */
                if ((ret = decode_dct_block(s, &gb, last_dc, 1, dest_cb, linesize_cb)) < 0)
                    return ret;
                if ((ret = decode_dct_block(s, &gb, last_dc, 2, dest_cr, linesize_cr)) < 0)
                    return ret;

                if (s->subsampling != SHQ_SUBSAMPLING_420) {
                    /* For 4:2:2, this is the bottom block; for 4:4:4, it's the bottom-left block. */
                    if ((ret = decode_dct_block(s, &gb, last_dc, 1, dest_cb + 8 * linesize_cb, linesize_cb)) < 0)
                        return ret;
                    if ((ret = decode_dct_block(s, &gb, last_dc, 2, dest_cr + 8 * linesize_cr, linesize_cr)) < 0)
                        return ret;

                    if (s->subsampling == SHQ_SUBSAMPLING_444) {
                        /* Top-right and bottom-right blocks. */
                        if ((ret = decode_dct_block(s, &gb, last_dc, 1, dest_cb + 8, linesize_cb)) < 0)
                            return ret;
                        if ((ret = decode_dct_block(s, &gb, last_dc, 2, dest_cr + 8, linesize_cr)) < 0)
                            return ret;
                        if ((ret = decode_dct_block(s, &gb, last_dc, 1, dest_cb + 8 * linesize_cb + 8, linesize_cb)) < 0)
                            return ret;
                        if ((ret = decode_dct_block(s, &gb, last_dc, 2, dest_cr + 8 * linesize_cr + 8, linesize_cr)) < 0)
                            return ret;

                        dest_cb += 8;
                        dest_cr += 8;
                    }
                }
                dest_y += 16;
                dest_cb += 8;
                dest_cr += 8;

                if (s->alpha_type == SHQ_RLE_ALPHA) {
                    /* Alpha coded using 16x8 RLE blocks. */
                    if ((ret = decode_alpha_block(s, &gb, last_alpha, dest_a, linesize_a)) < 0)
                        return ret;
                    if ((ret = decode_alpha_block(s, &gb, last_alpha, dest_a + 8 * linesize_a, linesize_a)) < 0)
                        return ret;
                    dest_a += 16;
                } else if (s->alpha_type == SHQ_DCT_ALPHA) {
                    /* Alpha encoded exactly like luma. */
                    if ((ret = decode_dct_block(s, &gb, last_dc, 3, dest_a, linesize_a)) < 0)
                        return ret;
                    if ((ret = decode_dct_block(s, &gb, last_dc, 3, dest_a + 8, linesize_a)) < 0)
                        return ret;
                    if ((ret = decode_dct_block(s, &gb, last_dc, 3, dest_a + 8 * linesize_a, linesize_a)) < 0)
                        return ret;
                    if ((ret = decode_dct_block(s, &gb, last_dc, 3, dest_a + 8 * linesize_a + 8, linesize_a)) < 0)
                        return ret;
                    dest_a += 16;
                }
            }
        }
    }

    return 0;
}