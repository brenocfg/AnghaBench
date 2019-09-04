#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_12__ {scalar_t__ huff_lsbs; } ;
struct TYPE_11__ {unsigned int num_substreams; int restart_intervals; int sequence_size; int* seq_offset; unsigned int* seq_size; unsigned int number_of_frames; scalar_t__* max_output_bits; int major_filter_state_subblock; scalar_t__ major_cur_subblock_index; int /*<<< orphan*/  number_of_subblocks; int /*<<< orphan*/  major_number_of_subblocks; int /*<<< orphan*/ * cur_channel_params; int /*<<< orphan*/ * prev_channel_params; int /*<<< orphan*/ * cur_decoding_params; int /*<<< orphan*/ * prev_decoding_params; int /*<<< orphan*/ ** major_params_changed; int /*<<< orphan*/ ** major_channel_params; int /*<<< orphan*/ ** major_decoding_params; TYPE_2__* restart_header; TYPE_2__* cur_restart_header; TYPE_1__* avctx; scalar_t__ channel_params; scalar_t__ decoding_params; } ;
struct TYPE_10__ {scalar_t__ max_output_bits; scalar_t__ max_huff_lsbs; } ;
struct TYPE_9__ {int channels; } ;
typedef  TYPE_2__ RestartHeader ;
typedef  TYPE_3__ MLPEncodeContext ;
typedef  TYPE_4__ DecodingParams ;
typedef  TYPE_4__ ChannelParams ;

/* Variables and functions */
 int MAJOR_HEADER_INTERVAL ; 
 int /*<<< orphan*/  compare_decoding_params (TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/ * restart_channel_params ; 
 int /*<<< orphan*/ * restart_decoding_params ; 

__attribute__((used)) static void set_major_params(MLPEncodeContext *ctx)
{
    RestartHeader *rh = ctx->cur_restart_header;
    unsigned int index;
    unsigned int substr;
    uint8_t max_huff_lsbs = 0;
    uint8_t max_output_bits = 0;

    for (substr = 0; substr < ctx->num_substreams; substr++) {
        DecodingParams *seq_dp = (DecodingParams *) ctx->decoding_params+
                                 (ctx->restart_intervals - 1)*(ctx->sequence_size)*(ctx->avctx->channels) +
                                 (ctx->seq_offset[ctx->restart_intervals - 1])*(ctx->avctx->channels);

        ChannelParams *seq_cp = (ChannelParams *) ctx->channel_params +
                                (ctx->restart_intervals - 1)*(ctx->sequence_size)*(ctx->avctx->channels) +
                                (ctx->seq_offset[ctx->restart_intervals - 1])*(ctx->avctx->channels);
        unsigned int channel;
        for (index = 0; index < ctx->seq_size[ctx->restart_intervals-1]; index++) {
            memcpy(&ctx->major_decoding_params[index][substr], seq_dp + index*(ctx->num_substreams) + substr, sizeof(DecodingParams));
            for (channel = 0; channel < ctx->avctx->channels; channel++) {
                uint8_t huff_lsbs = (seq_cp + index*(ctx->avctx->channels) + channel)->huff_lsbs;
                if (max_huff_lsbs < huff_lsbs)
                    max_huff_lsbs = huff_lsbs;
                memcpy(&ctx->major_channel_params[index][channel],
                       (seq_cp + index*(ctx->avctx->channels) + channel),
                       sizeof(ChannelParams));
            }
        }
    }

    rh->max_huff_lsbs = max_huff_lsbs;

    for (index = 0; index < ctx->number_of_frames; index++)
        if (max_output_bits < ctx->max_output_bits[index])
            max_output_bits = ctx->max_output_bits[index];
    rh->max_output_bits = max_output_bits;

    for (substr = 0; substr < ctx->num_substreams; substr++) {

        ctx->cur_restart_header = &ctx->restart_header[substr];

        ctx->prev_decoding_params = &restart_decoding_params[substr];
        ctx->prev_channel_params = restart_channel_params;

        for (index = 0; index < MAJOR_HEADER_INTERVAL + 1; index++) {
                ctx->cur_decoding_params = &ctx->major_decoding_params[index][substr];
                ctx->cur_channel_params = ctx->major_channel_params[index];

                ctx->major_params_changed[index][substr] = compare_decoding_params(ctx);

                ctx->prev_decoding_params = ctx->cur_decoding_params;
                ctx->prev_channel_params = ctx->cur_channel_params;
        }
    }

    ctx->major_number_of_subblocks = ctx->number_of_subblocks;
    ctx->major_filter_state_subblock = 1;
    ctx->major_cur_subblock_index = 0;
}