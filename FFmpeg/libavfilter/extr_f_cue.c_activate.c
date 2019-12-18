#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_22__ {TYPE_1__* priv; TYPE_3__** outputs; TYPE_3__** inputs; } ;
struct TYPE_21__ {int /*<<< orphan*/  time_base; } ;
struct TYPE_20__ {int /*<<< orphan*/  pts; } ;
struct TYPE_19__ {int status; scalar_t__ first_pts; scalar_t__ preroll; scalar_t__ buffer; scalar_t__ cue; } ;
typedef  TYPE_1__ CueContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 int FFERROR_NOT_READY ; 
 int /*<<< orphan*/  FF_FILTER_FORWARD_STATUS (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  FF_FILTER_FORWARD_STATUS_BACK (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  FF_FILTER_FORWARD_WANTED (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  av_clip (scalar_t__,int,int) ; 
 scalar_t__ av_gettime () ; 
 scalar_t__ av_rescale_q (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_usleep (int /*<<< orphan*/ ) ; 
 int ff_filter_frame (TYPE_3__*,TYPE_2__*) ; 
 int ff_inlink_consume_frame (TYPE_3__*,TYPE_2__**) ; 
 TYPE_2__* ff_inlink_peek_frame (TYPE_3__*,scalar_t__) ; 
 scalar_t__ ff_inlink_queued_frames (TYPE_3__*) ; 

__attribute__((used)) static int activate(AVFilterContext *ctx)
{
    AVFilterLink *inlink = ctx->inputs[0];
    AVFilterLink *outlink = ctx->outputs[0];
    CueContext *s = ctx->priv;

    FF_FILTER_FORWARD_STATUS_BACK(outlink, inlink);

    if (ff_inlink_queued_frames(inlink)) {
        AVFrame *frame = ff_inlink_peek_frame(inlink, 0);
        int64_t pts = av_rescale_q(frame->pts, inlink->time_base, AV_TIME_BASE_Q);

        if (!s->status) {
            s->first_pts = pts;
            s->status++;
        }
        if (s->status == 1) {
            if (pts - s->first_pts < s->preroll) {
                int ret = ff_inlink_consume_frame(inlink, &frame);
                if (ret < 0)
                    return ret;
                return ff_filter_frame(outlink, frame);
            }
            s->first_pts = pts;
            s->status++;
        }
        if (s->status == 2) {
            frame = ff_inlink_peek_frame(inlink, ff_inlink_queued_frames(inlink) - 1);
            pts = av_rescale_q(frame->pts, inlink->time_base, AV_TIME_BASE_Q);
            if (!(pts - s->first_pts < s->buffer && (av_gettime() - s->cue) < 0))
                s->status++;
        }
        if (s->status == 3) {
            int64_t diff;
            while ((diff = (av_gettime() - s->cue)) < 0)
                av_usleep(av_clip(-diff / 2, 100, 1000000));
            s->status++;
        }
        if (s->status == 4) {
            int ret = ff_inlink_consume_frame(inlink, &frame);
            if (ret < 0)
                return ret;
            return ff_filter_frame(outlink, frame);
        }
    }

    FF_FILTER_FORWARD_STATUS(inlink, outlink);
    FF_FILTER_FORWARD_WANTED(outlink, inlink);

    return FFERROR_NOT_READY;
}