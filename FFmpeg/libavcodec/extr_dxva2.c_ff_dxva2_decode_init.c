#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
struct dxva_context {int /*<<< orphan*/  workaround; int /*<<< orphan*/  surface_count; int /*<<< orphan*/  surface; int /*<<< orphan*/ * cfg; int /*<<< orphan*/  decoder; } ;
typedef  enum AVHWDeviceType { ____Placeholder_AVHWDeviceType } AVHWDeviceType ;
struct TYPE_30__ {int /*<<< orphan*/  context_mutex; int /*<<< orphan*/  workaround; int /*<<< orphan*/  surface; int /*<<< orphan*/  surface_count; int /*<<< orphan*/ * cfg; int /*<<< orphan*/  video_context; int /*<<< orphan*/  decoder; } ;
struct TYPE_29__ {int /*<<< orphan*/  video_context; } ;
struct TYPE_28__ {int /*<<< orphan*/  nb_surfaces; int /*<<< orphan*/  surfaces; } ;
struct TYPE_27__ {scalar_t__ format; TYPE_7__* hwctx; TYPE_3__* device_ctx; } ;
struct TYPE_25__ {struct dxva_context dxva2; TYPE_9__ d3d11va; } ;
struct TYPE_26__ {scalar_t__ pix_fmt; int /*<<< orphan*/  workaround; int /*<<< orphan*/  dxva2_config; int /*<<< orphan*/  dxva2_decoder; TYPE_4__ ctx; int /*<<< orphan*/  d3d11_views; int /*<<< orphan*/  nb_d3d11_views; int /*<<< orphan*/  d3d11_config; int /*<<< orphan*/  d3d11_decoder; TYPE_3__* device_ctx; } ;
struct TYPE_24__ {TYPE_8__* hwctx; } ;
struct TYPE_23__ {scalar_t__ data; } ;
struct TYPE_22__ {scalar_t__ pix_fmt; } ;
struct TYPE_21__ {TYPE_2__* hw_frames_ctx; TYPE_1__* hwaccel; scalar_t__ hwaccel_context; } ;
typedef  TYPE_5__ FFDXVASharedContext ;
typedef  TYPE_6__ AVHWFramesContext ;
typedef  TYPE_7__ AVDXVA2FramesContext ;
typedef  TYPE_8__ AVD3D11VADeviceContext ;
typedef  TYPE_9__ AVD3D11VAContext ;
typedef  TYPE_10__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_HWDEVICE_TYPE_D3D11VA ; 
 int AV_HWDEVICE_TYPE_DXVA2 ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_PIX_FMT_D3D11 ; 
 scalar_t__ AV_PIX_FMT_DXVA2_VLD ; 
 TYPE_5__* DXVA_SHARED_CONTEXT (TYPE_10__*) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  av_log (TYPE_10__*,int /*<<< orphan*/ ,char*) ; 
 int d3d11va_create_decoder (TYPE_10__*) ; 
 int dxva2_create_decoder (TYPE_10__*) ; 
 int ff_decode_get_hw_frames_ctx (TYPE_10__*,int) ; 
 int /*<<< orphan*/  ff_dxva2_decode_uninit (TYPE_10__*) ; 
 int /*<<< orphan*/  ff_dxva2_lock (TYPE_10__*) ; 
 int /*<<< orphan*/  ff_dxva2_unlock (TYPE_10__*) ; 

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