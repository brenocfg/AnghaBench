#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_15__ ;
typedef  struct TYPE_25__   TYPE_12__ ;
typedef  struct TYPE_24__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ mfxMemId ;
typedef  scalar_t__ VADisplay ;
struct TYPE_35__ {int /*<<< orphan*/ * devmgr; scalar_t__ display; } ;
struct TYPE_34__ {int frame_type; scalar_t__ surface_type; scalar_t__* surfaces; scalar_t__ surface_ids; } ;
struct TYPE_33__ {int /*<<< orphan*/  child_pix_fmt; scalar_t__ handle; int /*<<< orphan*/  child_device_type; } ;
struct TYPE_32__ {TYPE_15__* child_frames_ref; TYPE_5__* surfaces_internal; } ;
struct TYPE_30__ {scalar_t__ MemId; } ;
struct TYPE_31__ {TYPE_4__ Data; } ;
struct TYPE_29__ {TYPE_2__* internal; } ;
struct TYPE_28__ {TYPE_7__* priv; } ;
struct TYPE_27__ {TYPE_6__* priv; } ;
struct TYPE_26__ {scalar_t__ data; } ;
struct TYPE_25__ {scalar_t__ type; TYPE_9__* hwctx; } ;
struct TYPE_24__ {int initial_pool_size; TYPE_8__* hwctx; void* height; void* width; int /*<<< orphan*/  sw_format; int /*<<< orphan*/  format; TYPE_3__* device_ctx; TYPE_1__* internal; } ;
typedef  TYPE_6__ QSVFramesContext ;
typedef  TYPE_7__ QSVDeviceContext ;
typedef  int /*<<< orphan*/  IDirect3DDeviceManager9 ;
typedef  TYPE_8__ AVVAAPIFramesContext ;
typedef  TYPE_9__ AVVAAPIDeviceContext ;
typedef  TYPE_8__ AVQSVFramesContext ;
typedef  TYPE_11__ AVHWFramesContext ;
typedef  TYPE_12__ AVHWDeviceContext ;
typedef  TYPE_8__ AVDXVA2FramesContext ;
typedef  TYPE_9__ AVDXVA2DeviceContext ;
typedef  TYPE_15__ AVBufferRef ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_HWDEVICE_TYPE_DXVA2 ; 
 scalar_t__ AV_HWDEVICE_TYPE_VAAPI ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ DXVA2_VideoDecoderRenderTarget ; 
 scalar_t__ DXVA2_VideoProcessorRenderTarget ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* FFALIGN (void*,int) ; 
 void* MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET ; 
 int MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET ; 
 int /*<<< orphan*/  av_buffer_unref (TYPE_15__**) ; 
 TYPE_15__* av_hwdevice_ctx_alloc (int /*<<< orphan*/ ) ; 
 int av_hwdevice_ctx_init (TYPE_15__*) ; 
 TYPE_15__* av_hwframe_ctx_alloc (TYPE_15__*) ; 
 int av_hwframe_ctx_init (TYPE_15__*) ; 
 int /*<<< orphan*/  av_log (TYPE_11__*,int /*<<< orphan*/ ,char*) ; 

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