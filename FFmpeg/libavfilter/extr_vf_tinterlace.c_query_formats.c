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
#define  AV_PIX_FMT_GRAY8 150 
#define  AV_PIX_FMT_NONE 149 
#define  AV_PIX_FMT_YUV410P 148 
#define  AV_PIX_FMT_YUV411P 147 
#define  AV_PIX_FMT_YUV420P 146 
#define  AV_PIX_FMT_YUV420P10LE 145 
#define  AV_PIX_FMT_YUV420P12LE 144 
#define  AV_PIX_FMT_YUV422P 143 
#define  AV_PIX_FMT_YUV422P10LE 142 
#define  AV_PIX_FMT_YUV422P12LE 141 
#define  AV_PIX_FMT_YUV440P 140 
#define  AV_PIX_FMT_YUV440P10LE 139 
#define  AV_PIX_FMT_YUV440P12LE 138 
#define  AV_PIX_FMT_YUV444P 137 
#define  AV_PIX_FMT_YUV444P10LE 136 
#define  AV_PIX_FMT_YUV444P12LE 135 
#define  AV_PIX_FMT_YUVA420P 134 
#define  AV_PIX_FMT_YUVA420P10LE 133 
#define  AV_PIX_FMT_YUVA422P 132 
#define  AV_PIX_FMT_YUVA422P10LE 131 
#define  AV_PIX_FMT_YUVA444P 130 
#define  AV_PIX_FMT_YUVA444P10LE 129 
 int /*<<< orphan*/  ENOMEM ; 
#define  FULL_SCALE_YUVJ_FORMATS 128 
 int /*<<< orphan*/ * ff_make_format_list (int const*) ; 
 int ff_set_common_formats (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    static const enum AVPixelFormat pix_fmts[] = {
        AV_PIX_FMT_YUV410P, AV_PIX_FMT_YUV411P,
        AV_PIX_FMT_YUV420P, AV_PIX_FMT_YUV422P,
        AV_PIX_FMT_YUV440P, AV_PIX_FMT_YUV444P,
        AV_PIX_FMT_YUV420P10LE, AV_PIX_FMT_YUV422P10LE,
        AV_PIX_FMT_YUV440P10LE, AV_PIX_FMT_YUV444P10LE,
        AV_PIX_FMT_YUV420P12LE, AV_PIX_FMT_YUV422P12LE,
        AV_PIX_FMT_YUV440P12LE, AV_PIX_FMT_YUV444P12LE,
        AV_PIX_FMT_YUVA420P, AV_PIX_FMT_YUVA422P, AV_PIX_FMT_YUVA444P,
        AV_PIX_FMT_YUVA420P10LE, AV_PIX_FMT_YUVA422P10LE, AV_PIX_FMT_YUVA444P10LE,
        AV_PIX_FMT_GRAY8, FULL_SCALE_YUVJ_FORMATS,
        AV_PIX_FMT_NONE
    };

    AVFilterFormats *fmts_list = ff_make_format_list(pix_fmts);
    if (!fmts_list)
        return AVERROR(ENOMEM);
    return ff_set_common_formats(ctx, fmts_list);
}