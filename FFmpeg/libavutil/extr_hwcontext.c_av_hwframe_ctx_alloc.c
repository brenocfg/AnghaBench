#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_17__ {scalar_t__ data; } ;
struct TYPE_16__ {TYPE_1__* internal; } ;
struct TYPE_15__ {struct TYPE_15__* hwctx; struct TYPE_15__* internal; struct TYPE_15__* priv; TYPE_2__ const* hw_type; void* sw_format; void* format; TYPE_4__* device_ctx; TYPE_5__* device_ref; int /*<<< orphan*/ * av_class; } ;
struct TYPE_14__ {int frames_priv_size; int frames_hwctx_size; } ;
struct TYPE_13__ {TYPE_2__* hw_type; } ;
typedef  TYPE_2__ HWContextType ;
typedef  TYPE_3__ AVHWFramesContext ;
typedef  TYPE_4__ AVHWDeviceContext ;
typedef  TYPE_5__ AVBufferRef ;

/* Variables and functions */
 int /*<<< orphan*/  AV_BUFFER_FLAG_READONLY ; 
 void* AV_PIX_FMT_NONE ; 
 TYPE_5__* av_buffer_create (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_5__* av_buffer_ref (TYPE_5__*) ; 
 int /*<<< orphan*/  av_buffer_unref (TYPE_5__**) ; 
 int /*<<< orphan*/  av_freep (TYPE_3__**) ; 
 void* av_mallocz (int) ; 
 int /*<<< orphan*/  hwframe_ctx_class ; 
 int /*<<< orphan*/  hwframe_ctx_free ; 

AVBufferRef *av_hwframe_ctx_alloc(AVBufferRef *device_ref_in)
{
    AVHWDeviceContext *device_ctx = (AVHWDeviceContext*)device_ref_in->data;
    const HWContextType  *hw_type = device_ctx->internal->hw_type;
    AVHWFramesContext *ctx;
    AVBufferRef *buf, *device_ref = NULL;

    ctx = av_mallocz(sizeof(*ctx));
    if (!ctx)
        return NULL;

    ctx->internal = av_mallocz(sizeof(*ctx->internal));
    if (!ctx->internal)
        goto fail;

    if (hw_type->frames_priv_size) {
        ctx->internal->priv = av_mallocz(hw_type->frames_priv_size);
        if (!ctx->internal->priv)
            goto fail;
    }

    if (hw_type->frames_hwctx_size) {
        ctx->hwctx = av_mallocz(hw_type->frames_hwctx_size);
        if (!ctx->hwctx)
            goto fail;
    }

    device_ref = av_buffer_ref(device_ref_in);
    if (!device_ref)
        goto fail;

    buf = av_buffer_create((uint8_t*)ctx, sizeof(*ctx),
                           hwframe_ctx_free, NULL,
                           AV_BUFFER_FLAG_READONLY);
    if (!buf)
        goto fail;

    ctx->av_class   = &hwframe_ctx_class;
    ctx->device_ref = device_ref;
    ctx->device_ctx = device_ctx;
    ctx->format     = AV_PIX_FMT_NONE;
    ctx->sw_format  = AV_PIX_FMT_NONE;

    ctx->internal->hw_type = hw_type;

    return buf;

fail:
    if (device_ref)
        av_buffer_unref(&device_ref);
    if (ctx->internal)
        av_freep(&ctx->internal->priv);
    av_freep(&ctx->internal);
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    return NULL;
}