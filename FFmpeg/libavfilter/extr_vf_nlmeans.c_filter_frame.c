#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_3__** outputs; TYPE_1__* priv; } ;
struct TYPE_17__ {int w; int h; TYPE_4__* dst; } ;
struct TYPE_16__ {int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;
struct TYPE_15__ {int nb_planes; int chroma_w; int chroma_h; int patch_hsize_uv; int patch_hsize; int research_hsize_uv; int research_hsize; } ;
typedef  TYPE_1__ NLMeansContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int ff_filter_frame (TYPE_3__*,TYPE_2__*) ; 
 TYPE_2__* ff_get_video_buffer (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  nlmeans_plane (TYPE_4__*,int const,int const,int const,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    int i;
    AVFilterContext *ctx = inlink->dst;
    NLMeansContext *s = ctx->priv;
    AVFilterLink *outlink = ctx->outputs[0];

    AVFrame *out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
    if (!out) {
        av_frame_free(&in);
        return AVERROR(ENOMEM);
    }
    av_frame_copy_props(out, in);

    for (i = 0; i < s->nb_planes; i++) {
        const int w = i ? s->chroma_w          : inlink->w;
        const int h = i ? s->chroma_h          : inlink->h;
        const int p = i ? s->patch_hsize_uv    : s->patch_hsize;
        const int r = i ? s->research_hsize_uv : s->research_hsize;
        nlmeans_plane(ctx, w, h, p, r,
                      out->data[i], out->linesize[i],
                      in->data[i],  in->linesize[i]);
    }

    av_frame_free(&in);
    return ff_filter_frame(outlink, out);
}