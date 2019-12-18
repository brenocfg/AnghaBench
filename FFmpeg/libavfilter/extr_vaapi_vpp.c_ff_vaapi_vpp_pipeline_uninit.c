#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int nb_filter_buffers; scalar_t__* filter_buffers; scalar_t__ va_context; scalar_t__ va_config; TYPE_1__* hwctx; int /*<<< orphan*/  device_ref; } ;
typedef  TYPE_2__ VAAPIVPPContext ;
struct TYPE_7__ {TYPE_2__* priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  display; } ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 scalar_t__ VA_INVALID_ID ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vaDestroyBuffer (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vaDestroyConfig (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vaDestroyContext (int /*<<< orphan*/ ,scalar_t__) ; 

void ff_vaapi_vpp_pipeline_uninit(AVFilterContext *avctx)
{
    VAAPIVPPContext *ctx   = avctx->priv;
    int i;
    for (i = 0; i < ctx->nb_filter_buffers; i++) {
        if (ctx->filter_buffers[i] != VA_INVALID_ID) {
            vaDestroyBuffer(ctx->hwctx->display, ctx->filter_buffers[i]);
            ctx->filter_buffers[i] = VA_INVALID_ID;
        }
    }
    ctx->nb_filter_buffers = 0;

    if (ctx->va_context != VA_INVALID_ID) {
        vaDestroyContext(ctx->hwctx->display, ctx->va_context);
        ctx->va_context = VA_INVALID_ID;
    }

    if (ctx->va_config != VA_INVALID_ID) {
        vaDestroyConfig(ctx->hwctx->display, ctx->va_config);
        ctx->va_config = VA_INVALID_ID;
    }

    av_buffer_unref(&ctx->device_ref);
    ctx->hwctx = NULL;
}