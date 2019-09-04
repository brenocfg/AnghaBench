#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  available; } ;
struct TYPE_17__ {TYPE_1__* priv; } ;
struct TYPE_16__ {int /*<<< orphan*/  time_base; TYPE_4__* dst; } ;
struct TYPE_15__ {int pts; } ;
struct TYPE_14__ {TYPE_9__* queues; } ;
typedef  TYPE_1__ InterleaveContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 unsigned int FF_INLINK_IDX (TYPE_3__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 int av_q2d (int /*<<< orphan*/ ) ; 
 int av_rescale_q (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_bufqueue_add (TYPE_4__*,TYPE_9__*,TYPE_2__*) ; 
 int push_frame (TYPE_4__*) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *frame)
{
    AVFilterContext *ctx = inlink->dst;
    InterleaveContext *s = ctx->priv;
    unsigned in_no = FF_INLINK_IDX(inlink);

    if (frame->pts == AV_NOPTS_VALUE) {
        av_log(ctx, AV_LOG_WARNING,
               "NOPTS value for input frame cannot be accepted, frame discarded\n");
        av_frame_free(&frame);
        return AVERROR_INVALIDDATA;
    }

    /* queue frame */
    frame->pts = av_rescale_q(frame->pts, inlink->time_base, AV_TIME_BASE_Q);
    av_log(ctx, AV_LOG_DEBUG, "frame pts:%f -> queue idx:%d available:%d\n",
           frame->pts * av_q2d(AV_TIME_BASE_Q), in_no, s->queues[in_no].available);
    ff_bufqueue_add(ctx, &s->queues[in_no], frame);

    return push_frame(ctx);
}