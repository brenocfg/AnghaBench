#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_6__ {TYPE_1__* priv; } ;
struct TYPE_5__ {scalar_t__ is_rgb; } ;
typedef  TYPE_1__ GEQContext ;
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AV_PIX_FMT_GBRAP 178 
#define  AV_PIX_FMT_GBRAP10 177 
#define  AV_PIX_FMT_GBRAP12 176 
#define  AV_PIX_FMT_GBRAP16 175 
#define  AV_PIX_FMT_GBRP 174 
#define  AV_PIX_FMT_GBRP10 173 
#define  AV_PIX_FMT_GBRP12 172 
#define  AV_PIX_FMT_GBRP14 171 
#define  AV_PIX_FMT_GBRP16 170 
#define  AV_PIX_FMT_GBRP9 169 
#define  AV_PIX_FMT_GRAY10 168 
#define  AV_PIX_FMT_GRAY12 167 
#define  AV_PIX_FMT_GRAY14 166 
#define  AV_PIX_FMT_GRAY16 165 
#define  AV_PIX_FMT_GRAY8 164 
#define  AV_PIX_FMT_GRAY9 163 
#define  AV_PIX_FMT_NONE 162 
#define  AV_PIX_FMT_YUV410P 161 
#define  AV_PIX_FMT_YUV411P 160 
#define  AV_PIX_FMT_YUV420P 159 
#define  AV_PIX_FMT_YUV420P10 158 
#define  AV_PIX_FMT_YUV420P12 157 
#define  AV_PIX_FMT_YUV420P14 156 
#define  AV_PIX_FMT_YUV420P16 155 
#define  AV_PIX_FMT_YUV420P9 154 
#define  AV_PIX_FMT_YUV422P 153 
#define  AV_PIX_FMT_YUV422P10 152 
#define  AV_PIX_FMT_YUV422P12 151 
#define  AV_PIX_FMT_YUV422P14 150 
#define  AV_PIX_FMT_YUV422P16 149 
#define  AV_PIX_FMT_YUV422P9 148 
#define  AV_PIX_FMT_YUV440P 147 
#define  AV_PIX_FMT_YUV440P10 146 
#define  AV_PIX_FMT_YUV444P 145 
#define  AV_PIX_FMT_YUV444P10 144 
#define  AV_PIX_FMT_YUV444P12 143 
#define  AV_PIX_FMT_YUV444P14 142 
#define  AV_PIX_FMT_YUV444P16 141 
#define  AV_PIX_FMT_YUV444P9 140 
#define  AV_PIX_FMT_YUVA420P 139 
#define  AV_PIX_FMT_YUVA420P10 138 
#define  AV_PIX_FMT_YUVA420P16 137 
#define  AV_PIX_FMT_YUVA420P9 136 
#define  AV_PIX_FMT_YUVA422P 135 
#define  AV_PIX_FMT_YUVA422P10 134 
#define  AV_PIX_FMT_YUVA422P16 133 
#define  AV_PIX_FMT_YUVA422P9 132 
#define  AV_PIX_FMT_YUVA444P 131 
#define  AV_PIX_FMT_YUVA444P10 130 
#define  AV_PIX_FMT_YUVA444P16 129 
#define  AV_PIX_FMT_YUVA444P9 128 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/ * ff_make_format_list (int const*) ; 
 int ff_set_common_formats (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int geq_query_formats(AVFilterContext *ctx)
{
    GEQContext *geq = ctx->priv;
    static const enum AVPixelFormat yuv_pix_fmts[] = {
        AV_PIX_FMT_YUV444P,  AV_PIX_FMT_YUV422P,  AV_PIX_FMT_YUV420P,
        AV_PIX_FMT_YUV411P,  AV_PIX_FMT_YUV410P,  AV_PIX_FMT_YUV440P,
        AV_PIX_FMT_YUVA444P, AV_PIX_FMT_YUVA422P, AV_PIX_FMT_YUVA420P,
        AV_PIX_FMT_GRAY8,
        AV_PIX_FMT_YUV444P9,  AV_PIX_FMT_YUV422P9,  AV_PIX_FMT_YUV420P9,
        AV_PIX_FMT_YUVA444P9, AV_PIX_FMT_YUVA422P9, AV_PIX_FMT_YUVA420P9,
        AV_PIX_FMT_YUV444P10,  AV_PIX_FMT_YUV422P10,  AV_PIX_FMT_YUV420P10,
        AV_PIX_FMT_YUV440P10,
        AV_PIX_FMT_YUVA444P10, AV_PIX_FMT_YUVA422P10, AV_PIX_FMT_YUVA420P10,
        AV_PIX_FMT_GRAY9, AV_PIX_FMT_GRAY10,
        AV_PIX_FMT_YUV444P12,  AV_PIX_FMT_YUV422P12,  AV_PIX_FMT_YUV420P12,
        AV_PIX_FMT_GRAY12, AV_PIX_FMT_GRAY14,
        AV_PIX_FMT_YUV444P14,  AV_PIX_FMT_YUV422P14,  AV_PIX_FMT_YUV420P14,
        AV_PIX_FMT_YUV444P16,  AV_PIX_FMT_YUV422P16,  AV_PIX_FMT_YUV420P16,
        AV_PIX_FMT_YUVA444P16, AV_PIX_FMT_YUVA422P16, AV_PIX_FMT_YUVA420P16,
        AV_PIX_FMT_GRAY16,
        AV_PIX_FMT_NONE
    };
    static const enum AVPixelFormat rgb_pix_fmts[] = {
        AV_PIX_FMT_GBRP, AV_PIX_FMT_GBRAP,
        AV_PIX_FMT_GBRP9,
        AV_PIX_FMT_GBRP10, AV_PIX_FMT_GBRAP10,
        AV_PIX_FMT_GBRP12, AV_PIX_FMT_GBRAP12,
        AV_PIX_FMT_GBRP14,
        AV_PIX_FMT_GBRP16, AV_PIX_FMT_GBRAP16,
        AV_PIX_FMT_NONE
    };
    AVFilterFormats *fmts_list;

    if (geq->is_rgb) {
        fmts_list = ff_make_format_list(rgb_pix_fmts);
    } else
        fmts_list = ff_make_format_list(yuv_pix_fmts);
    if (!fmts_list)
        return AVERROR(ENOMEM);
    return ff_set_common_formats(ctx, fmts_list);
}