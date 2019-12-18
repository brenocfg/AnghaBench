#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_19__ {int /*<<< orphan*/  time_base; } ;
struct TYPE_18__ {int nb_inputs; TYPE_4__** inputs; TYPE_1__* priv; int /*<<< orphan*/ ** outputs; } ;
struct TYPE_17__ {scalar_t__ pts; } ;
struct TYPE_16__ {scalar_t__ pts; } ;
typedef  TYPE_1__ InterleaveContext ;
typedef  TYPE_2__ AVFrame ;
typedef  int /*<<< orphan*/  AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVERROR_EOF ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 int FFERROR_NOT_READY ; 
 int /*<<< orphan*/  FF_FILTER_FORWARD_STATUS_BACK_ALL (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ INT64_MAX ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ av_rescale_q (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_filter_frame (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int ff_inlink_consume_frame (TYPE_4__*,TYPE_2__**) ; 
 TYPE_2__* ff_inlink_peek_frame (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ff_inlink_queued_frames (TYPE_4__*) ; 
 int /*<<< orphan*/  ff_inlink_request_frame (TYPE_4__*) ; 
 scalar_t__ ff_outlink_frame_wanted (int /*<<< orphan*/ *) ; 
 scalar_t__ ff_outlink_get_status (TYPE_4__*) ; 
 int /*<<< orphan*/  ff_outlink_set_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int activate(AVFilterContext *ctx)
{
    AVFilterLink *outlink = ctx->outputs[0];
    InterleaveContext *s = ctx->priv;
    int64_t q_pts, pts = INT64_MAX;
    int i, nb_eofs = 0, input_idx = -1;

    FF_FILTER_FORWARD_STATUS_BACK_ALL(outlink, ctx);

    for (i = 0; i < ctx->nb_inputs; i++) {
        if (!ff_outlink_get_status(ctx->inputs[i]) &&
            !ff_inlink_queued_frames(ctx->inputs[i]))
            break;
    }

    if (i == ctx->nb_inputs) {
        for (i = 0; i < ctx->nb_inputs; i++) {
            AVFrame *frame;

            if (ff_outlink_get_status(ctx->inputs[i]))
                continue;

            frame = ff_inlink_peek_frame(ctx->inputs[i], 0);
            if (frame->pts == AV_NOPTS_VALUE) {
                int ret;

                av_log(ctx, AV_LOG_WARNING,
                       "NOPTS value for input frame cannot be accepted, frame discarded\n");
                ret = ff_inlink_consume_frame(ctx->inputs[i], &frame);
                if (ret < 0)
                    return ret;
                av_frame_free(&frame);
                return AVERROR_INVALIDDATA;
            }

            q_pts = av_rescale_q(frame->pts, ctx->inputs[i]->time_base, AV_TIME_BASE_Q);
            if (q_pts < pts) {
                pts = q_pts;
                input_idx = i;
            }
        }

        if (input_idx >= 0) {
            AVFrame *frame;
            int ret;

            ret = ff_inlink_consume_frame(ctx->inputs[input_idx], &frame);
            if (ret < 0)
                return ret;

            frame->pts = s->pts = pts;
            return ff_filter_frame(outlink, frame);
        }
    }

    for (i = 0; i < ctx->nb_inputs; i++) {
        if (ff_inlink_queued_frames(ctx->inputs[i]))
            continue;
        if (ff_outlink_frame_wanted(outlink) &&
            !ff_outlink_get_status(ctx->inputs[i])) {
            ff_inlink_request_frame(ctx->inputs[i]);
            return 0;
        }
        nb_eofs++;
    }

    if (nb_eofs == ctx->nb_inputs) {
        ff_outlink_set_status(outlink, AVERROR_EOF, s->pts);
        return 0;
    }

    return FFERROR_NOT_READY;
}