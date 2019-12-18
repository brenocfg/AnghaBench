#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int colorspace; int cs; int depth; int size; int /*<<< orphan*/  pd; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  (* graticulef ) (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* vectorscope ) (TYPE_1__*,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ VectorscopeContext ;
struct TYPE_22__ {TYPE_3__** outputs; TYPE_1__* priv; } ;
struct TYPE_21__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_4__* dst; } ;
struct TYPE_20__ {int colorspace; int* linesize; scalar_t__* data; } ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
#define  AVCOL_SPC_BT470BG 130 
#define  AVCOL_SPC_BT709 129 
#define  AVCOL_SPC_SMPTE170M 128 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int ff_filter_frame (TYPE_3__*,TYPE_2__*) ; 
 TYPE_2__* ff_get_video_buffer (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx  = inlink->dst;
    VectorscopeContext *s = ctx->priv;
    AVFilterLink *outlink = ctx->outputs[0];
    AVFrame *out;
    int plane;

    if (s->colorspace) {
        s->cs = (s->depth - 8) * 2 + s->colorspace - 1;
    } else {
        switch (in->colorspace) {
        case AVCOL_SPC_SMPTE170M:
        case AVCOL_SPC_BT470BG:
            s->cs = (s->depth - 8) * 2 + 0;
            break;
        case AVCOL_SPC_BT709:
        default:
            s->cs = (s->depth - 8) * 2 + 1;
        }
    }

    out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
    if (!out) {
        av_frame_free(&in);
        return AVERROR(ENOMEM);
    }
    av_frame_copy_props(out, in);

    s->vectorscope(s, in, out, s->pd);
    s->graticulef(s, out, s->x, s->y, s->pd, s->cs);

    for (plane = 0; plane < 4; plane++) {
        if (out->data[plane]) {
            out->data[plane]    += (s->size - 1) * out->linesize[plane];
            out->linesize[plane] = -out->linesize[plane];
        }
    }

    av_frame_free(&in);
    return ff_filter_frame(outlink, out);
}