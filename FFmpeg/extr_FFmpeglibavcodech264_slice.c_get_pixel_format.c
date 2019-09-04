#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_14__ {int const pix_fmt; int /*<<< orphan*/  color_range; TYPE_1__* codec; int /*<<< orphan*/  colorspace; } ;
struct TYPE_12__ {TYPE_2__* sps; } ;
struct TYPE_13__ {TYPE_6__* avctx; TYPE_3__ ps; } ;
struct TYPE_11__ {int bit_depth_luma; } ;
struct TYPE_10__ {int* pix_fmts; } ;
typedef  TYPE_4__ H264Context ;

/* Variables and functions */
 int /*<<< orphan*/  AVCOL_RANGE_JPEG ; 
 int /*<<< orphan*/  AVCOL_SPC_RGB ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PIX_FMT_GBRP ; 
 int /*<<< orphan*/  AV_PIX_FMT_GBRP10 ; 
 int /*<<< orphan*/  AV_PIX_FMT_GBRP12 ; 
 int /*<<< orphan*/  AV_PIX_FMT_GBRP14 ; 
 int /*<<< orphan*/  AV_PIX_FMT_GBRP9 ; 
 int const AV_PIX_FMT_NONE ; 
 int /*<<< orphan*/  AV_PIX_FMT_YUV420P ; 
 int /*<<< orphan*/  AV_PIX_FMT_YUV420P10 ; 
 int /*<<< orphan*/  AV_PIX_FMT_YUV420P12 ; 
 int /*<<< orphan*/  AV_PIX_FMT_YUV420P14 ; 
 int /*<<< orphan*/  AV_PIX_FMT_YUV420P9 ; 
 int /*<<< orphan*/  AV_PIX_FMT_YUV422P ; 
 int /*<<< orphan*/  AV_PIX_FMT_YUV422P10 ; 
 int /*<<< orphan*/  AV_PIX_FMT_YUV422P12 ; 
 int /*<<< orphan*/  AV_PIX_FMT_YUV422P14 ; 
 int /*<<< orphan*/  AV_PIX_FMT_YUV422P9 ; 
 int /*<<< orphan*/  AV_PIX_FMT_YUV444P ; 
 int /*<<< orphan*/  AV_PIX_FMT_YUV444P10 ; 
 int /*<<< orphan*/  AV_PIX_FMT_YUV444P12 ; 
 int /*<<< orphan*/  AV_PIX_FMT_YUV444P14 ; 
 int /*<<< orphan*/  AV_PIX_FMT_YUV444P9 ; 
 int /*<<< orphan*/  AV_PIX_FMT_YUVJ420P ; 
 int /*<<< orphan*/  AV_PIX_FMT_YUVJ422P ; 
 int /*<<< orphan*/  AV_PIX_FMT_YUVJ444P ; 
 int /*<<< orphan*/  CHROMA422 (TYPE_4__*) ; 
 int /*<<< orphan*/  CHROMA444 (TYPE_4__*) ; 
 int CONFIG_H264_D3D11VA_HWACCEL ; 
 int /*<<< orphan*/  CONFIG_H264_DXVA2_HWACCEL ; 
 scalar_t__ CONFIG_H264_NVDEC_HWACCEL ; 
 scalar_t__ CONFIG_H264_VAAPI_HWACCEL ; 
 scalar_t__ CONFIG_H264_VDPAU_HWACCEL ; 
 scalar_t__ CONFIG_H264_VIDEOTOOLBOX_HWACCEL ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*,int) ; 
 int ff_thread_get_format (TYPE_6__*,int const*) ; 

