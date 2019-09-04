#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  log2_chroma_h; int /*<<< orphan*/  log2_chroma_w; TYPE_1__* comp; } ;
struct TYPE_10__ {TYPE_3__** inputs; TYPE_2__* priv; } ;
struct TYPE_9__ {void* h; void* w; int /*<<< orphan*/  format; TYPE_4__* src; } ;
struct TYPE_8__ {int depth; int max; int luma2d; int lt; int lumaT; int tl; int chromaT1; int tc; int chromaT2; int ct; int /*<<< orphan*/  derainbow; int /*<<< orphan*/  dedotcrawl; void** planeheight; TYPE_6__* desc; void** planewidth; int /*<<< orphan*/  nb_planes; } ;
struct TYPE_7__ {int depth; } ;
typedef  TYPE_2__ DedotContext ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR_BUG ; 
 void* AV_CEIL_RSHIFT (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_pix_fmt_count_planes (int /*<<< orphan*/ ) ; 
 TYPE_6__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dedotcrawl16 ; 
 int /*<<< orphan*/  dedotcrawl8 ; 
 int /*<<< orphan*/  derainbow16 ; 
 int /*<<< orphan*/  derainbow8 ; 

__attribute__((used)) static int config_output(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    DedotContext *s = ctx->priv;
    AVFilterLink *inlink = ctx->inputs[0];

    s->desc = av_pix_fmt_desc_get(outlink->format);
    if (!s->desc)
        return AVERROR_BUG;
    s->nb_planes = av_pix_fmt_count_planes(outlink->format);
    s->depth = s->desc->comp[0].depth;
    s->max = (1 << s->depth) - 1;
    s->luma2d = s->lt * s->max;
    s->lumaT = s->tl * s->max;
    s->chromaT1 = s->tc * s->max;
    s->chromaT2 = s->ct * s->max;

    s->planewidth[1] = s->planewidth[2] = AV_CEIL_RSHIFT(inlink->w, s->desc->log2_chroma_w);
    s->planewidth[0] = s->planewidth[3] = inlink->w;

    s->planeheight[1] = s->planeheight[2] = AV_CEIL_RSHIFT(inlink->h, s->desc->log2_chroma_h);
    s->planeheight[0] = s->planeheight[3] = inlink->h;

    if (s->depth <= 8) {
        s->dedotcrawl = dedotcrawl8;
        s->derainbow = derainbow8;
    } else {
        s->dedotcrawl = dedotcrawl16;
        s->derainbow = derainbow16;
    }

    return 0;
}