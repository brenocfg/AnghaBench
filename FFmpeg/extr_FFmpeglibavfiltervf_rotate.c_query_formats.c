#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AV_PIX_FMT_0BGR 162 
#define  AV_PIX_FMT_0RGB 161 
#define  AV_PIX_FMT_ABGR 160 
#define  AV_PIX_FMT_ARGB 159 
#define  AV_PIX_FMT_BGR0 158 
#define  AV_PIX_FMT_BGR24 157 
#define  AV_PIX_FMT_BGRA 156 
#define  AV_PIX_FMT_GBRAP 155 
#define  AV_PIX_FMT_GBRP 154 
#define  AV_PIX_FMT_GRAY8 153 
#define  AV_PIX_FMT_NONE 152 
#define  AV_PIX_FMT_RGB0 151 
#define  AV_PIX_FMT_RGB24 150 
#define  AV_PIX_FMT_RGBA 149 
#define  AV_PIX_FMT_YUV410P 148 
#define  AV_PIX_FMT_YUV420P 147 
#define  AV_PIX_FMT_YUV420P10LE 146 
#define  AV_PIX_FMT_YUV420P12LE 145 
#define  AV_PIX_FMT_YUV420P16LE 144 
#define  AV_PIX_FMT_YUV420P9LE 143 
#define  AV_PIX_FMT_YUV444P 142 
#define  AV_PIX_FMT_YUV444P10LE 141 
#define  AV_PIX_FMT_YUV444P12LE 140 
#define  AV_PIX_FMT_YUV444P16LE 139 
#define  AV_PIX_FMT_YUV444P9LE 138 
#define  AV_PIX_FMT_YUVA420P 137 
#define  AV_PIX_FMT_YUVA420P10LE 136 
#define  AV_PIX_FMT_YUVA420P16LE 135 
#define  AV_PIX_FMT_YUVA420P9LE 134 
#define  AV_PIX_FMT_YUVA444P 133 
#define  AV_PIX_FMT_YUVA444P10LE 132 
#define  AV_PIX_FMT_YUVA444P16LE 131 
#define  AV_PIX_FMT_YUVA444P9LE 130 
#define  AV_PIX_FMT_YUVJ420P 129 
#define  AV_PIX_FMT_YUVJ444P 128 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/ * ff_make_format_list (int const*) ; 
 int ff_set_common_formats (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    static const enum AVPixelFormat pix_fmts[] = {
        AV_PIX_FMT_GBRP,   AV_PIX_FMT_GBRAP,
        AV_PIX_FMT_ARGB,   AV_PIX_FMT_RGBA,
        AV_PIX_FMT_ABGR,   AV_PIX_FMT_BGRA,
        AV_PIX_FMT_0RGB,   AV_PIX_FMT_RGB0,
        AV_PIX_FMT_0BGR,   AV_PIX_FMT_BGR0,
        AV_PIX_FMT_RGB24,  AV_PIX_FMT_BGR24,
        AV_PIX_FMT_GRAY8,
        AV_PIX_FMT_YUV410P,
        AV_PIX_FMT_YUV444P,  AV_PIX_FMT_YUVJ444P,
        AV_PIX_FMT_YUV420P,  AV_PIX_FMT_YUVJ420P,
        AV_PIX_FMT_YUVA444P, AV_PIX_FMT_YUVA420P,
        AV_PIX_FMT_YUV420P10LE, AV_PIX_FMT_YUVA420P10LE,
        AV_PIX_FMT_YUV444P10LE, AV_PIX_FMT_YUVA444P10LE,
        AV_PIX_FMT_YUV420P12LE,
        AV_PIX_FMT_YUV444P12LE,
        AV_PIX_FMT_YUV444P16LE, AV_PIX_FMT_YUVA444P16LE,
        AV_PIX_FMT_YUV420P16LE, AV_PIX_FMT_YUVA420P16LE,
        AV_PIX_FMT_YUV444P9LE, AV_PIX_FMT_YUVA444P9LE,
        AV_PIX_FMT_YUV420P9LE, AV_PIX_FMT_YUVA420P9LE,
        AV_PIX_FMT_NONE
    };

    AVFilterFormats *fmts_list = ff_make_format_list(pix_fmts);
    if (!fmts_list)
        return AVERROR(ENOMEM);
    return ff_set_common_formats(ctx, fmts_list);
}