#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {struct TYPE_7__* internal; struct TYPE_7__* priv; struct TYPE_7__* hwctx; int /*<<< orphan*/  source_device; int /*<<< orphan*/  (* free ) (TYPE_2__*) ;TYPE_1__* hw_type; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* device_uninit ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ AVHWDeviceContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (TYPE_2__**) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 

__attribute__((used)) static void hwdevice_ctx_free(void *opaque, uint8_t *data)
{
    AVHWDeviceContext *ctx = (AVHWDeviceContext*)data;

    /* uninit might still want access the hw context and the user
     * free() callback might destroy it, so uninit has to be called first */
    if (ctx->internal->hw_type->device_uninit)
        ctx->internal->hw_type->device_uninit(ctx);

    if (ctx->free)
        ctx->free(ctx);

    av_buffer_unref(&ctx->internal->source_device);

    av_freep(&ctx->hwctx);
    av_freep(&ctx->internal->priv);
    av_freep(&ctx->internal);
    av_freep(&ctx);
}