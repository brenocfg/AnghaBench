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
struct TYPE_11__ {void* h; void* w; int /*<<< orphan*/  format; TYPE_5__* dst; } ;
struct TYPE_10__ {int log2_chroma_w; int log2_chroma_h; TYPE_1__* comp; } ;
struct TYPE_9__ {void* depthy; void** var_values; scalar_t__ tlut2; void* depthx; void** widthx; void** heightx; int /*<<< orphan*/  nb_planesx; } ;
struct TYPE_8__ {void* depth; } ;
typedef  TYPE_2__ LUT2Context ;
typedef  TYPE_3__ AVPixFmtDescriptor ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 void* AV_CEIL_RSHIFT (void*,int) ; 
 size_t VAR_BITDEPTHX ; 
 size_t VAR_BITDEPTHY ; 
 size_t VAR_H ; 
 size_t VAR_W ; 
 int /*<<< orphan*/  av_pix_fmt_count_planes (int /*<<< orphan*/ ) ; 
 TYPE_3__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_inputx(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    LUT2Context *s = ctx->priv;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);
    int hsub = desc->log2_chroma_w;
    int vsub = desc->log2_chroma_h;

    s->nb_planesx = av_pix_fmt_count_planes(inlink->format);
    s->heightx[1] = s->heightx[2] = AV_CEIL_RSHIFT(inlink->h, vsub);
    s->heightx[0] = s->heightx[3] = inlink->h;
    s->widthx[1]  = s->widthx[2]  = AV_CEIL_RSHIFT(inlink->w, hsub);
    s->widthx[0]  = s->widthx[3]  = inlink->w;

    s->var_values[VAR_W] = inlink->w;
    s->var_values[VAR_H] = inlink->h;
    s->depthx = desc->comp[0].depth;
    s->var_values[VAR_BITDEPTHX] = s->depthx;

    if (s->tlut2) {
        s->depthy = desc->comp[0].depth;
        s->var_values[VAR_BITDEPTHY] = s->depthy;
    }

    return 0;
}