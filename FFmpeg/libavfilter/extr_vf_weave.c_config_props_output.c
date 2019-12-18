#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int* planeheight; int /*<<< orphan*/  nb_planes; int /*<<< orphan*/  linesize; int /*<<< orphan*/  double_weave; } ;
typedef  TYPE_3__ WeaveContext ;
struct TYPE_14__ {TYPE_5__** inputs; TYPE_3__* priv; } ;
struct TYPE_10__ {int den; int /*<<< orphan*/  num; } ;
struct TYPE_9__ {int num; int /*<<< orphan*/  den; } ;
struct TYPE_13__ {int h; int /*<<< orphan*/  format; int /*<<< orphan*/  w; TYPE_2__ frame_rate; TYPE_1__ time_base; TYPE_6__* src; } ;
struct TYPE_12__ {int /*<<< orphan*/  log2_chroma_h; } ;
typedef  TYPE_4__ AVPixFmtDescriptor ;
typedef  TYPE_5__ AVFilterLink ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
 int AV_CEIL_RSHIFT (int,int /*<<< orphan*/ ) ; 
 int av_image_fill_linesizes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_pix_fmt_count_planes (int /*<<< orphan*/ ) ; 
 TYPE_4__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_props_output(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    WeaveContext *s = ctx->priv;
    AVFilterLink *inlink = ctx->inputs[0];
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);
    int ret;

    if (!s->double_weave) {
        outlink->time_base.num = inlink->time_base.num * 2;
        outlink->time_base.den = inlink->time_base.den;
        outlink->frame_rate.num = inlink->frame_rate.num;
        outlink->frame_rate.den = inlink->frame_rate.den * 2;
    }
    outlink->w = inlink->w;
    outlink->h = inlink->h * 2;

    if ((ret = av_image_fill_linesizes(s->linesize, inlink->format, inlink->w)) < 0)
        return ret;

    s->planeheight[1] = s->planeheight[2] = AV_CEIL_RSHIFT(inlink->h, desc->log2_chroma_h);
    s->planeheight[0] = s->planeheight[3] = inlink->h;

    s->nb_planes = av_pix_fmt_count_planes(inlink->format);

    return 0;
}