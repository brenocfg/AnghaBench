#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_13__ {TYPE_2__* priv; int /*<<< orphan*/ ** outputs; int /*<<< orphan*/ ** inputs; } ;
struct TYPE_12__ {int /*<<< orphan*/  hw_frames_ctx; } ;
struct TYPE_10__ {int /*<<< orphan*/ * ringbuffers; } ;
struct TYPE_11__ {int eof; int smooth_window; int /*<<< orphan*/  duration; int /*<<< orphan*/  curr_frame; int /*<<< orphan*/  read_buf_time; int /*<<< orphan*/  crop_upscale_time; int /*<<< orphan*/  transform_time; int /*<<< orphan*/  match_descriptors_time; int /*<<< orphan*/  brief_descriptors_time; int /*<<< orphan*/  refine_features_time; int /*<<< orphan*/  harris_response_time; int /*<<< orphan*/  grayscale_time; scalar_t__ debug_on; int /*<<< orphan*/  fq; TYPE_1__ abs_motion; int /*<<< orphan*/  initialized; } ;
typedef  TYPE_2__ DeshakeOpenCLContext ;
typedef  TYPE_3__ AVFrame ;
typedef  int /*<<< orphan*/  AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int /*<<< orphan*/  EINVAL ; 
 int FFERROR_NOT_READY ; 
 int /*<<< orphan*/  FF_FILTER_FORWARD_STATUS_BACK (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FF_FILTER_FORWARD_WANTED (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int RingbufCount ; 
 size_t RingbufX ; 
 int /*<<< orphan*/  av_fifo_drain (int /*<<< orphan*/ ,int) ; 
 scalar_t__ av_fifo_space (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  averaged_event_time_ms (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int deshake_opencl_init (TYPE_4__*) ; 
 int ff_framequeue_queued_frames (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_framequeue_take (int /*<<< orphan*/ *) ; 
 scalar_t__ ff_inlink_acknowledge_status (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int ff_inlink_consume_frame (int /*<<< orphan*/ *,TYPE_3__**) ; 
 int /*<<< orphan*/  ff_outlink_set_status (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int filter_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int queue_frame (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static int activate(AVFilterContext *ctx)
{
    AVFilterLink *inlink = ctx->inputs[0];
    AVFilterLink *outlink = ctx->outputs[0];
    DeshakeOpenCLContext *deshake_ctx = ctx->priv;
    AVFrame *frame = NULL;
    int ret, status;
    int64_t pts;

    FF_FILTER_FORWARD_STATUS_BACK(outlink, inlink);

    if (!deshake_ctx->eof) {
        ret = ff_inlink_consume_frame(inlink, &frame);
        if (ret < 0)
            return ret;
        if (ret > 0) {
            if (!frame->hw_frames_ctx)
                return AVERROR(EINVAL);

            if (!deshake_ctx->initialized) {
                ret = deshake_opencl_init(ctx);
                if (ret < 0)
                    return ret;
            }

            // If there is no more space in the ringbuffers, remove the oldest
            // values to make room for the new ones
            if (av_fifo_space(deshake_ctx->abs_motion.ringbuffers[RingbufX]) == 0) {
                for (int i = 0; i < RingbufCount; i++) {
                    av_fifo_drain(deshake_ctx->abs_motion.ringbuffers[i], sizeof(float));
                }
            }
            ret = queue_frame(inlink, frame);
            if (ret < 0)
                return ret;
            if (ret >= 0) {
                // See if we have enough buffered frames to process one
                //
                // "enough" is half the smooth window of queued frames into the future
                if (ff_framequeue_queued_frames(&deshake_ctx->fq) >= deshake_ctx->smooth_window / 2) {
                    return filter_frame(inlink, ff_framequeue_take(&deshake_ctx->fq));
                }
            }
        }
    }

    if (!deshake_ctx->eof && ff_inlink_acknowledge_status(inlink, &status, &pts)) {
        if (status == AVERROR_EOF) {
            deshake_ctx->eof = true;
        }
    }

    if (deshake_ctx->eof) {
        // Finish processing the rest of the frames in the queue.
        while(ff_framequeue_queued_frames(&deshake_ctx->fq) != 0) {
            for (int i = 0; i < RingbufCount; i++) {
                av_fifo_drain(deshake_ctx->abs_motion.ringbuffers[i], sizeof(float));
            }

            ret = filter_frame(inlink, ff_framequeue_take(&deshake_ctx->fq));
            if (ret < 0) {
                return ret;
            }
        }

        if (deshake_ctx->debug_on) {
            av_log(ctx, AV_LOG_VERBOSE,
                "Average kernel execution times:\n"
                "\t        grayscale: %0.3f ms\n"
                "\t  harris_response: %0.3f ms\n"
                "\t  refine_features: %0.3f ms\n"
                "\tbrief_descriptors: %0.3f ms\n"
                "\tmatch_descriptors: %0.3f ms\n"
                "\t        transform: %0.3f ms\n"
                "\t     crop_upscale: %0.3f ms\n"
                "Average buffer read times:\n"
                "\t     features buf: %0.3f ms\n",
                averaged_event_time_ms(deshake_ctx->grayscale_time, deshake_ctx->curr_frame),
                averaged_event_time_ms(deshake_ctx->harris_response_time, deshake_ctx->curr_frame),
                averaged_event_time_ms(deshake_ctx->refine_features_time, deshake_ctx->curr_frame),
                averaged_event_time_ms(deshake_ctx->brief_descriptors_time, deshake_ctx->curr_frame),
                averaged_event_time_ms(deshake_ctx->match_descriptors_time, deshake_ctx->curr_frame),
                averaged_event_time_ms(deshake_ctx->transform_time, deshake_ctx->curr_frame),
                averaged_event_time_ms(deshake_ctx->crop_upscale_time, deshake_ctx->curr_frame),
                averaged_event_time_ms(deshake_ctx->read_buf_time, deshake_ctx->curr_frame)
            );
        }

        ff_outlink_set_status(outlink, AVERROR_EOF, deshake_ctx->duration);
        return 0;
    }

    if (!deshake_ctx->eof) {
        FF_FILTER_FORWARD_WANTED(outlink, inlink);
    }

    return FFERROR_NOT_READY;
}