__attribute__((used)) static enum AVPixelFormat get_pixel_format(H264Context *h, int force_callback)
{
#define HWACCEL_MAX (CONFIG_H264_DXVA2_HWACCEL + \
                     (CONFIG_H264_D3D11VA_HWACCEL * 2) + \
                     CONFIG_H264_NVDEC_HWACCEL + \
                     CONFIG_H264_VAAPI_HWACCEL + \
                     CONFIG_H264_VIDEOTOOLBOX_HWACCEL + \
                     CONFIG_H264_VDPAU_HWACCEL)
    enum AVPixelFormat pix_fmts[HWACCEL_MAX + 2], *fmt = pix_fmts;
    const enum AVPixelFormat *choices = pix_fmts;
    int i;

    switch (h->ps.sps->bit_depth_luma) {
    case 9:
        if (CHROMA444(h)) {
            if (h->avctx->colorspace == AVCOL_SPC_RGB) {
                *fmt++ = AV_PIX_FMT_GBRP9;
            } else
                *fmt++ = AV_PIX_FMT_YUV444P9;
        } else if (CHROMA422(h))
            *fmt++ = AV_PIX_FMT_YUV422P9;
        else
            *fmt++ = AV_PIX_FMT_YUV420P9;
        break;
    case 10:
        if (CHROMA444(h)) {
            if (h->avctx->colorspace == AVCOL_SPC_RGB) {
                *fmt++ = AV_PIX_FMT_GBRP10;
            } else
                *fmt++ = AV_PIX_FMT_YUV444P10;
        } else if (CHROMA422(h))
            *fmt++ = AV_PIX_FMT_YUV422P10;
        else
            *fmt++ = AV_PIX_FMT_YUV420P10;
        break;
    case 12:
        if (CHROMA444(h)) {
            if (h->avctx->colorspace == AVCOL_SPC_RGB) {
                *fmt++ = AV_PIX_FMT_GBRP12;
            } else
                *fmt++ = AV_PIX_FMT_YUV444P12;
        } else if (CHROMA422(h))
            *fmt++ = AV_PIX_FMT_YUV422P12;
        else
            *fmt++ = AV_PIX_FMT_YUV420P12;
        break;
    case 14:
        if (CHROMA444(h)) {
            if (h->avctx->colorspace == AVCOL_SPC_RGB) {
                *fmt++ = AV_PIX_FMT_GBRP14;
            } else
                *fmt++ = AV_PIX_FMT_YUV444P14;
        } else if (CHROMA422(h))
            *fmt++ = AV_PIX_FMT_YUV422P14;
        else
            *fmt++ = AV_PIX_FMT_YUV420P14;
        break;
    case 8:
#if CONFIG_H264_VDPAU_HWACCEL
        *fmt++ = AV_PIX_FMT_VDPAU;
#endif
#if CONFIG_H264_NVDEC_HWACCEL
        *fmt++ = AV_PIX_FMT_CUDA;
#endif
        if (CHROMA444(h)) {
            if (h->avctx->colorspace == AVCOL_SPC_RGB)
                *fmt++ = AV_PIX_FMT_GBRP;
            else if (h->avctx->color_range == AVCOL_RANGE_JPEG)
                *fmt++ = AV_PIX_FMT_YUVJ444P;
            else
                *fmt++ = AV_PIX_FMT_YUV444P;
        } else if (CHROMA422(h)) {
            if (h->avctx->color_range == AVCOL_RANGE_JPEG)
                *fmt++ = AV_PIX_FMT_YUVJ422P;
            else
                *fmt++ = AV_PIX_FMT_YUV422P;
        } else {
#if CONFIG_H264_DXVA2_HWACCEL
            *fmt++ = AV_PIX_FMT_DXVA2_VLD;
#endif
#if CONFIG_H264_D3D11VA_HWACCEL
            *fmt++ = AV_PIX_FMT_D3D11VA_VLD;
            *fmt++ = AV_PIX_FMT_D3D11;
#endif
#if CONFIG_H264_VAAPI_HWACCEL
            *fmt++ = AV_PIX_FMT_VAAPI;
#endif
#if CONFIG_H264_VIDEOTOOLBOX_HWACCEL
            *fmt++ = AV_PIX_FMT_VIDEOTOOLBOX;
#endif
            if (h->avctx->codec->pix_fmts)
                choices = h->avctx->codec->pix_fmts;
            else if (h->avctx->color_range == AVCOL_RANGE_JPEG)
                *fmt++ = AV_PIX_FMT_YUVJ420P;
            else
                *fmt++ = AV_PIX_FMT_YUV420P;
        }
        break;
    default:
        av_log(h->avctx, AV_LOG_ERROR,
               "Unsupported bit depth %d\n", h->ps.sps->bit_depth_luma);
        return AVERROR_INVALIDDATA;
    }

    *fmt = AV_PIX_FMT_NONE;

    for (i=0; choices[i] != AV_PIX_FMT_NONE; i++)
        if (choices[i] == h->avctx->pix_fmt && !force_callback)
            return choices[i];
    return ff_thread_get_format(h->avctx, choices);
}