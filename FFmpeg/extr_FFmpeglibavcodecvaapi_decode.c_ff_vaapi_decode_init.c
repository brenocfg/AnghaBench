#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ VAStatus ;
struct TYPE_18__ {scalar_t__ va_config; void* va_context; TYPE_4__* hwfc; TYPE_3__* hwctx; TYPE_6__* frames; TYPE_2__* device; } ;
typedef  TYPE_5__ VAAPIDecodeContext ;
struct TYPE_21__ {scalar_t__ data; } ;
struct TYPE_20__ {int /*<<< orphan*/  coded_height; int /*<<< orphan*/  coded_width; TYPE_9__* hw_frames_ctx; TYPE_1__* internal; } ;
struct TYPE_19__ {int /*<<< orphan*/  device_ref; TYPE_2__* device_ctx; TYPE_4__* hwctx; } ;
struct TYPE_17__ {int /*<<< orphan*/  nb_surfaces; int /*<<< orphan*/  surface_ids; } ;
struct TYPE_16__ {int /*<<< orphan*/  display; } ;
struct TYPE_15__ {TYPE_3__* hwctx; } ;
struct TYPE_14__ {TYPE_5__* hwaccel_priv_data; } ;
typedef  TYPE_6__ AVHWFramesContext ;
typedef  TYPE_7__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_HWDEVICE_TYPE_VAAPI ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EIO ; 
 void* VA_INVALID_ID ; 
 int /*<<< orphan*/  VA_PROGRESSIVE ; 
 scalar_t__ VA_STATUS_SUCCESS ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*,scalar_t__,void*) ; 
 int ff_decode_get_hw_frames_ctx (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_vaapi_decode_uninit (TYPE_7__*) ; 
 scalar_t__ vaCreateContext (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 void* vaErrorStr (scalar_t__) ; 
 int vaapi_decode_make_config (TYPE_7__*,int /*<<< orphan*/ ,scalar_t__*,TYPE_9__*) ; 

int ff_vaapi_decode_init(AVCodecContext *avctx)
{
    VAAPIDecodeContext *ctx = avctx->internal->hwaccel_priv_data;
    VAStatus vas;
    int err;

    ctx->va_config  = VA_INVALID_ID;
    ctx->va_context = VA_INVALID_ID;

#if FF_API_STRUCT_VAAPI_CONTEXT
    if (avctx->hwaccel_context) {
        av_log(avctx, AV_LOG_WARNING, "Using deprecated struct "
               "vaapi_context in decode.\n");

        ctx->have_old_context = 1;
        ctx->old_context = avctx->hwaccel_context;

        // Really we only want the VAAPI device context, but this
        // allocates a whole generic device context because we don't
        // have any other way to determine how big it should be.
        ctx->device_ref =
            av_hwdevice_ctx_alloc(AV_HWDEVICE_TYPE_VAAPI);
        if (!ctx->device_ref) {
            err = AVERROR(ENOMEM);
            goto fail;
        }
        ctx->device = (AVHWDeviceContext*)ctx->device_ref->data;
        ctx->hwctx  = ctx->device->hwctx;

        ctx->hwctx->display = ctx->old_context->display;

        // The old VAAPI decode setup assumed this quirk was always
        // present, so set it here to avoid the behaviour changing.
        ctx->hwctx->driver_quirks =
            AV_VAAPI_DRIVER_QUIRK_RENDER_PARAM_BUFFERS;

    }
#endif

#if FF_API_STRUCT_VAAPI_CONTEXT
    if (ctx->have_old_context) {
        ctx->va_config  = ctx->old_context->config_id;
        ctx->va_context = ctx->old_context->context_id;

        av_log(avctx, AV_LOG_DEBUG, "Using user-supplied decoder "
               "context: %#x/%#x.\n", ctx->va_config, ctx->va_context);
    } else {
#endif

    err = ff_decode_get_hw_frames_ctx(avctx, AV_HWDEVICE_TYPE_VAAPI);
    if (err < 0)
        goto fail;

    ctx->frames = (AVHWFramesContext*)avctx->hw_frames_ctx->data;
    ctx->hwfc   = ctx->frames->hwctx;
    ctx->device = ctx->frames->device_ctx;
    ctx->hwctx  = ctx->device->hwctx;

    err = vaapi_decode_make_config(avctx, ctx->frames->device_ref,
                                   &ctx->va_config, avctx->hw_frames_ctx);
    if (err)
        goto fail;

    vas = vaCreateContext(ctx->hwctx->display, ctx->va_config,
                          avctx->coded_width, avctx->coded_height,
                          VA_PROGRESSIVE,
                          ctx->hwfc->surface_ids,
                          ctx->hwfc->nb_surfaces,
                          &ctx->va_context);
    if (vas != VA_STATUS_SUCCESS) {
        av_log(avctx, AV_LOG_ERROR, "Failed to create decode "
               "context: %d (%s).\n", vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        goto fail;
    }

    av_log(avctx, AV_LOG_DEBUG, "Decode context initialised: "
           "%#x/%#x.\n", ctx->va_config, ctx->va_context);
#if FF_API_STRUCT_VAAPI_CONTEXT
    }
#endif

    return 0;

fail:
    ff_vaapi_decode_uninit(avctx);
    return err;
}