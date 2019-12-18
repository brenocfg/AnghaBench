#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  sse_line; } ;
struct TYPE_16__ {TYPE_1__** inputs; TYPE_3__* priv; } ;
struct TYPE_15__ {unsigned int h; unsigned int w; int /*<<< orphan*/  format; TYPE_6__* dst; } ;
struct TYPE_14__ {int nb_components; TYPE_2__* comp; int /*<<< orphan*/  log2_chroma_w; int /*<<< orphan*/  log2_chroma_h; } ;
struct TYPE_13__ {int nb_components; int* max; int is_rgb; char* comps; unsigned int* planeheight; unsigned int* planewidth; double* planeweight; TYPE_7__ dsp; int /*<<< orphan*/  average_max; int /*<<< orphan*/  rgba_map; } ;
struct TYPE_12__ {int depth; } ;
struct TYPE_11__ {scalar_t__ w; scalar_t__ h; scalar_t__ format; } ;
typedef  TYPE_3__ PSNRContext ;
typedef  TYPE_4__ AVPixFmtDescriptor ;
typedef  TYPE_5__ AVFilterLink ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
 scalar_t__ ARCH_X86 ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 void* AV_CEIL_RSHIFT (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_4__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 scalar_t__ ff_fill_rgba_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_psnr_init_x86 (TYPE_7__*,int) ; 
 int /*<<< orphan*/  lrint (double) ; 
 int /*<<< orphan*/  sse_line_16bit ; 
 int /*<<< orphan*/  sse_line_8bit ; 

__attribute__((used)) static int config_input_ref(AVFilterLink *inlink)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);
    AVFilterContext *ctx  = inlink->dst;
    PSNRContext *s = ctx->priv;
    double average_max;
    unsigned sum;
    int j;

    s->nb_components = desc->nb_components;
    if (ctx->inputs[0]->w != ctx->inputs[1]->w ||
        ctx->inputs[0]->h != ctx->inputs[1]->h) {
        av_log(ctx, AV_LOG_ERROR, "Width and height of input videos must be same.\n");
        return AVERROR(EINVAL);
    }
    if (ctx->inputs[0]->format != ctx->inputs[1]->format) {
        av_log(ctx, AV_LOG_ERROR, "Inputs must be of same pixel format.\n");
        return AVERROR(EINVAL);
    }

    s->max[0] = (1 << desc->comp[0].depth) - 1;
    s->max[1] = (1 << desc->comp[1].depth) - 1;
    s->max[2] = (1 << desc->comp[2].depth) - 1;
    s->max[3] = (1 << desc->comp[3].depth) - 1;

    s->is_rgb = ff_fill_rgba_map(s->rgba_map, inlink->format) >= 0;
    s->comps[0] = s->is_rgb ? 'r' : 'y' ;
    s->comps[1] = s->is_rgb ? 'g' : 'u' ;
    s->comps[2] = s->is_rgb ? 'b' : 'v' ;
    s->comps[3] = 'a';

    s->planeheight[1] = s->planeheight[2] = AV_CEIL_RSHIFT(inlink->h, desc->log2_chroma_h);
    s->planeheight[0] = s->planeheight[3] = inlink->h;
    s->planewidth[1]  = s->planewidth[2]  = AV_CEIL_RSHIFT(inlink->w, desc->log2_chroma_w);
    s->planewidth[0]  = s->planewidth[3]  = inlink->w;
    sum = 0;
    for (j = 0; j < s->nb_components; j++)
        sum += s->planeheight[j] * s->planewidth[j];
    average_max = 0;
    for (j = 0; j < s->nb_components; j++) {
        s->planeweight[j] = (double) s->planeheight[j] * s->planewidth[j] / sum;
        average_max += s->max[j] * s->planeweight[j];
    }
    s->average_max = lrint(average_max);

    s->dsp.sse_line = desc->comp[0].depth > 8 ? sse_line_16bit : sse_line_8bit;
    if (ARCH_X86)
        ff_psnr_init_x86(&s->dsp, desc->comp[0].depth);

    return 0;
}