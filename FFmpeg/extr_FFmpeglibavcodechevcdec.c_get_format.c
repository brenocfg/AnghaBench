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
struct TYPE_6__ {int /*<<< orphan*/  avctx; } ;
struct TYPE_5__ {int pix_fmt; } ;
typedef  TYPE_1__ HEVCSPS ;
typedef  TYPE_2__ HEVCContext ;

/* Variables and functions */
 int AV_PIX_FMT_NONE ; 
#define  AV_PIX_FMT_YUV420P 134 
#define  AV_PIX_FMT_YUV420P10 133 
#define  AV_PIX_FMT_YUV420P12 132 
#define  AV_PIX_FMT_YUV444P 131 
#define  AV_PIX_FMT_YUV444P10 130 
#define  AV_PIX_FMT_YUV444P12 129 
#define  AV_PIX_FMT_YUVJ420P 128 
 int CONFIG_HEVC_D3D11VA_HWACCEL ; 
 int /*<<< orphan*/  CONFIG_HEVC_DXVA2_HWACCEL ; 
 scalar_t__ CONFIG_HEVC_NVDEC_HWACCEL ; 
 scalar_t__ CONFIG_HEVC_VAAPI_HWACCEL ; 
 scalar_t__ CONFIG_HEVC_VDPAU_HWACCEL ; 
 scalar_t__ CONFIG_HEVC_VIDEOTOOLBOX_HWACCEL ; 
 int ff_thread_get_format (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static enum AVPixelFormat get_format(HEVCContext *s, const HEVCSPS *sps)
{
#define HWACCEL_MAX (CONFIG_HEVC_DXVA2_HWACCEL + \
                     CONFIG_HEVC_D3D11VA_HWACCEL * 2 + \
                     CONFIG_HEVC_NVDEC_HWACCEL + \
                     CONFIG_HEVC_VAAPI_HWACCEL + \
                     CONFIG_HEVC_VIDEOTOOLBOX_HWACCEL + \
                     CONFIG_HEVC_VDPAU_HWACCEL)
    enum AVPixelFormat pix_fmts[HWACCEL_MAX + 2], *fmt = pix_fmts;

    switch (sps->pix_fmt) {
    case AV_PIX_FMT_YUV420P:
    case AV_PIX_FMT_YUVJ420P:
#if CONFIG_HEVC_DXVA2_HWACCEL
        *fmt++ = AV_PIX_FMT_DXVA2_VLD;
#endif
#if CONFIG_HEVC_D3D11VA_HWACCEL
        *fmt++ = AV_PIX_FMT_D3D11VA_VLD;
        *fmt++ = AV_PIX_FMT_D3D11;
#endif
#if CONFIG_HEVC_VAAPI_HWACCEL
        *fmt++ = AV_PIX_FMT_VAAPI;
#endif
#if CONFIG_HEVC_VDPAU_HWACCEL
        *fmt++ = AV_PIX_FMT_VDPAU;
#endif
#if CONFIG_HEVC_NVDEC_HWACCEL
        *fmt++ = AV_PIX_FMT_CUDA;
#endif
#if CONFIG_HEVC_VIDEOTOOLBOX_HWACCEL
        *fmt++ = AV_PIX_FMT_VIDEOTOOLBOX;
#endif
        break;
    case AV_PIX_FMT_YUV420P10:
#if CONFIG_HEVC_DXVA2_HWACCEL
        *fmt++ = AV_PIX_FMT_DXVA2_VLD;
#endif
#if CONFIG_HEVC_D3D11VA_HWACCEL
        *fmt++ = AV_PIX_FMT_D3D11VA_VLD;
        *fmt++ = AV_PIX_FMT_D3D11;
#endif
#if CONFIG_HEVC_VAAPI_HWACCEL
        *fmt++ = AV_PIX_FMT_VAAPI;
#endif
#if CONFIG_HEVC_VIDEOTOOLBOX_HWACCEL
        *fmt++ = AV_PIX_FMT_VIDEOTOOLBOX;
#endif
#if CONFIG_HEVC_NVDEC_HWACCEL
        *fmt++ = AV_PIX_FMT_CUDA;
#endif
        break;
    case AV_PIX_FMT_YUV420P12:
    case AV_PIX_FMT_YUV444P:
    case AV_PIX_FMT_YUV444P10:
    case AV_PIX_FMT_YUV444P12:
#if CONFIG_HEVC_NVDEC_HWACCEL
        *fmt++ = AV_PIX_FMT_CUDA;
#endif
        break;
    }

    *fmt++ = sps->pix_fmt;
    *fmt = AV_PIX_FMT_NONE;

    return ff_thread_get_format(s->avctx, pix_fmts);
}