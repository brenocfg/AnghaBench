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
struct TYPE_5__ {scalar_t__ inplace; } ;
typedef  TYPE_1__ PreMultiplyContext ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
#define  AV_PIX_FMT_GBRAP 155 
#define  AV_PIX_FMT_GBRAP10 154 
#define  AV_PIX_FMT_GBRAP12 153 
#define  AV_PIX_FMT_GBRAP16 152 
#define  AV_PIX_FMT_GBRP 151 
#define  AV_PIX_FMT_GBRP10 150 
#define  AV_PIX_FMT_GBRP12 149 
#define  AV_PIX_FMT_GBRP14 148 
#define  AV_PIX_FMT_GBRP16 147 
#define  AV_PIX_FMT_GBRP9 146 
#define  AV_PIX_FMT_GRAY10 145 
#define  AV_PIX_FMT_GRAY12 144 
#define  AV_PIX_FMT_GRAY14 143 
#define  AV_PIX_FMT_GRAY16 142 
#define  AV_PIX_FMT_GRAY8 141 
#define  AV_PIX_FMT_GRAY9 140 
#define  AV_PIX_FMT_NONE 139 
#define  AV_PIX_FMT_YUV444P 138 
#define  AV_PIX_FMT_YUV444P10 137 
#define  AV_PIX_FMT_YUV444P12 136 
#define  AV_PIX_FMT_YUV444P14 135 
#define  AV_PIX_FMT_YUV444P16 134 
#define  AV_PIX_FMT_YUV444P9 133 
#define  AV_PIX_FMT_YUVA444P 132 
#define  AV_PIX_FMT_YUVA444P10 131 
#define  AV_PIX_FMT_YUVA444P16 130 
#define  AV_PIX_FMT_YUVA444P9 129 
#define  AV_PIX_FMT_YUVJ444P 128 
 int /*<<< orphan*/  ff_make_format_list (int const*) ; 
 int ff_set_common_formats (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    PreMultiplyContext *s = ctx->priv;

    static const enum AVPixelFormat no_alpha_pix_fmts[] = {
        AV_PIX_FMT_YUV444P, AV_PIX_FMT_YUVJ444P,
        AV_PIX_FMT_YUV444P9, AV_PIX_FMT_YUV444P10,
        AV_PIX_FMT_YUV444P12, AV_PIX_FMT_YUV444P14,
        AV_PIX_FMT_YUV444P16,
        AV_PIX_FMT_GBRP, AV_PIX_FMT_GBRP9, AV_PIX_FMT_GBRP10,
        AV_PIX_FMT_GBRP12, AV_PIX_FMT_GBRP14, AV_PIX_FMT_GBRP16,
        AV_PIX_FMT_GRAY8, AV_PIX_FMT_GRAY9, AV_PIX_FMT_GRAY10, AV_PIX_FMT_GRAY12, AV_PIX_FMT_GRAY14, AV_PIX_FMT_GRAY16,
        AV_PIX_FMT_NONE
    };

    static const enum AVPixelFormat alpha_pix_fmts[] = {
        AV_PIX_FMT_YUVA444P,
        AV_PIX_FMT_YUVA444P9, AV_PIX_FMT_YUVA444P10, AV_PIX_FMT_YUVA444P16,
        AV_PIX_FMT_GBRAP,
        AV_PIX_FMT_GBRAP10, AV_PIX_FMT_GBRAP12, AV_PIX_FMT_GBRAP16,
        AV_PIX_FMT_NONE
    };

    return ff_set_common_formats(ctx, ff_make_format_list(s->inplace ? alpha_pix_fmts : no_alpha_pix_fmts));
}