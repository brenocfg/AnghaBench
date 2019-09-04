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
#define  AV_PIX_FMT_ABGR 197 
#define  AV_PIX_FMT_ARGB 196 
#define  AV_PIX_FMT_BGR24 195 
#define  AV_PIX_FMT_BGRA 194 
#define  AV_PIX_FMT_GBRAP 193 
#define  AV_PIX_FMT_GBRAP10 192 
#define  AV_PIX_FMT_GBRAP12 191 
#define  AV_PIX_FMT_GBRAP16 190 
#define  AV_PIX_FMT_GBRP 189 
#define  AV_PIX_FMT_GBRP10 188 
#define  AV_PIX_FMT_GBRP12 187 
#define  AV_PIX_FMT_GBRP14 186 
#define  AV_PIX_FMT_GBRP16 185 
#define  AV_PIX_FMT_GBRP9 184 
#define  AV_PIX_FMT_GRAY10 183 
#define  AV_PIX_FMT_GRAY12 182 
#define  AV_PIX_FMT_GRAY14 181 
#define  AV_PIX_FMT_GRAY16 180 
#define  AV_PIX_FMT_GRAY8 179 
#define  AV_PIX_FMT_GRAY9 178 
#define  AV_PIX_FMT_NONE 177 
#define  AV_PIX_FMT_NV12 176 
#define  AV_PIX_FMT_NV16 175 
#define  AV_PIX_FMT_NV21 174 
#define  AV_PIX_FMT_RGB24 173 
#define  AV_PIX_FMT_RGBA 172 
#define  AV_PIX_FMT_UYVY422 171 
#define  AV_PIX_FMT_YA8 170 
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
#define  AV_PIX_FMT_YUVA422P16 140 
#define  AV_PIX_FMT_YUVA422P9 139 
#define  AV_PIX_FMT_YUVA444P 138 
#define  AV_PIX_FMT_YUVA444P10 137 
#define  AV_PIX_FMT_YUVA444P16 136 
#define  AV_PIX_FMT_YUVA444P9 135 
#define  AV_PIX_FMT_YUVJ411P 134 
#define  AV_PIX_FMT_YUVJ420P 133 
#define  AV_PIX_FMT_YUVJ422P 132 
#define  AV_PIX_FMT_YUVJ440P 131 
#define  AV_PIX_FMT_YUVJ444P 130 
#define  AV_PIX_FMT_YUYV422 129 
#define  AV_PIX_FMT_YVYU422 128 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/ * ff_make_format_list (int const*) ; 
 int ff_set_common_formats (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    static const enum AVPixelFormat pix_fmts[] = {
        AV_PIX_FMT_YUV420P, AV_PIX_FMT_YUYV422, AV_PIX_FMT_RGB24,
        AV_PIX_FMT_BGR24, AV_PIX_FMT_YUV422P, AV_PIX_FMT_YUV444P,
        AV_PIX_FMT_YUV410P, AV_PIX_FMT_YUV411P, AV_PIX_FMT_GRAY8,
        AV_PIX_FMT_YUVJ420P, AV_PIX_FMT_YUVJ422P, AV_PIX_FMT_YUVJ444P,
        AV_PIX_FMT_UYVY422, AV_PIX_FMT_NV12, AV_PIX_FMT_NV21, AV_PIX_FMT_ARGB,
        AV_PIX_FMT_RGBA, AV_PIX_FMT_ABGR, AV_PIX_FMT_BGRA, AV_PIX_FMT_GRAY16,
        AV_PIX_FMT_YUV440P, AV_PIX_FMT_YUVJ440P, AV_PIX_FMT_YUVA420P,
        AV_PIX_FMT_YUV420P16, AV_PIX_FMT_YUV422P16, AV_PIX_FMT_YUV444P16,
        AV_PIX_FMT_YA8, AV_PIX_FMT_YUV420P9, AV_PIX_FMT_YUV420P10,
        AV_PIX_FMT_YUV422P10, AV_PIX_FMT_YUV444P9, AV_PIX_FMT_YUV444P10,
        AV_PIX_FMT_YUV422P9, AV_PIX_FMT_GBRP, AV_PIX_FMT_GBRP9,
        AV_PIX_FMT_GBRP10, AV_PIX_FMT_GBRP16, AV_PIX_FMT_YUVA422P,
        AV_PIX_FMT_YUVA444P, AV_PIX_FMT_YUVA420P9, AV_PIX_FMT_YUVA422P9,
        AV_PIX_FMT_YUVA444P9, AV_PIX_FMT_YUVA420P10, AV_PIX_FMT_YUVA422P10,
        AV_PIX_FMT_YUVA444P10, AV_PIX_FMT_YUVA420P16, AV_PIX_FMT_YUVA422P16,
        AV_PIX_FMT_YUVA444P16, AV_PIX_FMT_NV16, AV_PIX_FMT_YVYU422,
        AV_PIX_FMT_GBRAP, AV_PIX_FMT_GBRAP16, AV_PIX_FMT_YUV420P12,
        AV_PIX_FMT_YUV420P14, AV_PIX_FMT_YUV422P12, AV_PIX_FMT_YUV422P14,
        AV_PIX_FMT_YUV444P12, AV_PIX_FMT_YUV444P14, AV_PIX_FMT_GBRP12,
        AV_PIX_FMT_GBRP14, AV_PIX_FMT_YUVJ411P, AV_PIX_FMT_YUV440P10,
        AV_PIX_FMT_YUV440P12, AV_PIX_FMT_GBRAP12, AV_PIX_FMT_GBRAP10,
        AV_PIX_FMT_GRAY12, AV_PIX_FMT_GRAY10, AV_PIX_FMT_GRAY9,
        AV_PIX_FMT_GRAY14,
        AV_PIX_FMT_NONE
    };

    AVFilterFormats *fmts_list = ff_make_format_list(pix_fmts);
    if (!fmts_list)
        return AVERROR(ENOMEM);
    return ff_set_common_formats(ctx, fmts_list);
}