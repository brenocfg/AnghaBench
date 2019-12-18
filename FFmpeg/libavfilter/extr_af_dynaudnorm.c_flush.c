#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/ * inputs; TYPE_1__* priv; } ;
struct TYPE_15__ {TYPE_4__* src; } ;
struct TYPE_14__ {int /*<<< orphan*/  pts; } ;
struct TYPE_12__ {scalar_t__ available; } ;
struct TYPE_13__ {TYPE_11__ queue; scalar_t__ delay; int /*<<< orphan*/  pts; int /*<<< orphan*/ * gain_history_smoothed; } ;
typedef  TYPE_1__ DynamicAudioNormalizerContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  cqueue_empty (int /*<<< orphan*/ ) ; 
 TYPE_2__* ff_bufqueue_get (TYPE_11__*) ; 
 int ff_filter_frame (TYPE_3__*,TYPE_2__*) ; 
 int flush_buffer (TYPE_1__*,int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static int flush(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    DynamicAudioNormalizerContext *s = ctx->priv;
    int ret = 0;

    if (!cqueue_empty(s->gain_history_smoothed[0])) {
        ret = flush_buffer(s, ctx->inputs[0], outlink);
    } else if (s->queue.available) {
        AVFrame *out = ff_bufqueue_get(&s->queue);

        s->pts = out->pts;
        ret = ff_filter_frame(outlink, out);
        s->delay = s->queue.available;
    }

    return ret;
}