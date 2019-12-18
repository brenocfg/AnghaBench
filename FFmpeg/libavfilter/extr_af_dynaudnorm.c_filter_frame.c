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
struct TYPE_11__ {int /*<<< orphan*/  is_disabled; TYPE_2__** outputs; TYPE_1__* priv; } ;
struct TYPE_10__ {TYPE_3__* dst; } ;
struct TYPE_9__ {int /*<<< orphan*/  queue; int /*<<< orphan*/  is_enabled; int /*<<< orphan*/ * gain_history_smoothed; } ;
typedef  TYPE_1__ DynamicAudioNormalizerContext ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  amplify_frame (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  analyze_frame (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_frame_make_writable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cqueue_dequeue (int /*<<< orphan*/ ,double*) ; 
 int /*<<< orphan*/  cqueue_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cqueue_enqueue (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ff_bufqueue_add (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ff_bufqueue_get (int /*<<< orphan*/ *) ; 
 int ff_filter_frame (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    DynamicAudioNormalizerContext *s = ctx->priv;
    AVFilterLink *outlink = inlink->dst->outputs[0];
    int ret = 1;

    if (!cqueue_empty(s->gain_history_smoothed[0])) {
        double is_enabled;
        AVFrame *out = ff_bufqueue_get(&s->queue);

        cqueue_dequeue(s->is_enabled, &is_enabled);

        amplify_frame(s, out, is_enabled > 0.);
        ret = ff_filter_frame(outlink, out);
    }

    av_frame_make_writable(in);
    cqueue_enqueue(s->is_enabled, !ctx->is_disabled);
    analyze_frame(s, in);
    ff_bufqueue_add(ctx, &s->queue, in);

    return ret;
}