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
#define  AV_PIX_FMT_YUV420P 148 
#define  AV_PIX_FMT_YUV420P10 147 
#define  AV_PIX_FMT_YUV420P12 146 
#define  AV_PIX_FMT_YUV420P14 145 
#define  AV_PIX_FMT_YUV420P16 144 
#define  AV_PIX_FMT_YUV420P9 143 
#define  AV_PIX_FMT_YUV422P 142 
#define  AV_PIX_FMT_YUV422P10 141 
#define  AV_PIX_FMT_YUV422P12 140 
#define  AV_PIX_FMT_YUV422P14 139 
#define  AV_PIX_FMT_YUV422P16 138 
#define  AV_PIX_FMT_YUV422P9 137 
#define  AV_PIX_FMT_YUV444P 136 
#define  AV_PIX_FMT_YUV444P10 135 
#define  AV_PIX_FMT_YUV444P12 134 
#define  AV_PIX_FMT_YUV444P14 133 
#define  AV_PIX_FMT_YUV444P16 132 
#define  AV_PIX_FMT_YUV444P9 131 
#define  AV_PIX_FMT_YUVJ420P 130 
#define  AV_PIX_FMT_YUVJ422P 129 
#define  AV_PIX_FMT_YUVJ444P 128 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/ * ff_make_format_list (int const*) ; 
 int ff_set_common_formats (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    static const enum AVPixelFormat pixel_fmts_fftfilt[] = {
        AV_PIX_FMT_GRAY8,
        AV_PIX_FMT_YUV444P, AV_PIX_FMT_YUVJ444P,
        AV_PIX_FMT_YUV420P, AV_PIX_FMT_YUVJ420P,
        AV_PIX_FMT_YUV422P, AV_PIX_FMT_YUVJ422P,
        AV_PIX_FMT_YUV420P9, AV_PIX_FMT_YUV420P10,
        AV_PIX_FMT_YUV420P12, AV_PIX_FMT_YUV420P14,
        AV_PIX_FMT_YUV420P16,
        AV_PIX_FMT_YUV422P9, AV_PIX_FMT_YUV422P10,
        AV_PIX_FMT_YUV422P12, AV_PIX_FMT_YUV422P14,
        AV_PIX_FMT_YUV422P16,
        AV_PIX_FMT_YUV444P9, AV_PIX_FMT_YUV444P10,
        AV_PIX_FMT_YUV444P12, AV_PIX_FMT_YUV444P14,
        AV_PIX_FMT_YUV444P16,
        AV_PIX_FMT_NONE
    };

    AVFilterFormats *fmts_list = ff_make_format_list(pixel_fmts_fftfilt);
    if (!fmts_list)
        return AVERROR(ENOMEM);
    return ff_set_common_formats(ctx, fmts_list);
}