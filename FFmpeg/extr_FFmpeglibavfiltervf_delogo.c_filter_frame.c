#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {scalar_t__ h; scalar_t__ w; int /*<<< orphan*/  format; TYPE_1__* dst; } ;
struct TYPE_21__ {int num; int den; } ;
struct TYPE_23__ {int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; TYPE_3__ sample_aspect_ratio; } ;
struct TYPE_22__ {int log2_chroma_w; int log2_chroma_h; int nb_components; } ;
struct TYPE_20__ {int x; int y; int band; int /*<<< orphan*/  show; scalar_t__ h; scalar_t__ w; } ;
struct TYPE_19__ {TYPE_6__** outputs; TYPE_2__* priv; } ;
typedef  TYPE_2__ DelogoContext ;
typedef  TYPE_3__ AVRational ;
typedef  TYPE_4__ AVPixFmtDescriptor ;
typedef  TYPE_5__ AVFrame ;
typedef  TYPE_6__ AVFilterLink ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_CEIL_RSHIFT (scalar_t__,int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  apply_delogo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_5__*,TYPE_5__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_5__**) ; 
 scalar_t__ av_frame_is_writable (TYPE_5__*) ; 
 TYPE_4__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int ff_filter_frame (TYPE_6__*,TYPE_5__*) ; 
 TYPE_5__* ff_get_video_buffer (TYPE_6__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    DelogoContext *s = inlink->dst->priv;
    AVFilterLink *outlink = inlink->dst->outputs[0];
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);
    AVFrame *out;
    int hsub0 = desc->log2_chroma_w;
    int vsub0 = desc->log2_chroma_h;
    int direct = 0;
    int plane;
    AVRational sar;

    if (av_frame_is_writable(in)) {
        direct = 1;
        out = in;
    } else {
        out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
        if (!out) {
            av_frame_free(&in);
            return AVERROR(ENOMEM);
        }

        av_frame_copy_props(out, in);
    }

    sar = in->sample_aspect_ratio;
    /* Assume square pixels if SAR is unknown */
    if (!sar.num)
        sar.num = sar.den = 1;

    for (plane = 0; plane < desc->nb_components; plane++) {
        int hsub = plane == 1 || plane == 2 ? hsub0 : 0;
        int vsub = plane == 1 || plane == 2 ? vsub0 : 0;

        apply_delogo(out->data[plane], out->linesize[plane],
                     in ->data[plane], in ->linesize[plane],
                     AV_CEIL_RSHIFT(inlink->w, hsub),
                     AV_CEIL_RSHIFT(inlink->h, vsub),
                     sar, s->x>>hsub, s->y>>vsub,
                     /* Up and left borders were rounded down, inject lost bits
                      * into width and height to avoid error accumulation */
                     AV_CEIL_RSHIFT(s->w + (s->x & ((1<<hsub)-1)), hsub),
                     AV_CEIL_RSHIFT(s->h + (s->y & ((1<<vsub)-1)), vsub),
                     s->band>>FFMIN(hsub, vsub),
                     s->show, direct);
    }

    if (!direct)
        av_frame_free(&in);

    return ff_filter_frame(outlink, out);
}