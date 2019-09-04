#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ rescale_pts; } ;
struct TYPE_11__ {TYPE_2__** outputs; TYPE_4__* priv; } ;
struct TYPE_10__ {int /*<<< orphan*/  sample_rate; TYPE_3__* dst; } ;
struct TYPE_9__ {int /*<<< orphan*/  pts; int /*<<< orphan*/  sample_rate; } ;
typedef  TYPE_1__ AVFrame ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;
typedef  TYPE_4__ ASetRateContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_rescale (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_filter_frame (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *frame)
{
    AVFilterContext *ctx = inlink->dst;
    ASetRateContext *sr = ctx->priv;
    AVFilterLink *outlink = ctx->outputs[0];

    frame->sample_rate = outlink->sample_rate;
    if (sr->rescale_pts)
        frame->pts = av_rescale(frame->pts, inlink->sample_rate,
                                           outlink->sample_rate);
    return ff_filter_frame(outlink, frame);
}