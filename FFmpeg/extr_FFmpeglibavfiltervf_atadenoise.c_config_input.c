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
struct TYPE_12__ {int* thra; int* fthra; int* thrb; int* fthrb; int /*<<< orphan*/  filter_slice; void** planewidth; void** planeheight; int /*<<< orphan*/  nb_planes; } ;
struct TYPE_11__ {TYPE_5__* priv; } ;
struct TYPE_10__ {void* w; void* h; TYPE_4__* dst; int /*<<< orphan*/  format; } ;
struct TYPE_9__ {TYPE_1__* comp; int /*<<< orphan*/  log2_chroma_w; int /*<<< orphan*/  log2_chroma_h; int /*<<< orphan*/  nb_components; } ;
struct TYPE_8__ {int depth; } ;
typedef  TYPE_2__ AVPixFmtDescriptor ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;
typedef  TYPE_5__ ATADenoiseContext ;

/* Variables and functions */
 void* AV_CEIL_RSHIFT (void*,int /*<<< orphan*/ ) ; 
 TYPE_2__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_slice16 ; 
 int /*<<< orphan*/  filter_slice8 ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);
    AVFilterContext *ctx = inlink->dst;
    ATADenoiseContext *s = ctx->priv;
    int depth;

    s->nb_planes = desc->nb_components;

    s->planeheight[1] = s->planeheight[2] = AV_CEIL_RSHIFT(inlink->h, desc->log2_chroma_h);
    s->planeheight[0] = s->planeheight[3] = inlink->h;
    s->planewidth[1]  = s->planewidth[2]  = AV_CEIL_RSHIFT(inlink->w, desc->log2_chroma_w);
    s->planewidth[0]  = s->planewidth[3]  = inlink->w;

    depth = desc->comp[0].depth;
    if (depth == 8)
        s->filter_slice = filter_slice8;
    else
        s->filter_slice = filter_slice16;

    s->thra[0] = s->fthra[0] * (1 << depth) - 1;
    s->thra[1] = s->fthra[1] * (1 << depth) - 1;
    s->thra[2] = s->fthra[2] * (1 << depth) - 1;
    s->thrb[0] = s->fthrb[0] * (1 << depth) - 1;
    s->thrb[1] = s->fthrb[1] * (1 << depth) - 1;
    s->thrb[2] = s->fthrb[2] * (1 << depth) - 1;

    return 0;
}