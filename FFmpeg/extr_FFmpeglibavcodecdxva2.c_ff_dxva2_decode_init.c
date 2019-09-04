#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVHWDeviceType { ____Placeholder_AVHWDeviceType } AVHWDeviceType ;
struct TYPE_16__ {TYPE_2__* hw_frames_ctx; TYPE_1__* hwaccel; scalar_t__ hwaccel_context; } ;
struct TYPE_15__ {scalar_t__ format; int /*<<< orphan*/  device_ctx; } ;
struct TYPE_14__ {scalar_t__ pix_fmt; int /*<<< orphan*/  device_ctx; } ;
struct TYPE_13__ {scalar_t__ data; } ;
struct TYPE_12__ {scalar_t__ pix_fmt; } ;
typedef  TYPE_3__ FFDXVASharedContext ;
typedef  TYPE_4__ AVHWFramesContext ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_HWDEVICE_TYPE_D3D11VA ; 
 int AV_HWDEVICE_TYPE_DXVA2 ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_PIX_FMT_DXVA2_VLD ; 
 TYPE_3__* DXVA_SHARED_CONTEXT (TYPE_5__*) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int ff_decode_get_hw_frames_ctx (TYPE_5__*,int) ; 
 int /*<<< orphan*/  ff_dxva2_decode_uninit (TYPE_5__*) ; 

int ff_dxva2_decode_init(AVCodecContext *avctx)
{
    FFDXVASharedContext *sctx = DXVA_SHARED_CONTEXT(avctx);
    AVHWFramesContext *frames_ctx;
    enum AVHWDeviceType dev_type = avctx->hwaccel->pix_fmt == AV_PIX_FMT_DXVA2_VLD
                            ? AV_HWDEVICE_TYPE_DXVA2 : AV_HWDEVICE_TYPE_D3D11VA;
    int ret = 0;

    // Old API.
    if (avctx->hwaccel_context)
        return 0;

    // (avctx->pix_fmt is not updated yet at this point)
    sctx->pix_fmt = avctx->hwaccel->pix_fmt;

    ret = ff_decode_get_hw_frames_ctx(avctx, dev_type);
    if (ret < 0)
        return ret;

    frames_ctx = (AVHWFramesContext*)avctx->hw_frames_ctx->data;
    sctx->device_ctx = frames_ctx->device_ctx;

    if (frames_ctx->format != sctx->pix_fmt) {
        av_log(avctx, AV_LOG_ERROR, "Invalid pixfmt for hwaccel!\n");
        ret = AVERROR(EINVAL);
        goto fail;
    }

#if CONFIG_D3D11VA
    if (sctx->pix_fmt == AV_PIX_FMT_D3D11) {
        AVD3D11VADeviceContext *device_hwctx = frames_ctx->device_ctx->hwctx;
        AVD3D11VAContext *d3d11_ctx = &sctx->ctx.d3d11va;

        ff_dxva2_lock(avctx);
        ret = d3d11va_create_decoder(avctx);
        ff_dxva2_unlock(avctx);
        if (ret < 0)
            goto fail;

        d3d11_ctx->decoder       = sctx->d3d11_decoder;
        d3d11_ctx->video_context = device_hwctx->video_context;
        d3d11_ctx->cfg           = &sctx->d3d11_config;
        d3d11_ctx->surface_count = sctx->nb_d3d11_views;
        d3d11_ctx->surface       = sctx->d3d11_views;
        d3d11_ctx->workaround    = sctx->workaround;
        d3d11_ctx->context_mutex = INVALID_HANDLE_VALUE;
    }
#endif

#if CONFIG_DXVA2
    if (sctx->pix_fmt == AV_PIX_FMT_DXVA2_VLD) {
        AVDXVA2FramesContext *frames_hwctx = frames_ctx->hwctx;
        struct dxva_context *dxva_ctx = &sctx->ctx.dxva2;

        ff_dxva2_lock(avctx);
        ret = dxva2_create_decoder(avctx);
        ff_dxva2_unlock(avctx);
        if (ret < 0)
            goto fail;

        dxva_ctx->decoder       = sctx->dxva2_decoder;
        dxva_ctx->cfg           = &sctx->dxva2_config;
        dxva_ctx->surface       = frames_hwctx->surfaces;
        dxva_ctx->surface_count = frames_hwctx->nb_surfaces;
        dxva_ctx->workaround    = sctx->workaround;
    }
#endif

    return 0;

fail:
    ff_dxva2_decode_uninit(avctx);
    return ret;
}