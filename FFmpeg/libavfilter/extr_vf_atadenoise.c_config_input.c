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
struct TYPE_14__ {int /*<<< orphan*/  filter_row; } ;
struct TYPE_13__ {scalar_t__ algorithm; int* thra; int* fthra; int* thrb; int* fthrb; TYPE_6__ dsp; int /*<<< orphan*/  filter_slice; void** planewidth; void** planeheight; int /*<<< orphan*/  nb_planes; } ;
struct TYPE_12__ {TYPE_5__* priv; } ;
struct TYPE_11__ {void* w; void* h; TYPE_4__* dst; int /*<<< orphan*/  format; } ;
struct TYPE_10__ {TYPE_1__* comp; int /*<<< orphan*/  log2_chroma_w; int /*<<< orphan*/  log2_chroma_h; int /*<<< orphan*/  nb_components; } ;
struct TYPE_9__ {int depth; } ;
typedef  TYPE_2__ AVPixFmtDescriptor ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;
typedef  TYPE_5__ ATADenoiseContext ;

/* Variables and functions */
 scalar_t__ ARCH_X86 ; 
 void* AV_CEIL_RSHIFT (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ PARALLEL ; 
 TYPE_2__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_atadenoise_init_x86 (TYPE_6__*,int,scalar_t__) ; 
 int /*<<< orphan*/  filter_row16 ; 
 int /*<<< orphan*/  filter_row16_serial ; 
 int /*<<< orphan*/  filter_row8 ; 
 int /*<<< orphan*/  filter_row8_serial ; 
 int /*<<< orphan*/  filter_slice ; 

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
    s->filter_slice = filter_slice;
    if (depth == 8)
        s->dsp.filter_row = s->algorithm == PARALLEL ? filter_row8 : filter_row8_serial;
    else
        s->dsp.filter_row = s->algorithm == PARALLEL ? filter_row16 : filter_row16_serial;

    s->thra[0] = s->fthra[0] * (1 << depth) - 1;
    s->thra[1] = s->fthra[1] * (1 << depth) - 1;
    s->thra[2] = s->fthra[2] * (1 << depth) - 1;
    s->thrb[0] = s->fthrb[0] * (1 << depth) - 1;
    s->thrb[1] = s->fthrb[1] * (1 << depth) - 1;
    s->thrb[2] = s->fthrb[2] * (1 << depth) - 1;

    if (ARCH_X86)
        ff_atadenoise_init_x86(&s->dsp, depth, s->algorithm);

    return 0;
}