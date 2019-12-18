#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int codebook; int huff_lsbs; int /*<<< orphan*/  huff_offset; } ;
struct TYPE_10__ {int /*<<< orphan*/ * shift; } ;
struct TYPE_12__ {int param_presence_flags; int blocksize; int* quant_step_size; TYPE_2__ matrix_params; } ;
struct TYPE_11__ {TYPE_5__* cur_channel_params; TYPE_1__* cur_restart_header; TYPE_4__* cur_decoding_params; } ;
struct TYPE_9__ {unsigned int max_matrix_channel; unsigned int max_channel; unsigned int min_channel; } ;
typedef  TYPE_1__ RestartHeader ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_2__ MatrixParams ;
typedef  TYPE_3__ MLPEncodeContext ;
typedef  TYPE_4__ DecodingParams ;
typedef  TYPE_5__ ChannelParams ;

/* Variables and functions */
 int /*<<< orphan*/  FIR ; 
 int /*<<< orphan*/  IIR ; 
 int PARAMS_DEFAULT ; 
 int PARAM_BLOCKSIZE ; 
 int PARAM_FIR ; 
 int PARAM_HUFFOFFSET ; 
 int PARAM_IIR ; 
 int PARAM_MATRIX ; 
 int PARAM_OUTSHIFT ; 
 int PARAM_PRESENCE_FLAGS ; 
 int PARAM_QUANTSTEP ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  put_sbits (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_filter_params (TYPE_3__*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_matrix_params (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void write_decoding_params(MLPEncodeContext *ctx, PutBitContext *pb,
                                  int params_changed)
{
    DecodingParams *dp = ctx->cur_decoding_params;
    RestartHeader  *rh = ctx->cur_restart_header;
    MatrixParams *mp = &dp->matrix_params;
    unsigned int ch;

    if (dp->param_presence_flags != PARAMS_DEFAULT &&
        params_changed & PARAM_PRESENCE_FLAGS) {
        put_bits(pb, 1, 1);
        put_bits(pb, 8, dp->param_presence_flags);
    } else {
        put_bits(pb, 1, 0);
    }

    if (dp->param_presence_flags & PARAM_BLOCKSIZE) {
        if (params_changed       & PARAM_BLOCKSIZE) {
            put_bits(pb, 1, 1);
            put_bits(pb, 9, dp->blocksize);
        } else {
            put_bits(pb, 1, 0);
        }
    }

    if (dp->param_presence_flags & PARAM_MATRIX) {
        if (params_changed       & PARAM_MATRIX) {
            put_bits(pb, 1, 1);
            write_matrix_params(ctx, pb);
        } else {
            put_bits(pb, 1, 0);
        }
    }

    if (dp->param_presence_flags & PARAM_OUTSHIFT) {
        if (params_changed       & PARAM_OUTSHIFT) {
            put_bits(pb, 1, 1);
            for (ch = 0; ch <= rh->max_matrix_channel; ch++)
                put_sbits(pb, 4, mp->shift[ch]);
        } else {
            put_bits(pb, 1, 0);
        }
    }

    if (dp->param_presence_flags & PARAM_QUANTSTEP) {
        if (params_changed       & PARAM_QUANTSTEP) {
            put_bits(pb, 1, 1);
            for (ch = 0; ch <= rh->max_channel; ch++)
                put_bits(pb, 4, dp->quant_step_size[ch]);
        } else {
            put_bits(pb, 1, 0);
        }
    }

    for (ch = rh->min_channel; ch <= rh->max_channel; ch++) {
        ChannelParams *cp = &ctx->cur_channel_params[ch];

        if (dp->param_presence_flags & 0xF) {
            put_bits(pb, 1, 1);

            if (dp->param_presence_flags & PARAM_FIR) {
                if (params_changed       & PARAM_FIR) {
                    put_bits(pb, 1, 1);
                    write_filter_params(ctx, pb, ch, FIR);
                } else {
                    put_bits(pb, 1, 0);
                }
            }

            if (dp->param_presence_flags & PARAM_IIR) {
                if (params_changed       & PARAM_IIR) {
                    put_bits(pb, 1, 1);
                    write_filter_params(ctx, pb, ch, IIR);
                } else {
                    put_bits(pb, 1, 0);
                }
            }

            if (dp->param_presence_flags & PARAM_HUFFOFFSET) {
                if (params_changed       & PARAM_HUFFOFFSET) {
                    put_bits (pb,  1, 1);
                    put_sbits(pb, 15, cp->huff_offset);
                } else {
                    put_bits(pb, 1, 0);
                }
            }

            put_bits(pb, 2, cp->codebook );
            put_bits(pb, 5, cp->huff_lsbs);
        } else {
            put_bits(pb, 1, 0);
        }
    }
}