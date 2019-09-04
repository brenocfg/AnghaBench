#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_21__ {TYPE_3__** outputs; TYPE_3__** inputs; TYPE_1__* priv; } ;
struct TYPE_20__ {int /*<<< orphan*/  time_base; } ;
struct TYPE_19__ {scalar_t__ pts; } ;
struct TYPE_18__ {scalar_t__ pts; } ;
typedef  TYPE_1__ GraphMonitorContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 int FFERROR_NOT_READY ; 
 int /*<<< orphan*/  FF_FILTER_FORWARD_STATUS (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  FF_FILTER_FORWARD_STATUS_BACK (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  FF_FILTER_FORWARD_WANTED (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 scalar_t__ av_rescale_q (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int create_frame (TYPE_4__*,scalar_t__) ; 
 int ff_inlink_consume_frame (TYPE_3__*,TYPE_2__**) ; 
 scalar_t__ ff_inlink_queued_frames (TYPE_3__*) ; 
 scalar_t__ ff_outlink_frame_wanted (TYPE_3__*) ; 

__attribute__((used)) static int activate(AVFilterContext *ctx)
{
    GraphMonitorContext *s = ctx->priv;
    AVFilterLink *inlink = ctx->inputs[0];
    AVFilterLink *outlink = ctx->outputs[0];
    int64_t pts = AV_NOPTS_VALUE;

    FF_FILTER_FORWARD_STATUS_BACK(outlink, inlink);

    if (ff_inlink_queued_frames(inlink)) {
        AVFrame *frame = NULL;
        int ret;

        ret = ff_inlink_consume_frame(inlink, &frame);
        if (ret < 0)
            return ret;
        if (ret > 0) {
            pts = frame->pts;
            av_frame_free(&frame);
        }
    }

    if (pts != AV_NOPTS_VALUE) {
        pts = av_rescale_q(pts, inlink->time_base, outlink->time_base);
        if (s->pts < pts && ff_outlink_frame_wanted(outlink))
            return create_frame(ctx, pts);
    }

    FF_FILTER_FORWARD_STATUS(inlink, outlink);
    FF_FILTER_FORWARD_WANTED(outlink, inlink);

    return FFERROR_NOT_READY;
}