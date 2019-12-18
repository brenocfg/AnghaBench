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
#define  AV_PIX_FMT_GBRAP 186 
#define  AV_PIX_FMT_GBRAP10 185 
#define  AV_PIX_FMT_GBRAP12 184 
#define  AV_PIX_FMT_GBRAP16 183 
#define  AV_PIX_FMT_GBRP 182 
#define  AV_PIX_FMT_GBRP10 181 
#define  AV_PIX_FMT_GBRP12 180 
#define  AV_PIX_FMT_GBRP14 179 
#define  AV_PIX_FMT_GBRP16 178 
#define  AV_PIX_FMT_GBRP9 177 
#define  AV_PIX_FMT_GRAY10 176 
#define  AV_PIX_FMT_GRAY12 175 
#define  AV_PIX_FMT_GRAY14 174 
#define  AV_PIX_FMT_GRAY16 173 
#define  AV_PIX_FMT_GRAY8 172 
#define  AV_PIX_FMT_GRAY9 171 
#define  AV_PIX_FMT_NONE 170 
#define  AV_PIX_FMT_YUV410P 169 
#define  AV_PIX_FMT_YUV411P 168 
#define  AV_PIX_FMT_YUV420P 167 
#define  AV_PIX_FMT_YUV420P10 166 
#define  AV_PIX_FMT_YUV420P12 165 
#define  AV_PIX_FMT_YUV420P14 164 
#define  AV_PIX_FMT_YUV420P16 163 
#define  AV_PIX_FMT_YUV420P9 162 
#define  AV_PIX_FMT_YUV422P 161 
#define  AV_PIX_FMT_YUV422P10 160 
#define  AV_PIX_FMT_YUV422P12 159 
#define  AV_PIX_FMT_YUV422P14 158 
#define  AV_PIX_FMT_YUV422P16 157 
#define  AV_PIX_FMT_YUV422P9 156 
#define  AV_PIX_FMT_YUV440P 155 
#define  AV_PIX_FMT_YUV440P10 154 
#define  AV_PIX_FMT_YUV440P12 153 
#define  AV_PIX_FMT_YUV444P 152 
#define  AV_PIX_FMT_YUV444P10 151 
#define  AV_PIX_FMT_YUV444P12 150 
#define  AV_PIX_FMT_YUV444P14 149 
#define  AV_PIX_FMT_YUV444P16 148 
#define  AV_PIX_FMT_YUV444P9 147 
#define  AV_PIX_FMT_YUVA420P 146 
#define  AV_PIX_FMT_YUVA420P10 145 
#define  AV_PIX_FMT_YUVA420P16 144 
#define  AV_PIX_FMT_YUVA420P9 143 
#define  AV_PIX_FMT_YUVA422P 142 
#define  AV_PIX_FMT_YUVA422P10 141 
#define  AV_PIX_FMT_YUVA422P12 140 
#define  AV_PIX_FMT_YUVA422P16 139 
#define  AV_PIX_FMT_YUVA422P9 138 
#define  AV_PIX_FMT_YUVA444P 137 
#define  AV_PIX_FMT_YUVA444P10 136 
#define  AV_PIX_FMT_YUVA444P12 135 
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
        // YUVA444
        AV_PIX_FMT_YUVA444P,   AV_PIX_FMT_YUVA444P9,
        AV_PIX_FMT_YUVA444P10, AV_PIX_FMT_YUVA444P12,
        AV_PIX_FMT_YUVA444P16,

        // YUVA422
        AV_PIX_FMT_YUVA422P,   AV_PIX_FMT_YUVA422P9,
        AV_PIX_FMT_YUVA422P10, AV_PIX_FMT_YUVA422P12,
        AV_PIX_FMT_YUVA422P16,

        // YUVA420
        AV_PIX_FMT_YUVA420P,   AV_PIX_FMT_YUVA420P9,
        AV_PIX_FMT_YUVA420P10, AV_PIX_FMT_YUVA420P16,

        // YUVJ
        AV_PIX_FMT_YUVJ444P, AV_PIX_FMT_YUVJ440P,
        AV_PIX_FMT_YUVJ422P, AV_PIX_FMT_YUVJ420P,
        AV_PIX_FMT_YUVJ411P,

        // YUV444
        AV_PIX_FMT_YUV444P,   AV_PIX_FMT_YUV444P9,
        AV_PIX_FMT_YUV444P10, AV_PIX_FMT_YUV444P12,
        AV_PIX_FMT_YUV444P14, AV_PIX_FMT_YUV444P16,

        // YUV440
        AV_PIX_FMT_YUV440P, AV_PIX_FMT_YUV440P10,
        AV_PIX_FMT_YUV440P12,

        // YUV422
        AV_PIX_FMT_YUV422P,   AV_PIX_FMT_YUV422P9,
        AV_PIX_FMT_YUV422P10, AV_PIX_FMT_YUV422P12,
        AV_PIX_FMT_YUV422P14, AV_PIX_FMT_YUV422P16,

        // YUV420
        AV_PIX_FMT_YUV420P,   AV_PIX_FMT_YUV420P9,
        AV_PIX_FMT_YUV420P10, AV_PIX_FMT_YUV420P12,
        AV_PIX_FMT_YUV420P14, AV_PIX_FMT_YUV420P16,

        // YUV411
        AV_PIX_FMT_YUV411P,

        // YUV410
        AV_PIX_FMT_YUV410P,

        // GBR
        AV_PIX_FMT_GBRP,   AV_PIX_FMT_GBRP9,
        AV_PIX_FMT_GBRP10, AV_PIX_FMT_GBRP12,
        AV_PIX_FMT_GBRP14, AV_PIX_FMT_GBRP16,

        // GBRA
        AV_PIX_FMT_GBRAP,   AV_PIX_FMT_GBRAP10,
        AV_PIX_FMT_GBRAP12, AV_PIX_FMT_GBRAP16,

        // GRAY
        AV_PIX_FMT_GRAY8,  AV_PIX_FMT_GRAY9,
        AV_PIX_FMT_GRAY10, AV_PIX_FMT_GRAY12,
        AV_PIX_FMT_GRAY14, AV_PIX_FMT_GRAY16,

        AV_PIX_FMT_NONE
    };

    AVFilterFormats *fmts_list = ff_make_format_list(pix_fmts);
    if (!fmts_list)
        return AVERROR(ENOMEM);
    return ff_set_common_formats(ctx, fmts_list);
}