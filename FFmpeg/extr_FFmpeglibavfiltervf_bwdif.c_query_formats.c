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
#define  AV_PIX_FMT_GBRAP 176 
#define  AV_PIX_FMT_GBRAP16 175 
#define  AV_PIX_FMT_GBRP 174 
#define  AV_PIX_FMT_GBRP10 173 
#define  AV_PIX_FMT_GBRP12 172 
#define  AV_PIX_FMT_GBRP14 171 
#define  AV_PIX_FMT_GBRP16 170 
#define  AV_PIX_FMT_GBRP9 169 
#define  AV_PIX_FMT_GRAY16 168 
#define  AV_PIX_FMT_GRAY8 167 
#define  AV_PIX_FMT_NONE 166 
#define  AV_PIX_FMT_YUV410P 165 
#define  AV_PIX_FMT_YUV411P 164 
#define  AV_PIX_FMT_YUV420P 163 
#define  AV_PIX_FMT_YUV420P10 162 
#define  AV_PIX_FMT_YUV420P12 161 
#define  AV_PIX_FMT_YUV420P14 160 
#define  AV_PIX_FMT_YUV420P16 159 
#define  AV_PIX_FMT_YUV420P9 158 
#define  AV_PIX_FMT_YUV422P 157 
#define  AV_PIX_FMT_YUV422P10 156 
#define  AV_PIX_FMT_YUV422P12 155 
#define  AV_PIX_FMT_YUV422P14 154 
#define  AV_PIX_FMT_YUV422P16 153 
#define  AV_PIX_FMT_YUV422P9 152 
#define  AV_PIX_FMT_YUV440P 151 
#define  AV_PIX_FMT_YUV444P 150 
#define  AV_PIX_FMT_YUV444P10 149 
#define  AV_PIX_FMT_YUV444P12 148 
#define  AV_PIX_FMT_YUV444P14 147 
#define  AV_PIX_FMT_YUV444P16 146 
#define  AV_PIX_FMT_YUV444P9 145 
#define  AV_PIX_FMT_YUVA420P 144 
#define  AV_PIX_FMT_YUVA420P10 143 
#define  AV_PIX_FMT_YUVA420P16 142 
#define  AV_PIX_FMT_YUVA420P9 141 
#define  AV_PIX_FMT_YUVA422P 140 
#define  AV_PIX_FMT_YUVA422P10 139 
#define  AV_PIX_FMT_YUVA422P16 138 
#define  AV_PIX_FMT_YUVA422P9 137 
#define  AV_PIX_FMT_YUVA444P 136 
#define  AV_PIX_FMT_YUVA444P10 135 
#define  AV_PIX_FMT_YUVA444P16 134 
#define  AV_PIX_FMT_YUVA444P9 133 
#define  AV_PIX_FMT_YUVJ411P 132 
#define  AV_PIX_FMT_YUVJ420P 131 
#define  AV_PIX_FMT_YUVJ422P 130 
#define  AV_PIX_FMT_YUVJ440P 129 
#define  AV_PIX_FMT_YUVJ444P 128 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/ * ff_make_format_list (int const*) ; 
 int ff_set_common_formats (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    static const enum AVPixelFormat pix_fmts[] = {
        AV_PIX_FMT_YUV410P, AV_PIX_FMT_YUV411P, AV_PIX_FMT_YUV420P,
        AV_PIX_FMT_YUV422P, AV_PIX_FMT_YUV440P, AV_PIX_FMT_YUV444P,
        AV_PIX_FMT_YUVJ411P, AV_PIX_FMT_YUVJ420P,
        AV_PIX_FMT_YUVJ422P, AV_PIX_FMT_YUVJ440P, AV_PIX_FMT_YUVJ444P,
        AV_PIX_FMT_YUV420P9, AV_PIX_FMT_YUV422P9, AV_PIX_FMT_YUV444P9,
        AV_PIX_FMT_YUV420P10, AV_PIX_FMT_YUV422P10, AV_PIX_FMT_YUV444P10,
        AV_PIX_FMT_YUV420P12, AV_PIX_FMT_YUV422P12, AV_PIX_FMT_YUV444P12,
        AV_PIX_FMT_YUV420P14, AV_PIX_FMT_YUV422P14, AV_PIX_FMT_YUV444P14,
        AV_PIX_FMT_YUV420P16, AV_PIX_FMT_YUV422P16, AV_PIX_FMT_YUV444P16,
        AV_PIX_FMT_YUVA420P, AV_PIX_FMT_YUVA422P, AV_PIX_FMT_YUVA444P,
        AV_PIX_FMT_YUVA420P9, AV_PIX_FMT_YUVA422P9, AV_PIX_FMT_YUVA444P9,
        AV_PIX_FMT_YUVA420P10, AV_PIX_FMT_YUVA422P10, AV_PIX_FMT_YUVA444P10,
        AV_PIX_FMT_YUVA420P16, AV_PIX_FMT_YUVA422P16, AV_PIX_FMT_YUVA444P16,
        AV_PIX_FMT_GBRP, AV_PIX_FMT_GBRP9, AV_PIX_FMT_GBRP10,
        AV_PIX_FMT_GBRP12, AV_PIX_FMT_GBRP14, AV_PIX_FMT_GBRP16,
        AV_PIX_FMT_GBRAP, AV_PIX_FMT_GBRAP16,
        AV_PIX_FMT_GRAY8, AV_PIX_FMT_GRAY16,
        AV_PIX_FMT_NONE
    };

    AVFilterFormats *fmts_list = ff_make_format_list(pix_fmts);
    if (!fmts_list)
        return AVERROR(ENOMEM);

    return ff_set_common_formats(ctx, fmts_list);
}