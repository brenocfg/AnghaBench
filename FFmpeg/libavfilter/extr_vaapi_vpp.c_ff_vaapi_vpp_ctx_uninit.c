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
struct TYPE_5__ {int /*<<< orphan*/  device_ref; int /*<<< orphan*/  input_frames_ref; int /*<<< orphan*/  (* pipeline_uninit ) (TYPE_2__*) ;scalar_t__ valid_ids; } ;
typedef  TYPE_1__ VAAPIVPPContext ;
struct TYPE_6__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void ff_vaapi_vpp_ctx_uninit(AVFilterContext *avctx)
{
    VAAPIVPPContext *ctx   = avctx->priv;
    if (ctx->valid_ids && ctx->pipeline_uninit)
        ctx->pipeline_uninit(avctx);

    av_buffer_unref(&ctx->input_frames_ref);
    av_buffer_unref(&ctx->device_ref);
}