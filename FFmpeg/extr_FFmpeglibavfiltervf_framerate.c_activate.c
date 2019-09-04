#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_11__ {TYPE_1__* priv; int /*<<< orphan*/ ** outputs; int /*<<< orphan*/ ** inputs; } ;
struct TYPE_10__ {scalar_t__ pts; scalar_t__ interlaced_frame; } ;
struct TYPE_9__ {scalar_t__ pts1; scalar_t__ pts0; scalar_t__ delta; double score; scalar_t__ start_pts; int flush; TYPE_2__* f0; scalar_t__ n; TYPE_2__* f1; int /*<<< orphan*/  dest_time_base; int /*<<< orphan*/  srce_time_base; int /*<<< orphan*/  work; } ;
typedef  TYPE_1__ FrameRateContext ;
typedef  TYPE_2__ AVFrame ;
typedef  int /*<<< orphan*/  AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int FFERROR_NOT_READY ; 
 int /*<<< orphan*/  FF_FILTER_FORWARD_STATUS_BACK (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FF_FILTER_FORWARD_WANTED (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ av_rescale_q (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_filter_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ff_inlink_acknowledge_status (int /*<<< orphan*/ *,int*,scalar_t__*) ; 
 int ff_inlink_consume_frame (int /*<<< orphan*/ *,TYPE_2__**) ; 
 int /*<<< orphan*/  ff_outlink_set_status (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int process_work_frame (TYPE_3__*) ; 

__attribute__((used)) static int activate(AVFilterContext *ctx)
{
    int ret, status;
    AVFilterLink *inlink = ctx->inputs[0];
    AVFilterLink *outlink = ctx->outputs[0];
    FrameRateContext *s = ctx->priv;
    AVFrame *inpicref;
    int64_t pts;

    FF_FILTER_FORWARD_STATUS_BACK(outlink, inlink);

retry:
    ret = process_work_frame(ctx);
    if (ret < 0)
        return ret;
    else if (ret == 1)
        return ff_filter_frame(outlink, s->work);

    ret = ff_inlink_consume_frame(inlink, &inpicref);
    if (ret < 0)
        return ret;

    if (inpicref) {
        if (inpicref->interlaced_frame)
            av_log(ctx, AV_LOG_WARNING, "Interlaced frame found - the output will not be correct.\n");

        if (inpicref->pts == AV_NOPTS_VALUE) {
            av_log(ctx, AV_LOG_WARNING, "Ignoring frame without PTS.\n");
            av_frame_free(&inpicref);
        }
    }

    if (inpicref) {
        pts = av_rescale_q(inpicref->pts, s->srce_time_base, s->dest_time_base);

        if (s->f1 && pts == s->pts1) {
            av_log(ctx, AV_LOG_WARNING, "Ignoring frame with same PTS.\n");
            av_frame_free(&inpicref);
        }
    }

    if (inpicref) {
        av_frame_free(&s->f0);
        s->f0 = s->f1;
        s->pts0 = s->pts1;
        s->f1 = inpicref;
        s->pts1 = pts;
        s->delta = s->pts1 - s->pts0;
        s->score = -1.0;

        if (s->delta < 0) {
            av_log(ctx, AV_LOG_WARNING, "PTS discontinuity.\n");
            s->start_pts = s->pts1;
            s->n = 0;
            av_frame_free(&s->f0);
        }

        if (s->start_pts == AV_NOPTS_VALUE)
            s->start_pts = s->pts1;

        goto retry;
    }

    if (ff_inlink_acknowledge_status(inlink, &status, &pts)) {
        if (!s->flush) {
            s->flush = 1;
            goto retry;
        }
        ff_outlink_set_status(outlink, status, pts);
        return 0;
    }

    FF_FILTER_FORWARD_WANTED(outlink, inlink);

    return FFERROR_NOT_READY;
}