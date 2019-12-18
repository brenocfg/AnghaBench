#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {int* comp_index; size_t* quant_sindex; unsigned long long* coefs_finished; int mb_height; int* block_stride; int mb_width; int /*<<< orphan*/  avctx; int /*<<< orphan*/ * ac_index; scalar_t__ restart_interval; scalar_t__ restart_count; int /*<<< orphan*/  gb; int /*<<< orphan*/ ** last_nnz; int /*<<< orphan*/ ** blocks; int /*<<< orphan*/ ** quant_matrixes; } ;
typedef  TYPE_1__ MJpegDecodeContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * block ; 
 int decode_block_progressive (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int,int*) ; 
 int decode_block_refinement (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int,int*) ; 
 scalar_t__ get_bits_left (int /*<<< orphan*/ *) ; 
 scalar_t__ handle_rstn (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** int16_t (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mjpeg_decode_scan_progressive_ac(MJpegDecodeContext *s, int ss,
                                            int se, int Ah, int Al)
{
    int mb_x, mb_y;
    int EOBRUN = 0;
    int c = s->comp_index[0];
    uint16_t *quant_matrix = s->quant_matrixes[s->quant_sindex[0]];

    av_assert0(ss>=0 && Ah>=0 && Al>=0);
    if (se < ss || se > 63) {
        av_log(s->avctx, AV_LOG_ERROR, "SS/SE %d/%d is invalid\n", ss, se);
        return AVERROR_INVALIDDATA;
    }

    // s->coefs_finished is a bitmask for coefficients coded
    // ss and se are parameters telling start and end coefficients
    s->coefs_finished[c] |= (2ULL << se) - (1ULL << ss);

    s->restart_count = 0;

    for (mb_y = 0; mb_y < s->mb_height; mb_y++) {
        int block_idx    = mb_y * s->block_stride[c];
        int16_t (*block)[64] = &s->blocks[c][block_idx];
        uint8_t *last_nnz    = &s->last_nnz[c][block_idx];
        if (get_bits_left(&s->gb) <= 0) {
            av_log(s->avctx, AV_LOG_ERROR, "bitstream truncated in mjpeg_decode_scan_progressive_ac\n");
            return AVERROR_INVALIDDATA;
        }
        for (mb_x = 0; mb_x < s->mb_width; mb_x++, block++, last_nnz++) {
                int ret;
                if (s->restart_interval && !s->restart_count)
                    s->restart_count = s->restart_interval;

                if (Ah)
                    ret = decode_block_refinement(s, *block, last_nnz, s->ac_index[0],
                                                  quant_matrix, ss, se, Al, &EOBRUN);
                else
                    ret = decode_block_progressive(s, *block, last_nnz, s->ac_index[0],
                                                   quant_matrix, ss, se, Al, &EOBRUN);
                if (ret < 0) {
                    av_log(s->avctx, AV_LOG_ERROR,
                           "error y=%d x=%d\n", mb_y, mb_x);
                    return AVERROR_INVALIDDATA;
                }

            if (handle_rstn(s, 0))
                EOBRUN = 0;
        }
    }
    return 0;
}