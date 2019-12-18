#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_14__ {TYPE_2__** outputs; TYPE_1__** inputs; TYPE_3__* priv; } ;
struct TYPE_13__ {struct TYPE_13__* formats; } ;
struct TYPE_12__ {scalar_t__ format; } ;
struct TYPE_11__ {int /*<<< orphan*/  in_formats; } ;
struct TYPE_10__ {int /*<<< orphan*/  out_formats; } ;
typedef  TYPE_3__ RemapContext ;
typedef  TYPE_4__ AVFilterFormats ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AV_PIX_FMT_ABGR 165 
#define  AV_PIX_FMT_ARGB 164 
#define  AV_PIX_FMT_BGR24 163 
#define  AV_PIX_FMT_BGR48 162 
#define  AV_PIX_FMT_BGRA 161 
#define  AV_PIX_FMT_BGRA64 160 
#define  AV_PIX_FMT_GBRAP 159 
#define  AV_PIX_FMT_GBRAP10 158 
#define  AV_PIX_FMT_GBRAP12 157 
#define  AV_PIX_FMT_GBRAP16 156 
#define  AV_PIX_FMT_GBRP 155 
#define  AV_PIX_FMT_GBRP10 154 
#define  AV_PIX_FMT_GBRP12 153 
#define  AV_PIX_FMT_GBRP14 152 
#define  AV_PIX_FMT_GBRP16 151 
#define  AV_PIX_FMT_GBRP9 150 
#define  AV_PIX_FMT_GRAY10 149 
#define  AV_PIX_FMT_GRAY12 148 
#define  AV_PIX_FMT_GRAY14 147 
#define  AV_PIX_FMT_GRAY16 146 
#define  AV_PIX_FMT_GRAY8 145 
#define  AV_PIX_FMT_GRAY9 144 
#define  AV_PIX_FMT_NONE 143 
#define  AV_PIX_FMT_RGB24 142 
#define  AV_PIX_FMT_RGB48 141 
#define  AV_PIX_FMT_RGBA 140 
#define  AV_PIX_FMT_RGBA64 139 
#define  AV_PIX_FMT_YUV444P 138 
#define  AV_PIX_FMT_YUV444P10 137 
#define  AV_PIX_FMT_YUV444P12 136 
#define  AV_PIX_FMT_YUV444P14 135 
#define  AV_PIX_FMT_YUV444P16 134 
#define  AV_PIX_FMT_YUV444P9 133 
#define  AV_PIX_FMT_YUVA444P 132 
#define  AV_PIX_FMT_YUVA444P10 131 
#define  AV_PIX_FMT_YUVA444P16 130 
#define  AV_PIX_FMT_YUVA444P9 129 
#define  AV_PIX_FMT_YUVJ444P 128 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_freep (TYPE_4__**) ; 
 int ff_formats_ref (TYPE_4__*,int /*<<< orphan*/ *) ; 
 TYPE_4__* ff_make_format_list (int const*) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    RemapContext *s = ctx->priv;
    static const enum AVPixelFormat pix_fmts[] = {
        AV_PIX_FMT_YUVA444P,
        AV_PIX_FMT_YUV444P,
        AV_PIX_FMT_YUVJ444P,
        AV_PIX_FMT_RGB24, AV_PIX_FMT_BGR24,
        AV_PIX_FMT_ARGB, AV_PIX_FMT_ABGR, AV_PIX_FMT_RGBA, AV_PIX_FMT_BGRA,
        AV_PIX_FMT_GBRP, AV_PIX_FMT_GBRAP,
        AV_PIX_FMT_YUV444P9, AV_PIX_FMT_YUV444P10, AV_PIX_FMT_YUV444P12,
        AV_PIX_FMT_YUV444P14, AV_PIX_FMT_YUV444P16,
        AV_PIX_FMT_YUVA444P9, AV_PIX_FMT_YUVA444P10, AV_PIX_FMT_YUVA444P16,
        AV_PIX_FMT_GBRP9, AV_PIX_FMT_GBRP10, AV_PIX_FMT_GBRP12,
        AV_PIX_FMT_GBRP14, AV_PIX_FMT_GBRP16,
        AV_PIX_FMT_GBRAP10, AV_PIX_FMT_GBRAP12, AV_PIX_FMT_GBRAP16,
        AV_PIX_FMT_RGB48, AV_PIX_FMT_BGR48,
        AV_PIX_FMT_RGBA64, AV_PIX_FMT_BGRA64,
        AV_PIX_FMT_NONE
    };
    static const enum AVPixelFormat gray_pix_fmts[] = {
        AV_PIX_FMT_GRAY8, AV_PIX_FMT_GRAY9,
        AV_PIX_FMT_GRAY10, AV_PIX_FMT_GRAY12,
        AV_PIX_FMT_GRAY14, AV_PIX_FMT_GRAY16,
        AV_PIX_FMT_NONE
    };
    static const enum AVPixelFormat map_fmts[] = {
        AV_PIX_FMT_GRAY16,
        AV_PIX_FMT_NONE
    };
    AVFilterFormats *pix_formats = NULL, *map_formats = NULL;
    int ret;

    if (!(pix_formats = ff_make_format_list(s->format ? gray_pix_fmts : pix_fmts)) ||
        !(map_formats = ff_make_format_list(map_fmts))) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }
    if ((ret = ff_formats_ref(pix_formats, &ctx->inputs[0]->out_formats)) < 0 ||
        (ret = ff_formats_ref(map_formats, &ctx->inputs[1]->out_formats)) < 0 ||
        (ret = ff_formats_ref(map_formats, &ctx->inputs[2]->out_formats)) < 0 ||
        (ret = ff_formats_ref(pix_formats, &ctx->outputs[0]->in_formats)) < 0)
        goto fail;
    return 0;
fail:
    if (pix_formats)
        av_freep(&pix_formats->formats);
    av_freep(&pix_formats);
    if (map_formats)
        av_freep(&map_formats->formats);
    av_freep(&map_formats);
    return ret;
}