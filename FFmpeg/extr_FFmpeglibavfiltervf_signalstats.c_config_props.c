#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_4__** inputs; TYPE_2__* priv; } ;
struct TYPE_12__ {int w; int h; int /*<<< orphan*/  format; TYPE_5__* src; } ;
struct TYPE_11__ {TYPE_1__* comp; int /*<<< orphan*/  log2_chroma_h; int /*<<< orphan*/  log2_chroma_w; } ;
struct TYPE_10__ {int depth; int chromaw; int chromah; int fs; int cfs; int nb_jobs; void* frame_hue; void* frame_sat; void* jobs_rets; int /*<<< orphan*/  vsub; int /*<<< orphan*/  hsub; void* histsat; void* histv; void* histu; void* histy; } ;
struct TYPE_9__ {int depth; } ;
typedef  TYPE_2__ SignalstatsContext ;
typedef  TYPE_3__ AVPixFmtDescriptor ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 void* AV_CEIL_RSHIFT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_PIX_FMT_GRAY16 ; 
 int /*<<< orphan*/  AV_PIX_FMT_GRAY8 ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMAX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FFMIN (int,int /*<<< orphan*/ ) ; 
 void* alloc_frame (int /*<<< orphan*/ ,int,int) ; 
 void* av_malloc_array (int,int) ; 
 TYPE_3__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_filter_get_nb_threads (TYPE_5__*) ; 

__attribute__((used)) static int config_props(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    SignalstatsContext *s = ctx->priv;
    AVFilterLink *inlink = outlink->src->inputs[0];
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(outlink->format);
    s->hsub = desc->log2_chroma_w;
    s->vsub = desc->log2_chroma_h;
    s->depth = desc->comp[0].depth;
    if (s->depth > 8) {
        s->histy = av_malloc_array(1 << s->depth, sizeof(*s->histy));
        s->histu = av_malloc_array(1 << s->depth, sizeof(*s->histu));
        s->histv = av_malloc_array(1 << s->depth, sizeof(*s->histv));
        s->histsat = av_malloc_array(1 << s->depth, sizeof(*s->histsat));

        if (!s->histy || !s->histu || !s->histv || !s->histsat)
            return AVERROR(ENOMEM);
    }

    outlink->w = inlink->w;
    outlink->h = inlink->h;

    s->chromaw = AV_CEIL_RSHIFT(inlink->w, s->hsub);
    s->chromah = AV_CEIL_RSHIFT(inlink->h, s->vsub);

    s->fs = inlink->w * inlink->h;
    s->cfs = s->chromaw * s->chromah;

    s->nb_jobs   = FFMAX(1, FFMIN(inlink->h, ff_filter_get_nb_threads(ctx)));
    s->jobs_rets = av_malloc_array(s->nb_jobs, sizeof(*s->jobs_rets));
    if (!s->jobs_rets)
        return AVERROR(ENOMEM);

    s->frame_sat = alloc_frame(s->depth > 8 ? AV_PIX_FMT_GRAY16 : AV_PIX_FMT_GRAY8,  inlink->w, inlink->h);
    s->frame_hue = alloc_frame(AV_PIX_FMT_GRAY16, inlink->w, inlink->h);
    if (!s->frame_sat || !s->frame_hue)
        return AVERROR(ENOMEM);

    return 0;
}