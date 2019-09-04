#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int blocksize; } ;
struct TYPE_15__ {unsigned int num_substreams; unsigned int number_of_frames; int* frame_size; unsigned int number_of_subblocks; int sample_buffer; int num_channels; TYPE_3__* cur_decoding_params; int /*<<< orphan*/ * best_offset; int /*<<< orphan*/  cur_best_offset; TYPE_1__* avctx; int /*<<< orphan*/ * cur_channel_params; int /*<<< orphan*/ * restart_header; int /*<<< orphan*/ * cur_restart_header; TYPE_3__* seq_decoding_params; int /*<<< orphan*/ * seq_channel_params; } ;
struct TYPE_14__ {int channels; } ;
typedef  TYPE_2__ MLPEncodeContext ;
typedef  TYPE_3__ DecodingParams ;
typedef  int /*<<< orphan*/  ChannelParams ;

/* Variables and functions */
 int /*<<< orphan*/  apply_filters (TYPE_2__*) ; 
 int /*<<< orphan*/  copy_restart_frame_params (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  determine_bits (TYPE_2__*) ; 
 int /*<<< orphan*/  determine_filters (TYPE_2__*) ; 
 int /*<<< orphan*/  determine_quant_step_size (TYPE_2__*) ; 
 int /*<<< orphan*/  generate_2_noise_channels (TYPE_2__*) ; 
 int /*<<< orphan*/  lossless_matrix_coeffs (TYPE_2__*) ; 
 int /*<<< orphan*/  rematrix_channels (TYPE_2__*) ; 
 int /*<<< orphan*/  set_best_codebook (TYPE_2__*) ; 

__attribute__((used)) static void analyze_sample_buffer(MLPEncodeContext *ctx)
{
    ChannelParams *seq_cp = ctx->seq_channel_params;
    DecodingParams *seq_dp = ctx->seq_decoding_params;
    unsigned int index;
    unsigned int substr;

    for (substr = 0; substr < ctx->num_substreams; substr++) {

        ctx->cur_restart_header = &ctx->restart_header[substr];
        ctx->cur_decoding_params = seq_dp + 1*(ctx->num_substreams) + substr;
        ctx->cur_channel_params = seq_cp + 1*(ctx->avctx->channels);

        determine_quant_step_size(ctx);
        generate_2_noise_channels(ctx);
        lossless_matrix_coeffs   (ctx);
        rematrix_channels        (ctx);
        determine_filters        (ctx);
        apply_filters            (ctx);

        copy_restart_frame_params(ctx, substr);

        /* Copy frame_size from frames 0...max to decoding_params 1...max + 1
         * decoding_params[0] is for the filter state subblock.
         */
        for (index = 0; index < ctx->number_of_frames; index++) {
            DecodingParams *dp = seq_dp + (index + 1)*(ctx->num_substreams) + substr;
            dp->blocksize = ctx->frame_size[index];
        }
        /* The official encoder seems to always encode a filter state subblock
         * even if there are no filters. TODO check if it is possible to skip
         * the filter state subblock for no filters.
         */
        (seq_dp + substr)->blocksize  = 8;
        (seq_dp + 1*(ctx->num_substreams) + substr)->blocksize -= 8;

        for (index = 0; index < ctx->number_of_subblocks; index++) {
                ctx->cur_decoding_params = seq_dp + index*(ctx->num_substreams) + substr;
                ctx->cur_channel_params = seq_cp + index*(ctx->avctx->channels);
                ctx->cur_best_offset = ctx->best_offset[index];
                determine_bits(ctx);
                ctx->sample_buffer += ctx->cur_decoding_params->blocksize * ctx->num_channels;
        }

        set_best_codebook(ctx);
    }
}