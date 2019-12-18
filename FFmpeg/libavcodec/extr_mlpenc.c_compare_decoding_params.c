#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ huff_offset; scalar_t__ codebook; scalar_t__ huff_lsbs; } ;
struct TYPE_13__ {scalar_t__* shift; } ;
struct TYPE_15__ {scalar_t__ param_presence_flags; scalar_t__ blocksize; scalar_t__* quant_step_size; TYPE_2__ matrix_params; } ;
struct TYPE_14__ {TYPE_5__* cur_channel_params; TYPE_5__* prev_channel_params; TYPE_1__* cur_restart_header; TYPE_4__* cur_decoding_params; TYPE_4__* prev_decoding_params; } ;
struct TYPE_12__ {unsigned int max_matrix_channel; unsigned int max_channel; unsigned int min_channel; } ;
typedef  TYPE_1__ RestartHeader ;
typedef  TYPE_2__ MatrixParams ;
typedef  TYPE_3__ MLPEncodeContext ;
typedef  TYPE_4__ DecodingParams ;
typedef  TYPE_5__ ChannelParams ;

/* Variables and functions */
 int /*<<< orphan*/  FIR ; 
 int /*<<< orphan*/  IIR ; 
 int PARAM_BLOCKSIZE ; 
 int PARAM_FIR ; 
 int PARAM_HUFFOFFSET ; 
 int PARAM_IIR ; 
 int PARAM_MATRIX ; 
 int PARAM_OUTSHIFT ; 
 int PARAM_PRESENCE_FLAGS ; 
 int PARAM_QUANTSTEP ; 
 scalar_t__ compare_filter_params (TYPE_5__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ compare_matrix_params (TYPE_3__*,TYPE_2__*,TYPE_2__*) ; 

__attribute__((used)) static int compare_decoding_params(MLPEncodeContext *ctx)
{
    DecodingParams *prev = ctx->prev_decoding_params;
    DecodingParams *dp = ctx->cur_decoding_params;
    MatrixParams *prev_mp = &prev->matrix_params;
    MatrixParams *mp = &dp->matrix_params;
    RestartHeader  *rh = ctx->cur_restart_header;
    unsigned int ch;
    int retval = 0;

    if (prev->param_presence_flags != dp->param_presence_flags)
        retval |= PARAM_PRESENCE_FLAGS;

    if (prev->blocksize != dp->blocksize)
        retval |= PARAM_BLOCKSIZE;

    if (compare_matrix_params(ctx, prev_mp, mp))
        retval |= PARAM_MATRIX;

    for (ch = 0; ch <= rh->max_matrix_channel; ch++)
        if (prev_mp->shift[ch] != mp->shift[ch]) {
            retval |= PARAM_OUTSHIFT;
            break;
        }

    for (ch = 0; ch <= rh->max_channel; ch++)
        if (prev->quant_step_size[ch] != dp->quant_step_size[ch]) {
            retval |= PARAM_QUANTSTEP;
            break;
        }

    for (ch = rh->min_channel; ch <= rh->max_channel; ch++) {
        ChannelParams *prev_cp = &ctx->prev_channel_params[ch];
        ChannelParams *cp = &ctx->cur_channel_params[ch];

        if (!(retval & PARAM_FIR) &&
            compare_filter_params(prev_cp, cp, FIR))
            retval |= PARAM_FIR;

        if (!(retval & PARAM_IIR) &&
            compare_filter_params(prev_cp, cp, IIR))
            retval |= PARAM_IIR;

        if (prev_cp->huff_offset != cp->huff_offset)
            retval |= PARAM_HUFFOFFSET;

        if (prev_cp->codebook    != cp->codebook  ||
            prev_cp->huff_lsbs   != cp->huff_lsbs  )
            retval |= 0x1;
    }

    return retval;
}