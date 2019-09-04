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
struct FFBufQueue {scalar_t__ available; } ;
typedef  int int64_t ;
struct TYPE_13__ {int nb_inputs; int /*<<< orphan*/ * outputs; TYPE_1__** inputs; TYPE_2__* priv; } ;
struct TYPE_12__ {int pts; } ;
struct TYPE_11__ {struct FFBufQueue* queues; } ;
struct TYPE_10__ {int /*<<< orphan*/  status_out; } ;
typedef  TYPE_2__ InterleaveContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 int INT64_MAX ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,int,int) ; 
 int av_q2d (int /*<<< orphan*/ ) ; 
 TYPE_3__* ff_bufqueue_get (struct FFBufQueue*) ; 
 TYPE_3__* ff_bufqueue_peek (struct FFBufQueue*,int /*<<< orphan*/ ) ; 
 int ff_filter_frame (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) inline static int push_frame(AVFilterContext *ctx)
{
    InterleaveContext *s = ctx->priv;
    AVFrame *frame;
    int i, queue_idx = -1;
    int64_t pts_min = INT64_MAX;

    /* look for oldest frame */
    for (i = 0; i < ctx->nb_inputs; i++) {
        struct FFBufQueue *q = &s->queues[i];

        if (!q->available && !ctx->inputs[i]->status_out)
            return 0;
        if (q->available) {
            frame = ff_bufqueue_peek(q, 0);
            if (frame->pts < pts_min) {
                pts_min = frame->pts;
                queue_idx = i;
            }
        }
    }

    /* all inputs are closed */
    if (queue_idx < 0)
        return AVERROR_EOF;

    frame = ff_bufqueue_get(&s->queues[queue_idx]);
    av_log(ctx, AV_LOG_DEBUG, "queue:%d -> frame time:%f\n",
           queue_idx, frame->pts * av_q2d(AV_TIME_BASE_Q));
    return ff_filter_frame(ctx->outputs[0], frame);
}