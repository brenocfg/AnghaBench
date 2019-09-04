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
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_14__ {TYPE_3__** outputs; TYPE_1__** inputs; } ;
struct TYPE_13__ {int nb_formats; int /*<<< orphan*/ * formats; } ;
struct TYPE_12__ {int flags; TYPE_2__* comp; } ;
struct TYPE_11__ {int /*<<< orphan*/  in_formats; } ;
struct TYPE_10__ {int depth; } ;
struct TYPE_9__ {TYPE_5__* in_formats; int /*<<< orphan*/  out_formats; } ;
typedef  TYPE_4__ AVPixFmtDescriptor ;
typedef  TYPE_5__ AVFilterFormats ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_PIX_FMT_FLAG_RGB ; 
 int /*<<< orphan*/  EAGAIN ; 
 TYPE_4__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int ff_formats_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_make_format_list (int const*) ; 
 int const* levels_in_pix_fmts ; 
 int* levels_out_rgb10_pix_fmts ; 
 int* levels_out_rgb12_pix_fmts ; 
 int* levels_out_rgb8_pix_fmts ; 
 int* levels_out_rgb9_pix_fmts ; 
 int* levels_out_yuv10_pix_fmts ; 
 int* levels_out_yuv12_pix_fmts ; 
 int* levels_out_yuv8_pix_fmts ; 
 int* levels_out_yuv9_pix_fmts ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    AVFilterFormats *avff;
    const AVPixFmtDescriptor *desc;
    const enum AVPixelFormat *out_pix_fmts;
    int rgb, i, bits;
    int ret;

    if (!ctx->inputs[0]->in_formats ||
        !ctx->inputs[0]->in_formats->nb_formats) {
        return AVERROR(EAGAIN);
    }

    if (!ctx->inputs[0]->out_formats)
        if ((ret = ff_formats_ref(ff_make_format_list(levels_in_pix_fmts), &ctx->inputs[0]->out_formats)) < 0)
            return ret;
    avff = ctx->inputs[0]->in_formats;
    desc = av_pix_fmt_desc_get(avff->formats[0]);
    rgb = desc->flags & AV_PIX_FMT_FLAG_RGB;
    bits = desc->comp[0].depth;
    for (i = 1; i < avff->nb_formats; i++) {
        desc = av_pix_fmt_desc_get(avff->formats[i]);
        if ((rgb != (desc->flags & AV_PIX_FMT_FLAG_RGB)) ||
            (bits != desc->comp[0].depth))
            return AVERROR(EAGAIN);
    }

    if (rgb && bits == 8)
        out_pix_fmts = levels_out_rgb8_pix_fmts;
    else if (rgb && bits == 9)
        out_pix_fmts = levels_out_rgb9_pix_fmts;
    else if (rgb && bits == 10)
        out_pix_fmts = levels_out_rgb10_pix_fmts;
    else if (rgb && bits == 12)
        out_pix_fmts = levels_out_rgb12_pix_fmts;
    else if (bits == 8)
        out_pix_fmts = levels_out_yuv8_pix_fmts;
    else if (bits == 9)
        out_pix_fmts = levels_out_yuv9_pix_fmts;
    else if (bits == 10)
        out_pix_fmts = levels_out_yuv10_pix_fmts;
    else if (bits == 12)
        out_pix_fmts = levels_out_yuv12_pix_fmts;
    else
        return AVERROR(EAGAIN);
    if ((ret = ff_formats_ref(ff_make_format_list(out_pix_fmts), &ctx->outputs[0]->in_formats)) < 0)
        return ret;

    return 0;
}