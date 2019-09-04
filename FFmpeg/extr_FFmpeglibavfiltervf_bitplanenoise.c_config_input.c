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
struct TYPE_12__ {TYPE_2__* priv; } ;
struct TYPE_11__ {void* w; void* h; TYPE_5__* dst; int /*<<< orphan*/  format; } ;
struct TYPE_10__ {TYPE_1__* comp; int /*<<< orphan*/  log2_chroma_w; int /*<<< orphan*/  log2_chroma_h; int /*<<< orphan*/  nb_components; } ;
struct TYPE_9__ {int /*<<< orphan*/  depth; void** planewidth; void** planeheight; int /*<<< orphan*/  nb_planes; } ;
struct TYPE_8__ {int /*<<< orphan*/  depth; } ;
typedef  TYPE_2__ BPNContext ;
typedef  TYPE_3__ AVPixFmtDescriptor ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 void* AV_CEIL_RSHIFT (void*,int /*<<< orphan*/ ) ; 
 TYPE_3__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);
    AVFilterContext *ctx = inlink->dst;
    BPNContext *s = ctx->priv;

    s->nb_planes = desc->nb_components;

    s->planeheight[1] = s->planeheight[2] = AV_CEIL_RSHIFT(inlink->h, desc->log2_chroma_h);
    s->planeheight[0] = s->planeheight[3] = inlink->h;
    s->planewidth[1]  = s->planewidth[2]  = AV_CEIL_RSHIFT(inlink->w, desc->log2_chroma_w);
    s->planewidth[0]  = s->planewidth[3]  = inlink->w;

    s->depth = desc->comp[0].depth;

    return 0;
}