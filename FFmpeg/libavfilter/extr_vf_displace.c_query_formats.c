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
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
#define  AV_PIX_FMT_0BGR 155 
#define  AV_PIX_FMT_0RGB 154 
#define  AV_PIX_FMT_ABGR 153 
#define  AV_PIX_FMT_ARGB 152 
#define  AV_PIX_FMT_BGR0 151 
#define  AV_PIX_FMT_BGR24 150 
#define  AV_PIX_FMT_BGRA 149 
#define  AV_PIX_FMT_GBRAP 148 
#define  AV_PIX_FMT_GBRP 147 
#define  AV_PIX_FMT_GRAY8 146 
#define  AV_PIX_FMT_NONE 145 
#define  AV_PIX_FMT_RGB0 144 
#define  AV_PIX_FMT_RGB24 143 
#define  AV_PIX_FMT_RGBA 142 
#define  AV_PIX_FMT_YUV410P 141 
#define  AV_PIX_FMT_YUV411P 140 
#define  AV_PIX_FMT_YUV420P 139 
#define  AV_PIX_FMT_YUV422P 138 
#define  AV_PIX_FMT_YUV440P 137 
#define  AV_PIX_FMT_YUV444P 136 
#define  AV_PIX_FMT_YUVA420P 135 
#define  AV_PIX_FMT_YUVA422P 134 
#define  AV_PIX_FMT_YUVA444P 133 
#define  AV_PIX_FMT_YUVJ411P 132 
#define  AV_PIX_FMT_YUVJ420P 131 
#define  AV_PIX_FMT_YUVJ422P 130 
#define  AV_PIX_FMT_YUVJ440P 129 
#define  AV_PIX_FMT_YUVJ444P 128 
 int /*<<< orphan*/  ff_make_format_list (int const*) ; 
 int ff_set_common_formats (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    static const enum AVPixelFormat pix_fmts[] = {
        AV_PIX_FMT_YUVA444P, AV_PIX_FMT_YUV444P, AV_PIX_FMT_YUV440P,
        AV_PIX_FMT_YUVJ444P, AV_PIX_FMT_YUVJ440P,
        AV_PIX_FMT_YUVA422P, AV_PIX_FMT_YUV422P, AV_PIX_FMT_YUVA420P, AV_PIX_FMT_YUV420P,
        AV_PIX_FMT_YUVJ422P, AV_PIX_FMT_YUVJ420P,
        AV_PIX_FMT_YUVJ411P, AV_PIX_FMT_YUV411P, AV_PIX_FMT_YUV410P,
        AV_PIX_FMT_RGB24, AV_PIX_FMT_BGR24,
        AV_PIX_FMT_ARGB, AV_PIX_FMT_ABGR, AV_PIX_FMT_RGBA, AV_PIX_FMT_BGRA,
        AV_PIX_FMT_0RGB, AV_PIX_FMT_0BGR, AV_PIX_FMT_RGB0, AV_PIX_FMT_BGR0,
        AV_PIX_FMT_GBRP, AV_PIX_FMT_GBRAP,
        AV_PIX_FMT_GRAY8, AV_PIX_FMT_NONE
    };

    return ff_set_common_formats(ctx, ff_make_format_list(pix_fmts));
}