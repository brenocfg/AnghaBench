#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {scalar_t__ data; } ;
struct TYPE_21__ {void* height; void* width; int /*<<< orphan*/  initial_pool_size; int /*<<< orphan*/  sw_format; int /*<<< orphan*/  format; TYPE_3__* device_ctx; TYPE_1__* internal; int /*<<< orphan*/ * hwctx; } ;
struct TYPE_20__ {int /*<<< orphan*/  child_pix_fmt; int /*<<< orphan*/  child_device_type; int /*<<< orphan*/  handle; } ;
struct TYPE_19__ {TYPE_7__* child_frames_ref; } ;
struct TYPE_18__ {TYPE_2__* internal; } ;
struct TYPE_17__ {TYPE_5__* priv; } ;
struct TYPE_16__ {TYPE_4__* priv; } ;
typedef  TYPE_4__ QSVFramesContext ;
typedef  TYPE_5__ QSVDeviceContext ;
typedef  int /*<<< orphan*/  AVQSVFramesContext ;
typedef  TYPE_6__ AVHWFramesContext ;
typedef  int /*<<< orphan*/  AVHWDeviceContext ;
typedef  TYPE_7__ AVBufferRef ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* FFALIGN (void*,int) ; 
 int /*<<< orphan*/  av_buffer_unref (TYPE_7__**) ; 
 TYPE_7__* av_hwdevice_ctx_alloc (int /*<<< orphan*/ ) ; 
 int av_hwdevice_ctx_init (TYPE_7__*) ; 
 TYPE_7__* av_hwframe_ctx_alloc (TYPE_7__*) ; 
 int av_hwframe_ctx_init (TYPE_7__*) ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int qsv_init_child_ctx(AVHWFramesContext *ctx)
{
    AVQSVFramesContext     *hwctx = ctx->hwctx;
    QSVFramesContext           *s = ctx->internal->priv;
    QSVDeviceContext *device_priv = ctx->device_ctx->internal->priv;

    AVBufferRef *child_device_ref = NULL;
    AVBufferRef *child_frames_ref = NULL;

    AVHWDeviceContext *child_device_ctx;
    AVHWFramesContext *child_frames_ctx;

    int i, ret = 0;

    if (!device_priv->handle) {
        av_log(ctx, AV_LOG_ERROR,
               "Cannot create a non-opaque internal surface pool without "
               "a hardware handle\n");
        return AVERROR(EINVAL);
    }

    child_device_ref = av_hwdevice_ctx_alloc(device_priv->child_device_type);
    if (!child_device_ref)
        return AVERROR(ENOMEM);
    child_device_ctx   = (AVHWDeviceContext*)child_device_ref->data;

#if CONFIG_VAAPI
    if (child_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIDeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        child_device_hwctx->display = (VADisplay)device_priv->handle;
    }
#endif
#if CONFIG_DXVA2
    if (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2DeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        child_device_hwctx->devmgr = (IDirect3DDeviceManager9*)device_priv->handle;
    }
#endif

    ret = av_hwdevice_ctx_init(child_device_ref);
    if (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child device context\n");
        goto fail;
    }

    child_frames_ref = av_hwframe_ctx_alloc(child_device_ref);
    if (!child_frames_ref) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }
    child_frames_ctx = (AVHWFramesContext*)child_frames_ref->data;

    child_frames_ctx->format            = device_priv->child_pix_fmt;
    child_frames_ctx->sw_format         = ctx->sw_format;
    child_frames_ctx->initial_pool_size = ctx->initial_pool_size;
    child_frames_ctx->width             = FFALIGN(ctx->width, 16);
    child_frames_ctx->height            = FFALIGN(ctx->height, 16);

#if CONFIG_DXVA2
    if (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2FramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        if (hwctx->frame_type & MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET)
            child_frames_hwctx->surface_type = DXVA2_VideoProcessorRenderTarget;
        else
            child_frames_hwctx->surface_type = DXVA2_VideoDecoderRenderTarget;
    }
#endif

    ret = av_hwframe_ctx_init(child_frames_ref);
    if (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child frames context\n");
        goto fail;
    }

#if CONFIG_VAAPI
    if (child_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        for (i = 0; i < ctx->initial_pool_size; i++)
            s->surfaces_internal[i].Data.MemId = child_frames_hwctx->surface_ids + i;
        hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
    }
#endif
#if CONFIG_DXVA2
    if (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2FramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        for (i = 0; i < ctx->initial_pool_size; i++)
            s->surfaces_internal[i].Data.MemId = (mfxMemId)child_frames_hwctx->surfaces[i];
        if (child_frames_hwctx->surface_type == DXVA2_VideoProcessorRenderTarget)
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        else
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
    }
#endif

    s->child_frames_ref       = child_frames_ref;
    child_frames_ref          = NULL;

fail:
    av_buffer_unref(&child_device_ref);
    av_buffer_unref(&child_frames_ref);
    return ret;
}