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
struct TYPE_19__ {scalar_t__ is_disabled; TYPE_3__** outputs; TYPE_1__* priv; } ;
struct TYPE_18__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_4__* dst; } ;
struct TYPE_17__ {int /*<<< orphan*/ * linesize; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/ * data; } ;
struct TYPE_16__ {int hsub; int vsub; int /*<<< orphan*/ * coefs; int /*<<< orphan*/ * frame_prev; int /*<<< orphan*/  line; } ;
typedef  TYPE_1__ HQDN3DContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_CEIL_RSHIFT (int /*<<< orphan*/ ,int) ; 
 size_t CHROMA_SPATIAL ; 
 size_t CHROMA_TMP ; 
 int /*<<< orphan*/  ENOMEM ; 
 size_t LUMA_SPATIAL ; 
 size_t LUMA_TMP ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 scalar_t__ av_frame_is_writable (TYPE_2__*) ; 
 int /*<<< orphan*/  denoise (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_filter_frame (TYPE_3__*,TYPE_2__*) ; 
 TYPE_2__* ff_get_video_buffer (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx  = inlink->dst;
    HQDN3DContext *s = ctx->priv;
    AVFilterLink *outlink = ctx->outputs[0];

    AVFrame *out;
    int c, direct = av_frame_is_writable(in) && !ctx->is_disabled;

    if (direct) {
        out = in;
    } else {
        out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
        if (!out) {
            av_frame_free(&in);
            return AVERROR(ENOMEM);
        }

        av_frame_copy_props(out, in);
    }

    for (c = 0; c < 3; c++) {
        denoise(s, in->data[c], out->data[c],
                s->line, &s->frame_prev[c],
                AV_CEIL_RSHIFT(in->width,  (!!c * s->hsub)),
                AV_CEIL_RSHIFT(in->height, (!!c * s->vsub)),
                in->linesize[c], out->linesize[c],
                s->coefs[c ? CHROMA_SPATIAL : LUMA_SPATIAL],
                s->coefs[c ? CHROMA_TMP     : LUMA_TMP]);
    }

    if (ctx->is_disabled) {
        av_frame_free(&out);
        return ff_filter_frame(outlink, in);
    }

    if (!direct)
        av_frame_free(&in);

    return ff_filter_frame(outlink, out);
}