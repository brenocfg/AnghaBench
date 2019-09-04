#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {TYPE_3__** outputs; TYPE_1__* priv; } ;
struct TYPE_18__ {int const w; int const h; TYPE_4__* dst; } ;
struct TYPE_17__ {int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;
struct TYPE_16__ {scalar_t__ luma_strength; scalar_t__ chroma_strength; int /*<<< orphan*/  vsub; int /*<<< orphan*/  hsub; } ;
typedef  TYPE_1__ OWDenoiseContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_CEIL_RSHIFT (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 scalar_t__ av_frame_is_writable (TYPE_2__*) ; 
 int /*<<< orphan*/  av_image_copy_plane (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int const) ; 
 int ff_filter_frame (TYPE_3__*,TYPE_2__*) ; 
 TYPE_2__* ff_get_video_buffer (TYPE_3__*,int const,int const) ; 
 int /*<<< orphan*/  filter (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int const,scalar_t__) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    OWDenoiseContext *s = ctx->priv;
    AVFilterLink *outlink = ctx->outputs[0];
    AVFrame *out;
    const int cw = AV_CEIL_RSHIFT(inlink->w, s->hsub);
    const int ch = AV_CEIL_RSHIFT(inlink->h, s->vsub);

    if (av_frame_is_writable(in)) {
        out = in;

        if (s->luma_strength > 0)
            filter(s, out->data[0], out->linesize[0], in->data[0], in->linesize[0], inlink->w, inlink->h, s->luma_strength);
        if (s->chroma_strength > 0) {
            filter(s, out->data[1], out->linesize[1], in->data[1], in->linesize[1], cw,        ch,        s->chroma_strength);
            filter(s, out->data[2], out->linesize[2], in->data[2], in->linesize[2], cw,        ch,        s->chroma_strength);
        }
    } else {
        out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
        if (!out) {
            av_frame_free(&in);
            return AVERROR(ENOMEM);
        }
        av_frame_copy_props(out, in);

        if (s->luma_strength > 0) {
            filter(s, out->data[0], out->linesize[0], in->data[0], in->linesize[0], inlink->w, inlink->h, s->luma_strength);
        } else {
            av_image_copy_plane(out->data[0], out->linesize[0], in ->data[0], in ->linesize[0], inlink->w, inlink->h);
        }
        if (s->chroma_strength > 0) {
            filter(s, out->data[1], out->linesize[1], in->data[1], in->linesize[1], cw, ch, s->chroma_strength);
            filter(s, out->data[2], out->linesize[2], in->data[2], in->linesize[2], cw, ch, s->chroma_strength);
        } else {
            av_image_copy_plane(out->data[1], out->linesize[1], in ->data[1], in ->linesize[1], inlink->w, inlink->h);
            av_image_copy_plane(out->data[2], out->linesize[2], in ->data[2], in ->linesize[2], inlink->w, inlink->h);
        }

        if (in->data[3])
            av_image_copy_plane(out->data[3], out->linesize[3],
                                in ->data[3], in ->linesize[3],
                                inlink->w, inlink->h);
        av_frame_free(&in);
    }

    return ff_filter_frame(outlink, out);
}