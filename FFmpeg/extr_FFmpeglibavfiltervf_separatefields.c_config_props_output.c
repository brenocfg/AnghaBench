#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_4__** inputs; TYPE_3__* priv; } ;
struct TYPE_9__ {int num; int /*<<< orphan*/  den; } ;
struct TYPE_8__ {int den; int /*<<< orphan*/  num; } ;
struct TYPE_11__ {int h; int /*<<< orphan*/  w; TYPE_2__ frame_rate; TYPE_1__ time_base; int /*<<< orphan*/  format; TYPE_5__* src; } ;
struct TYPE_10__ {int /*<<< orphan*/  nb_planes; } ;
typedef  TYPE_3__ SeparateFieldsContext ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  av_pix_fmt_count_planes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_props_output(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    SeparateFieldsContext *s = ctx->priv;
    AVFilterLink *inlink = ctx->inputs[0];

    s->nb_planes = av_pix_fmt_count_planes(inlink->format);

    if (inlink->h & 1) {
        av_log(ctx, AV_LOG_ERROR, "height must be even\n");
        return AVERROR_INVALIDDATA;
    }

    outlink->time_base.num = inlink->time_base.num;
    outlink->time_base.den = inlink->time_base.den * 2;
    outlink->frame_rate.num = inlink->frame_rate.num * 2;
    outlink->frame_rate.den = inlink->frame_rate.den;
    outlink->w = inlink->w;
    outlink->h = inlink->h / 2;

    return 0;
}