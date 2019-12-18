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
#define  AV_PIX_FMT_NONE 144 
#define  AV_PIX_FMT_YUV410P 143 
#define  AV_PIX_FMT_YUV411P 142 
#define  AV_PIX_FMT_YUV420P 141 
#define  AV_PIX_FMT_YUV420P10 140 
#define  AV_PIX_FMT_YUV422P 139 
#define  AV_PIX_FMT_YUV422P10 138 
#define  AV_PIX_FMT_YUV440P 137 
#define  AV_PIX_FMT_YUV440P10 136 
#define  AV_PIX_FMT_YUV444P 135 
#define  AV_PIX_FMT_YUV444P10 134 
#define  AV_PIX_FMT_YUVA420P 133 
#define  AV_PIX_FMT_YUVA420P10 132 
#define  AV_PIX_FMT_YUVA422P 131 
#define  AV_PIX_FMT_YUVA422P10 130 
#define  AV_PIX_FMT_YUVA444P 129 
#define  AV_PIX_FMT_YUVA444P10 128 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/ * ff_make_format_list (int const*) ; 
 int ff_set_common_formats (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    static const enum AVPixelFormat pix_fmts[] = {
        AV_PIX_FMT_YUV444P,      AV_PIX_FMT_YUV422P,
        AV_PIX_FMT_YUV420P,      AV_PIX_FMT_YUV411P,
        AV_PIX_FMT_YUV410P,      AV_PIX_FMT_YUV440P,
        AV_PIX_FMT_YUVA444P,     AV_PIX_FMT_YUVA422P,
        AV_PIX_FMT_YUVA420P,
        AV_PIX_FMT_YUV444P10,      AV_PIX_FMT_YUV422P10,
        AV_PIX_FMT_YUV420P10,
        AV_PIX_FMT_YUV440P10,
        AV_PIX_FMT_YUVA444P10,     AV_PIX_FMT_YUVA422P10,
        AV_PIX_FMT_YUVA420P10,
        AV_PIX_FMT_NONE
    };
    AVFilterFormats *fmts_list = ff_make_format_list(pix_fmts);
    if (!fmts_list)
        return AVERROR(ENOMEM);
    return ff_set_common_formats(ctx, fmts_list);
}