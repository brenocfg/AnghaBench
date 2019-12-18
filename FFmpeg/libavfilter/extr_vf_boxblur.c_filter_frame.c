#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {TYPE_5__** outputs; TYPE_2__* priv; } ;
struct TYPE_21__ {int w; int /*<<< orphan*/  h; int /*<<< orphan*/  format; TYPE_6__* dst; } ;
struct TYPE_20__ {int height; scalar_t__* linesize; scalar_t__* data; } ;
struct TYPE_19__ {TYPE_1__* comp; } ;
struct TYPE_18__ {int /*<<< orphan*/  temp; int /*<<< orphan*/ * power; int /*<<< orphan*/ * radius; int /*<<< orphan*/  vsub; int /*<<< orphan*/  hsub; } ;
struct TYPE_17__ {int depth; } ;
typedef  TYPE_2__ BoxBlurContext ;
typedef  TYPE_3__ AVPixFmtDescriptor ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFilterLink ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_CEIL_RSHIFT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_4__**) ; 
 TYPE_3__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int ff_filter_frame (TYPE_5__*,TYPE_4__*) ; 
 TYPE_4__* ff_get_video_buffer (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hblur (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  vblur (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    BoxBlurContext *s = ctx->priv;
    AVFilterLink *outlink = inlink->dst->outputs[0];
    AVFrame *out;
    int plane;
    int cw = AV_CEIL_RSHIFT(inlink->w, s->hsub), ch = AV_CEIL_RSHIFT(in->height, s->vsub);
    int w[4] = { inlink->w, cw, cw, inlink->w };
    int h[4] = { in->height, ch, ch, in->height };
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);
    const int depth = desc->comp[0].depth;
    const int pixsize = (depth+7)/8;

    out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
    if (!out) {
        av_frame_free(&in);
        return AVERROR(ENOMEM);
    }
    av_frame_copy_props(out, in);

    for (plane = 0; plane < 4 && in->data[plane] && in->linesize[plane]; plane++)
        hblur(out->data[plane], out->linesize[plane],
              in ->data[plane], in ->linesize[plane],
              w[plane], h[plane], s->radius[plane], s->power[plane],
              s->temp, pixsize);

    for (plane = 0; plane < 4 && in->data[plane] && in->linesize[plane]; plane++)
        vblur(out->data[plane], out->linesize[plane],
              out->data[plane], out->linesize[plane],
              w[plane], h[plane], s->radius[plane], s->power[plane],
              s->temp, pixsize);

    av_frame_free(&in);

    return ff_filter_frame(outlink, out);
}