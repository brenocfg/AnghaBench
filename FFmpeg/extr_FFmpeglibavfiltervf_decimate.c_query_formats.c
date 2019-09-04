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
#define  AV_PIX_FMT_GRAY16 163 
#define  AV_PIX_FMT_GRAY8 162 
#define  AV_PIX_FMT_NONE 161 
#define  AV_PIX_FMT_YUV410P 160 
#define  AV_PIX_FMT_YUV411P 159 
#define  AV_PIX_FMT_YUV420P 158 
#define  AV_PIX_FMT_YUV420P10 157 
#define  AV_PIX_FMT_YUV420P12 156 
#define  AV_PIX_FMT_YUV420P14 155 
#define  AV_PIX_FMT_YUV420P16 154 
#define  AV_PIX_FMT_YUV420P9 153 
#define  AV_PIX_FMT_YUV422P 152 
#define  AV_PIX_FMT_YUV422P10 151 
#define  AV_PIX_FMT_YUV422P12 150 
#define  AV_PIX_FMT_YUV422P14 149 
#define  AV_PIX_FMT_YUV422P16 148 
#define  AV_PIX_FMT_YUV422P9 147 
#define  AV_PIX_FMT_YUV440P 146 
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
 int ff_set_common_formats (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    static const enum AVPixelFormat pix_fmts[] = {
#define PF_NOALPHA(suf) AV_PIX_FMT_YUV420##suf,  AV_PIX_FMT_YUV422##suf,  AV_PIX_FMT_YUV444##suf
#define PF_ALPHA(suf)   AV_PIX_FMT_YUVA420##suf, AV_PIX_FMT_YUVA422##suf, AV_PIX_FMT_YUVA444##suf
#define PF(suf)         PF_NOALPHA(suf), PF_ALPHA(suf)
        PF(P), PF(P9), PF(P10), PF_NOALPHA(P12), PF_NOALPHA(P14), PF(P16),
        AV_PIX_FMT_YUV440P, AV_PIX_FMT_YUV411P, AV_PIX_FMT_YUV410P,
        AV_PIX_FMT_GRAY8, AV_PIX_FMT_GRAY16,
        AV_PIX_FMT_NONE
    };
    AVFilterFormats *fmts_list = ff_make_format_list(pix_fmts);
    if (!fmts_list)
        return AVERROR(ENOMEM);
    return ff_set_common_formats(ctx, fmts_list);
}