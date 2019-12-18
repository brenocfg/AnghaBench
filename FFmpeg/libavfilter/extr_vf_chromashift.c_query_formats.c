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
struct TYPE_6__ {TYPE_1__* filter; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AV_PIX_FMT_GBRAP 175 
#define  AV_PIX_FMT_GBRAP10 174 
#define  AV_PIX_FMT_GBRAP12 173 
#define  AV_PIX_FMT_GBRAP16 172 
#define  AV_PIX_FMT_GBRP 171 
#define  AV_PIX_FMT_GBRP10 170 
#define  AV_PIX_FMT_GBRP12 169 
#define  AV_PIX_FMT_GBRP14 168 
#define  AV_PIX_FMT_GBRP16 167 
#define  AV_PIX_FMT_GBRP9 166 
#define  AV_PIX_FMT_NONE 165 
#define  AV_PIX_FMT_YUV410P 164 
#define  AV_PIX_FMT_YUV411P 163 
#define  AV_PIX_FMT_YUV420P 162 
#define  AV_PIX_FMT_YUV420P10 161 
#define  AV_PIX_FMT_YUV420P12 160 
#define  AV_PIX_FMT_YUV420P14 159 
#define  AV_PIX_FMT_YUV420P16 158 
#define  AV_PIX_FMT_YUV420P9 157 
#define  AV_PIX_FMT_YUV422P 156 
#define  AV_PIX_FMT_YUV422P10 155 
#define  AV_PIX_FMT_YUV422P12 154 
#define  AV_PIX_FMT_YUV422P14 153 
#define  AV_PIX_FMT_YUV422P16 152 
#define  AV_PIX_FMT_YUV422P9 151 
#define  AV_PIX_FMT_YUV440P 150 
#define  AV_PIX_FMT_YUV440P10 149 
#define  AV_PIX_FMT_YUV440P12 148 
#define  AV_PIX_FMT_YUV444P 147 
#define  AV_PIX_FMT_YUV444P10 146 
#define  AV_PIX_FMT_YUV444P12 145 
#define  AV_PIX_FMT_YUV444P14 144 
#define  AV_PIX_FMT_YUV444P16 143 
#define  AV_PIX_FMT_YUV444P9 142 
#define  AV_PIX_FMT_YUVA420P 141 
#define  AV_PIX_FMT_YUVA420P10 140 
#define  AV_PIX_FMT_YUVA420P16 139 
#define  AV_PIX_FMT_YUVA422P 138 
#define  AV_PIX_FMT_YUVA422P10 137 
#define  AV_PIX_FMT_YUVA422P16 136 
#define  AV_PIX_FMT_YUVA444P 135 
#define  AV_PIX_FMT_YUVA444P10 134 
#define  AV_PIX_FMT_YUVA444P16 133 
#define  AV_PIX_FMT_YUVJ411P 132 
#define  AV_PIX_FMT_YUVJ420P 131 
#define  AV_PIX_FMT_YUVJ422P 130 
#define  AV_PIX_FMT_YUVJ440P 129 
#define  AV_PIX_FMT_YUVJ444P 128 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/ * ff_make_format_list (int const*) ; 
 int ff_set_common_formats (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    static const enum AVPixelFormat yuv_pix_fmts[] = {
        AV_PIX_FMT_YUVA444P, AV_PIX_FMT_YUVA422P, AV_PIX_FMT_YUVA420P,
        AV_PIX_FMT_YUVJ444P, AV_PIX_FMT_YUVJ440P, AV_PIX_FMT_YUVJ422P,AV_PIX_FMT_YUVJ420P, AV_PIX_FMT_YUVJ411P,
        AV_PIX_FMT_YUV444P, AV_PIX_FMT_YUV440P, AV_PIX_FMT_YUV422P, AV_PIX_FMT_YUV420P, AV_PIX_FMT_YUV411P, AV_PIX_FMT_YUV410P,
        AV_PIX_FMT_YUV420P9, AV_PIX_FMT_YUV422P9, AV_PIX_FMT_YUV444P9,
        AV_PIX_FMT_YUV420P10, AV_PIX_FMT_YUV422P10, AV_PIX_FMT_YUV444P10, AV_PIX_FMT_YUV440P10,
        AV_PIX_FMT_YUVA420P10, AV_PIX_FMT_YUVA422P10, AV_PIX_FMT_YUVA444P10,
        AV_PIX_FMT_YUV420P12, AV_PIX_FMT_YUV422P12, AV_PIX_FMT_YUV444P12, AV_PIX_FMT_YUV440P12,
        AV_PIX_FMT_YUV444P14, AV_PIX_FMT_YUV422P14, AV_PIX_FMT_YUV420P14,
        AV_PIX_FMT_YUV420P16, AV_PIX_FMT_YUV422P16, AV_PIX_FMT_YUV444P16,
        AV_PIX_FMT_YUVA420P16, AV_PIX_FMT_YUVA422P16, AV_PIX_FMT_YUVA444P16,
        AV_PIX_FMT_NONE
    };
    static const enum AVPixelFormat rgb_pix_fmts[] = {
        AV_PIX_FMT_GBRP, AV_PIX_FMT_GBRAP, AV_PIX_FMT_GBRP9,
        AV_PIX_FMT_GBRP10, AV_PIX_FMT_GBRP12,
        AV_PIX_FMT_GBRP14, AV_PIX_FMT_GBRP16,
        AV_PIX_FMT_GBRAP10, AV_PIX_FMT_GBRAP12, AV_PIX_FMT_GBRAP16,
        AV_PIX_FMT_NONE
    };
    const enum AVPixelFormat *pix_fmts;
    AVFilterFormats *fmts_list;

    if (!strcmp(ctx->filter->name, "rgbashift"))
        pix_fmts = rgb_pix_fmts;
    else
        pix_fmts = yuv_pix_fmts;

    fmts_list = ff_make_format_list(pix_fmts);
    if (!fmts_list)
        return AVERROR(ENOMEM);
    return ff_set_common_formats(ctx, fmts_list);
}