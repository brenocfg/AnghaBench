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
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_14__ {int filter; } ;
typedef  TYPE_4__ WaveformContext ;
struct TYPE_17__ {TYPE_3__** outputs; TYPE_1__** inputs; TYPE_4__* priv; } ;
struct TYPE_16__ {int nb_formats; int /*<<< orphan*/ * formats; } ;
struct TYPE_15__ {int nb_components; int flags; TYPE_2__* comp; } ;
struct TYPE_13__ {TYPE_6__* in_formats; } ;
struct TYPE_12__ {int depth; } ;
struct TYPE_11__ {TYPE_6__* out_formats; TYPE_6__* in_formats; } ;
typedef  TYPE_5__ AVPixFmtDescriptor ;
typedef  TYPE_6__ AVFilterFormats ;
typedef  TYPE_7__ AVFilterContext ;

/* Variables and functions */
#define  ACOLOR 135 
#define  AFLAT 134 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_BUG ; 
 int AV_PIX_FMT_FLAG_RGB ; 
#define  CHROMA 133 
#define  COLOR 132 
 int /*<<< orphan*/  EAGAIN ; 
#define  FLAT 131 
#define  LOWPASS 130 
#define  XFLAT 129 
#define  YFLAT 128 
 TYPE_5__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int ff_formats_ref (int /*<<< orphan*/ ,TYPE_6__**) ; 
 int /*<<< orphan*/  ff_make_format_list (int const*) ; 
 int* in_color_pix_fmts ; 
 int* in_flat_pix_fmts ; 
 int* in_lowpass_pix_fmts ; 
 int* out_gray10_lowpass_pix_fmts ; 
 int* out_gray12_lowpass_pix_fmts ; 
 int* out_gray8_lowpass_pix_fmts ; 
 int* out_gray9_lowpass_pix_fmts ; 
 int* out_rgb10_lowpass_pix_fmts ; 
 int* out_rgb12_lowpass_pix_fmts ; 
 int* out_rgb8_lowpass_pix_fmts ; 
 int* out_rgb9_lowpass_pix_fmts ; 
 int* out_yuv10_lowpass_pix_fmts ; 
 int* out_yuv12_lowpass_pix_fmts ; 
 int* out_yuv8_lowpass_pix_fmts ; 
 int* out_yuv9_lowpass_pix_fmts ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    WaveformContext *s = ctx->priv;
    const enum AVPixelFormat *out_pix_fmts;
    const enum AVPixelFormat *in_pix_fmts;
    const AVPixFmtDescriptor *desc, *desc2;
    AVFilterFormats *avff, *avff2;
    int depth, depth2, rgb, i, ret, ncomp, ncomp2;

    if (!ctx->inputs[0]->in_formats ||
        !ctx->inputs[0]->in_formats->nb_formats) {
        return AVERROR(EAGAIN);
    }

    switch (s->filter) {
    case LOWPASS: in_pix_fmts = in_lowpass_pix_fmts; break;
    case CHROMA:
    case XFLAT:
    case YFLAT:
    case AFLAT:
    case FLAT:    in_pix_fmts = in_flat_pix_fmts;    break;
    case ACOLOR:
    case COLOR:   in_pix_fmts = in_color_pix_fmts;   break;
    default: return AVERROR_BUG;
    }

    if (!ctx->inputs[0]->out_formats) {
        if ((ret = ff_formats_ref(ff_make_format_list(in_pix_fmts), &ctx->inputs[0]->out_formats)) < 0)
            return ret;
    }

    avff = ctx->inputs[0]->in_formats;
    avff2 = ctx->inputs[0]->out_formats;
    desc = av_pix_fmt_desc_get(avff->formats[0]);
    desc2 = av_pix_fmt_desc_get(avff2->formats[0]);
    ncomp = desc->nb_components;
    ncomp2 = desc2->nb_components;
    rgb = desc->flags & AV_PIX_FMT_FLAG_RGB;
    depth = desc->comp[0].depth;
    depth2 = desc2->comp[0].depth;
    if (ncomp != ncomp2 || depth != depth2)
        return AVERROR(EAGAIN);
    for (i = 1; i < avff->nb_formats; i++) {
        desc = av_pix_fmt_desc_get(avff->formats[i]);
        if (rgb != (desc->flags & AV_PIX_FMT_FLAG_RGB) ||
            depth != desc->comp[0].depth)
            return AVERROR(EAGAIN);
    }

    if (s->filter == LOWPASS && ncomp == 1 && depth == 8)
        out_pix_fmts = out_gray8_lowpass_pix_fmts;
    else if (s->filter == LOWPASS && ncomp == 1 && depth == 9)
        out_pix_fmts = out_gray9_lowpass_pix_fmts;
    else if (s->filter == LOWPASS && ncomp == 1 && depth == 10)
        out_pix_fmts = out_gray10_lowpass_pix_fmts;
    else if (s->filter == LOWPASS && ncomp == 1 && depth == 12)
        out_pix_fmts = out_gray12_lowpass_pix_fmts;
    else if (rgb && depth == 8 && ncomp > 2)
        out_pix_fmts = out_rgb8_lowpass_pix_fmts;
    else if (rgb && depth == 9 && ncomp > 2)
        out_pix_fmts = out_rgb9_lowpass_pix_fmts;
    else if (rgb && depth == 10 && ncomp > 2)
        out_pix_fmts = out_rgb10_lowpass_pix_fmts;
    else if (rgb && depth == 12 && ncomp > 2)
        out_pix_fmts = out_rgb12_lowpass_pix_fmts;
    else if (depth == 8 && ncomp > 2)
        out_pix_fmts = out_yuv8_lowpass_pix_fmts;
    else if (depth == 9 && ncomp > 2)
        out_pix_fmts = out_yuv9_lowpass_pix_fmts;
    else if (depth == 10 && ncomp > 2)
        out_pix_fmts = out_yuv10_lowpass_pix_fmts;
    else if (depth == 12 && ncomp > 2)
        out_pix_fmts = out_yuv12_lowpass_pix_fmts;
    else
        return AVERROR(EAGAIN);
    if ((ret = ff_formats_ref(ff_make_format_list(out_pix_fmts), &ctx->outputs[0]->in_formats)) < 0)
        return ret;

    return 0;
}