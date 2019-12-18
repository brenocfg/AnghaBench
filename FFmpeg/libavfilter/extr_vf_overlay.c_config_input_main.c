#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  format; TYPE_1__* dst; } ;
struct TYPE_11__ {int /*<<< orphan*/  log2_chroma_h; int /*<<< orphan*/  log2_chroma_w; } ;
struct TYPE_10__ {int main_is_packed_rgb; int format; int /*<<< orphan*/  main_has_alpha; int /*<<< orphan*/  alpha_format; void* blend_slice; int /*<<< orphan*/  main_rgba_map; TYPE_3__ const* main_desc; int /*<<< orphan*/  vsub; int /*<<< orphan*/  hsub; int /*<<< orphan*/  main_pix_step; } ;
struct TYPE_9__ {TYPE_2__* priv; } ;
typedef  TYPE_2__ OverlayContext ;
typedef  TYPE_3__ AVPixFmtDescriptor ;
typedef  TYPE_4__ AVFilterLink ;

/* Variables and functions */
 scalar_t__ ARCH_X86 ; 
#define  AV_PIX_FMT_ABGR 141 
#define  AV_PIX_FMT_ARGB 140 
#define  AV_PIX_FMT_BGRA 139 
#define  AV_PIX_FMT_GBRAP 138 
#define  AV_PIX_FMT_RGBA 137 
#define  AV_PIX_FMT_YUVA420P 136 
#define  AV_PIX_FMT_YUVA422P 135 
#define  AV_PIX_FMT_YUVA444P 134 
#define  OVERLAY_FORMAT_AUTO 133 
#define  OVERLAY_FORMAT_GBRP 132 
#define  OVERLAY_FORMAT_RGB 131 
#define  OVERLAY_FORMAT_YUV420 130 
#define  OVERLAY_FORMAT_YUV422 129 
#define  OVERLAY_FORMAT_YUV444 128 
 int /*<<< orphan*/  alpha_pix_fmts ; 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_image_fill_max_pixsteps (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__ const*) ; 
 TYPE_3__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 void* blend_slice_gbrap ; 
 void* blend_slice_gbrap_pm ; 
 void* blend_slice_gbrp ; 
 void* blend_slice_gbrp_pm ; 
 void* blend_slice_rgb ; 
 void* blend_slice_rgb_pm ; 
 void* blend_slice_rgba ; 
 void* blend_slice_rgba_pm ; 
 void* blend_slice_yuv420 ; 
 void* blend_slice_yuv420_pm ; 
 void* blend_slice_yuv422 ; 
 void* blend_slice_yuv422_pm ; 
 void* blend_slice_yuv444 ; 
 void* blend_slice_yuv444_pm ; 
 void* blend_slice_yuva420 ; 
 void* blend_slice_yuva420_pm ; 
 void* blend_slice_yuva422 ; 
 void* blend_slice_yuva422_pm ; 
 void* blend_slice_yuva444 ; 
 void* blend_slice_yuva444_pm ; 
 scalar_t__ ff_fill_rgba_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_fmt_is_in (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_overlay_init_x86 (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_input_main(AVFilterLink *inlink)
{
    OverlayContext *s = inlink->dst->priv;
    const AVPixFmtDescriptor *pix_desc = av_pix_fmt_desc_get(inlink->format);

    av_image_fill_max_pixsteps(s->main_pix_step,    NULL, pix_desc);

    s->hsub = pix_desc->log2_chroma_w;
    s->vsub = pix_desc->log2_chroma_h;

    s->main_desc = pix_desc;

    s->main_is_packed_rgb =
        ff_fill_rgba_map(s->main_rgba_map, inlink->format) >= 0;
    s->main_has_alpha = ff_fmt_is_in(inlink->format, alpha_pix_fmts);
    switch (s->format) {
    case OVERLAY_FORMAT_YUV420:
        s->blend_slice = s->main_has_alpha ? blend_slice_yuva420 : blend_slice_yuv420;
        break;
    case OVERLAY_FORMAT_YUV422:
        s->blend_slice = s->main_has_alpha ? blend_slice_yuva422 : blend_slice_yuv422;
        break;
    case OVERLAY_FORMAT_YUV444:
        s->blend_slice = s->main_has_alpha ? blend_slice_yuva444 : blend_slice_yuv444;
        break;
    case OVERLAY_FORMAT_RGB:
        s->blend_slice = s->main_has_alpha ? blend_slice_rgba : blend_slice_rgb;
        break;
    case OVERLAY_FORMAT_GBRP:
        s->blend_slice = s->main_has_alpha ? blend_slice_gbrap : blend_slice_gbrp;
        break;
    case OVERLAY_FORMAT_AUTO:
        switch (inlink->format) {
        case AV_PIX_FMT_YUVA420P:
            s->blend_slice = blend_slice_yuva420;
            break;
        case AV_PIX_FMT_YUVA422P:
            s->blend_slice = blend_slice_yuva422;
            break;
        case AV_PIX_FMT_YUVA444P:
            s->blend_slice = blend_slice_yuva444;
            break;
        case AV_PIX_FMT_ARGB:
        case AV_PIX_FMT_RGBA:
        case AV_PIX_FMT_BGRA:
        case AV_PIX_FMT_ABGR:
            s->blend_slice = blend_slice_rgba;
            break;
        case AV_PIX_FMT_GBRAP:
            s->blend_slice = blend_slice_gbrap;
            break;
        default:
            av_assert0(0);
            break;
        }
        break;
    }

    if (!s->alpha_format)
        goto end;

    switch (s->format) {
    case OVERLAY_FORMAT_YUV420:
        s->blend_slice = s->main_has_alpha ? blend_slice_yuva420_pm : blend_slice_yuv420_pm;
        break;
    case OVERLAY_FORMAT_YUV422:
        s->blend_slice = s->main_has_alpha ? blend_slice_yuva422_pm : blend_slice_yuv422_pm;
        break;
    case OVERLAY_FORMAT_YUV444:
        s->blend_slice = s->main_has_alpha ? blend_slice_yuva444_pm : blend_slice_yuv444_pm;
        break;
    case OVERLAY_FORMAT_RGB:
        s->blend_slice = s->main_has_alpha ? blend_slice_rgba_pm : blend_slice_rgb_pm;
        break;
    case OVERLAY_FORMAT_GBRP:
        s->blend_slice = s->main_has_alpha ? blend_slice_gbrap_pm : blend_slice_gbrp_pm;
        break;
    case OVERLAY_FORMAT_AUTO:
        switch (inlink->format) {
        case AV_PIX_FMT_YUVA420P:
            s->blend_slice = blend_slice_yuva420_pm;
            break;
        case AV_PIX_FMT_YUVA422P:
            s->blend_slice = blend_slice_yuva422_pm;
            break;
        case AV_PIX_FMT_YUVA444P:
            s->blend_slice = blend_slice_yuva444_pm;
            break;
        case AV_PIX_FMT_ARGB:
        case AV_PIX_FMT_RGBA:
        case AV_PIX_FMT_BGRA:
        case AV_PIX_FMT_ABGR:
            s->blend_slice = blend_slice_rgba_pm;
            break;
        case AV_PIX_FMT_GBRAP:
            s->blend_slice = blend_slice_gbrap_pm;
            break;
        default:
            av_assert0(0);
            break;
        }
        break;
    }

end:
    if (ARCH_X86)
        ff_overlay_init_x86(s, s->format, inlink->format,
                            s->alpha_format, s->main_has_alpha);

    return 0;
}