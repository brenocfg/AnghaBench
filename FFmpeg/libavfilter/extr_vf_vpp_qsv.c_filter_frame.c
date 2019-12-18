#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ qsv; } ;
typedef  TYPE_1__ VPPContext ;
struct TYPE_15__ {TYPE_3__** outputs; TYPE_1__* priv; } ;
struct TYPE_14__ {int /*<<< orphan*/  time_base; TYPE_4__* dst; } ;
struct TYPE_13__ {int /*<<< orphan*/  pts; } ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int /*<<< orphan*/  av_rescale_q (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_filter_frame (TYPE_3__*,TYPE_2__*) ; 
 int ff_qsvvpp_filter_frame (scalar_t__,TYPE_3__*,TYPE_2__*) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *picref)
{
    int              ret = 0;
    AVFilterContext  *ctx = inlink->dst;
    VPPContext       *vpp = inlink->dst->priv;
    AVFilterLink     *outlink = ctx->outputs[0];

    if (vpp->qsv) {
        ret = ff_qsvvpp_filter_frame(vpp->qsv, inlink, picref);
        av_frame_free(&picref);
    } else {
        if (picref->pts != AV_NOPTS_VALUE)
            picref->pts = av_rescale_q(picref->pts, inlink->time_base, outlink->time_base);
        ret = ff_filter_frame(outlink, picref);
    }

    return ret;
}