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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  enum AVHWDeviceType { ____Placeholder_AVHWDeviceType } AVHWDeviceType ;
struct TYPE_6__ {int type; struct TYPE_6__* hwctx; struct TYPE_6__* internal; struct TYPE_6__* priv; TYPE_1__ const* hw_type; int /*<<< orphan*/ * av_class; } ;
struct TYPE_5__ {int type; int device_priv_size; int device_hwctx_size; } ;
typedef  TYPE_1__ HWContextType ;
typedef  TYPE_2__ AVHWDeviceContext ;
typedef  int /*<<< orphan*/  AVBufferRef ;

/* Variables and functions */
 int /*<<< orphan*/  AV_BUFFER_FLAG_READONLY ; 
 int /*<<< orphan*/ * av_buffer_create (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_freep (TYPE_2__**) ; 
 void* av_mallocz (int) ; 
 TYPE_1__** hw_table ; 
 int /*<<< orphan*/  hwdevice_ctx_class ; 
 int /*<<< orphan*/  hwdevice_ctx_free ; 

AVBufferRef *av_hwdevice_ctx_alloc(enum AVHWDeviceType type)
{
    AVHWDeviceContext *ctx;
    AVBufferRef *buf;
    const HWContextType *hw_type = NULL;
    int i;

    for (i = 0; hw_table[i]; i++) {
        if (hw_table[i]->type == type) {
            hw_type = hw_table[i];
            break;
        }
    }
    if (!hw_type)
        return NULL;

    ctx = av_mallocz(sizeof(*ctx));
    if (!ctx)
        return NULL;

    ctx->internal = av_mallocz(sizeof(*ctx->internal));
    if (!ctx->internal)
        goto fail;

    if (hw_type->device_priv_size) {
        ctx->internal->priv = av_mallocz(hw_type->device_priv_size);
        if (!ctx->internal->priv)
            goto fail;
    }

    if (hw_type->device_hwctx_size) {
        ctx->hwctx = av_mallocz(hw_type->device_hwctx_size);
        if (!ctx->hwctx)
            goto fail;
    }

    buf = av_buffer_create((uint8_t*)ctx, sizeof(*ctx),
                           hwdevice_ctx_free, NULL,
                           AV_BUFFER_FLAG_READONLY);
    if (!buf)
        goto fail;

    ctx->type     = type;
    ctx->av_class = &hwdevice_ctx_class;

    ctx->internal->hw_type = hw_type;

    return buf;

fail:
    if (ctx->internal)
        av_freep(&ctx->internal->priv);
    av_freep(&ctx->internal);
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    return NULL;
}