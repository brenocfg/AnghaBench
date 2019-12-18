#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_25__ {int channels; int frame_number; scalar_t__ frame_size; TYPE_2__* priv_data; } ;
struct TYPE_24__ {int /*<<< orphan*/ ** data; } ;
struct TYPE_23__ {unsigned int size; int /*<<< orphan*/  duration; int /*<<< orphan*/  pts; int /*<<< orphan*/  data; } ;
struct TYPE_22__ {int frame_index; int max_restart_interval; scalar_t__ inout_buffer; scalar_t__ major_inout_buffer; int one_sample_buffer_size; scalar_t__ last_frame; scalar_t__ sample_buffer; scalar_t__ major_scratch_buffer; scalar_t__ write_buffer; scalar_t__* frame_size; scalar_t__ min_restart_interval; scalar_t__ next_major_frame_size; unsigned int next_major_number_of_frames; int restart_intervals; int seq_index; int starting_frame_index; unsigned int number_of_frames; unsigned int number_of_subblocks; int sequence_size; int* seq_offset; int num_substreams; unsigned int number_of_samples; unsigned int* seq_size; scalar_t__ major_frame_size; unsigned int major_number_of_frames; int /*<<< orphan*/  afq; int /*<<< orphan*/ * seq_decoding_params; TYPE_1__* avctx; int /*<<< orphan*/ * seq_channel_params; scalar_t__ decoding_params; scalar_t__ channel_params; int /*<<< orphan*/  dts; int /*<<< orphan*/  timestamp; } ;
struct TYPE_21__ {int frame_number; int channels; } ;
typedef  TYPE_2__ MLPEncodeContext ;
typedef  int /*<<< orphan*/  DecodingParams ;
typedef  int /*<<< orphan*/  ChannelParams ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ MAX_BLOCKSIZE ; 
 int /*<<< orphan*/  analyze_sample_buffer (TYPE_2__*) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  clear_channel_params (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  default_decoding_params (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int ff_af_queue_add (int /*<<< orphan*/ *,TYPE_4__ const*) ; 
 int /*<<< orphan*/  ff_af_queue_remove (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ff_alloc_packet2 (TYPE_5__*,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_data (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_to_sample_buffer (TYPE_2__*) ; 
 int /*<<< orphan*/  process_major_frame (TYPE_2__*) ; 
 int /*<<< orphan*/  set_major_params (TYPE_2__*) ; 
 unsigned int write_access_unit (TYPE_2__*,int /*<<< orphan*/ ,unsigned int,int) ; 

__attribute__((used)) static int mlp_encode_frame(AVCodecContext *avctx, AVPacket *avpkt,
                            const AVFrame *frame, int *got_packet)
{
    MLPEncodeContext *ctx = avctx->priv_data;
    unsigned int bytes_written = 0;
    int restart_frame, ret;
    uint8_t *data;

    if ((ret = ff_alloc_packet2(avctx, avpkt, 87500 * avctx->channels, 0)) < 0)
        return ret;

    if (!frame)
        return 1;

    /* add current frame to queue */
    if ((ret = ff_af_queue_add(&ctx->afq, frame)) < 0)
        return ret;

    data = frame->data[0];

    ctx->frame_index = avctx->frame_number % ctx->max_restart_interval;

    ctx->inout_buffer = ctx->major_inout_buffer
                      + ctx->frame_index * ctx->one_sample_buffer_size;

    if (ctx->last_frame == ctx->inout_buffer) {
        return 0;
    }

    ctx->sample_buffer = ctx->major_scratch_buffer
                       + ctx->frame_index * ctx->one_sample_buffer_size;

    ctx->write_buffer = ctx->inout_buffer;

    if (avctx->frame_number < ctx->max_restart_interval) {
        if (data) {
            goto input_and_return;
        } else {
            /* There are less frames than the requested major header interval.
             * Update the context to reflect this.
             */
            ctx->max_restart_interval = avctx->frame_number;
            ctx->frame_index = 0;

            ctx->sample_buffer = ctx->major_scratch_buffer;
            ctx->inout_buffer = ctx->major_inout_buffer;
        }
    }

    if (ctx->frame_size[ctx->frame_index] > MAX_BLOCKSIZE) {
        av_log(avctx, AV_LOG_ERROR, "Invalid frame size (%d > %d)\n",
               ctx->frame_size[ctx->frame_index], MAX_BLOCKSIZE);
        return -1;
    }

    restart_frame = !ctx->frame_index;

    if (restart_frame) {
        set_major_params(ctx);
        if (ctx->min_restart_interval != ctx->max_restart_interval)
        process_major_frame(ctx);
    }

    if (ctx->min_restart_interval == ctx->max_restart_interval)
        ctx->write_buffer = ctx->sample_buffer;

    bytes_written = write_access_unit(ctx, avpkt->data, avpkt->size, restart_frame);

    ctx->timestamp += ctx->frame_size[ctx->frame_index];
    ctx->dts       += ctx->frame_size[ctx->frame_index];

input_and_return:

    if (data) {
        ctx->frame_size[ctx->frame_index] = avctx->frame_size;
        ctx->next_major_frame_size += avctx->frame_size;
        ctx->next_major_number_of_frames++;
        input_data(ctx, data);
    } else if (!ctx->last_frame) {
        ctx->last_frame = ctx->inout_buffer;
    }

    restart_frame = (ctx->frame_index + 1) % ctx->min_restart_interval;

    if (!restart_frame) {
        int seq_index;

        for (seq_index = 0;
             seq_index < ctx->restart_intervals && (seq_index * ctx->min_restart_interval) <= ctx->avctx->frame_number;
             seq_index++) {
            unsigned int number_of_samples = 0;
            unsigned int index;

            ctx->sample_buffer = ctx->major_scratch_buffer;
            ctx->inout_buffer = ctx->major_inout_buffer;
            ctx->seq_index = seq_index;

            ctx->starting_frame_index = (ctx->avctx->frame_number - (ctx->avctx->frame_number % ctx->min_restart_interval)
                                      - (seq_index * ctx->min_restart_interval)) % ctx->max_restart_interval;
            ctx->number_of_frames = ctx->next_major_number_of_frames;
            ctx->number_of_subblocks = ctx->next_major_number_of_frames + 1;

            ctx->seq_channel_params = (ChannelParams *) ctx->channel_params +
                                      (ctx->frame_index / ctx->min_restart_interval)*(ctx->sequence_size)*(ctx->avctx->channels) +
                                      (ctx->seq_offset[seq_index])*(ctx->avctx->channels);

            ctx->seq_decoding_params = (DecodingParams *) ctx->decoding_params +
                                       (ctx->frame_index / ctx->min_restart_interval)*(ctx->sequence_size)*(ctx->num_substreams) +
                                       (ctx->seq_offset[seq_index])*(ctx->num_substreams);

            for (index = 0; index < ctx->number_of_frames; index++) {
                number_of_samples += ctx->frame_size[(ctx->starting_frame_index + index) % ctx->max_restart_interval];
            }
            ctx->number_of_samples = number_of_samples;

            for (index = 0; index < ctx->seq_size[seq_index]; index++) {
                clear_channel_params(ctx, ctx->seq_channel_params + index*(ctx->avctx->channels));
                default_decoding_params(ctx, ctx->seq_decoding_params + index*(ctx->num_substreams));
            }

            input_to_sample_buffer(ctx);

            analyze_sample_buffer(ctx);
        }

        if (ctx->frame_index == (ctx->max_restart_interval - 1)) {
            ctx->major_frame_size = ctx->next_major_frame_size;
            ctx->next_major_frame_size = 0;
            ctx->major_number_of_frames = ctx->next_major_number_of_frames;
            ctx->next_major_number_of_frames = 0;

            if (!ctx->major_frame_size)
                goto no_data_left;
        }
    }

no_data_left:

    ff_af_queue_remove(&ctx->afq, avctx->frame_size, &avpkt->pts,
                       &avpkt->duration);
    avpkt->size = bytes_written;
    *got_packet = 1;
    return 0;
}