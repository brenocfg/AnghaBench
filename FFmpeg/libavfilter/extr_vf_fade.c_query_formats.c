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
struct TYPE_5__ {scalar_t__ black_fade; scalar_t__ alpha; } ;
typedef  TYPE_1__ FadeContext ;
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AV_PIX_FMT_ABGR 147 
#define  AV_PIX_FMT_ARGB 146 
#define  AV_PIX_FMT_BGR24 145 
#define  AV_PIX_FMT_BGRA 144 
#define  AV_PIX_FMT_NONE 143 
#define  AV_PIX_FMT_RGB24 142 
#define  AV_PIX_FMT_RGBA 141 
#define  AV_PIX_FMT_YUV410P 140 
#define  AV_PIX_FMT_YUV411P 139 
#define  AV_PIX_FMT_YUV420P 138 
#define  AV_PIX_FMT_YUV422P 137 
#define  AV_PIX_FMT_YUV440P 136 
#define  AV_PIX_FMT_YUV444P 135 
#define  AV_PIX_FMT_YUVA420P 134 
#define  AV_PIX_FMT_YUVA422P 133 
#define  AV_PIX_FMT_YUVA444P 132 
#define  AV_PIX_FMT_YUVJ420P 131 
#define  AV_PIX_FMT_YUVJ422P 130 
#define  AV_PIX_FMT_YUVJ440P 129 
#define  AV_PIX_FMT_YUVJ444P 128 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/ * ff_make_format_list (int const*) ; 
 int ff_set_common_formats (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    const FadeContext *s = ctx->priv;
    static const enum AVPixelFormat pix_fmts[] = {
        AV_PIX_FMT_YUV444P,  AV_PIX_FMT_YUV422P,  AV_PIX_FMT_YUV420P,
        AV_PIX_FMT_YUV411P,  AV_PIX_FMT_YUV410P,
        AV_PIX_FMT_YUVJ444P, AV_PIX_FMT_YUVJ422P, AV_PIX_FMT_YUVJ420P,
        AV_PIX_FMT_YUV440P,  AV_PIX_FMT_YUVJ440P,
        AV_PIX_FMT_YUVA420P, AV_PIX_FMT_YUVA422P, AV_PIX_FMT_YUVA444P,
        AV_PIX_FMT_RGB24,    AV_PIX_FMT_BGR24,
        AV_PIX_FMT_ARGB,     AV_PIX_FMT_ABGR,
        AV_PIX_FMT_RGBA,     AV_PIX_FMT_BGRA,
        AV_PIX_FMT_NONE
    };
    static const enum AVPixelFormat pix_fmts_rgb[] = {
        AV_PIX_FMT_RGB24,    AV_PIX_FMT_BGR24,
        AV_PIX_FMT_ARGB,     AV_PIX_FMT_ABGR,
        AV_PIX_FMT_RGBA,     AV_PIX_FMT_BGRA,
        AV_PIX_FMT_NONE
    };
    static const enum AVPixelFormat pix_fmts_alpha[] = {
        AV_PIX_FMT_YUVA420P, AV_PIX_FMT_YUVA422P, AV_PIX_FMT_YUVA444P,
        AV_PIX_FMT_ARGB,     AV_PIX_FMT_ABGR,
        AV_PIX_FMT_RGBA,     AV_PIX_FMT_BGRA,
        AV_PIX_FMT_NONE
    };
    static const enum AVPixelFormat pix_fmts_rgba[] = {
        AV_PIX_FMT_ARGB,     AV_PIX_FMT_ABGR,
        AV_PIX_FMT_RGBA,     AV_PIX_FMT_BGRA,
        AV_PIX_FMT_NONE
    };
    AVFilterFormats *fmts_list;

    if (s->alpha) {
        if (s->black_fade)
            fmts_list = ff_make_format_list(pix_fmts_alpha);
        else
            fmts_list = ff_make_format_list(pix_fmts_rgba);
    } else {
        if (s->black_fade)
            fmts_list = ff_make_format_list(pix_fmts);
        else
            fmts_list = ff_make_format_list(pix_fmts_rgb);
    }
    if (!fmts_list)
        return AVERROR(ENOMEM);
    return ff_set_common_formats(ctx, fmts_list);
}