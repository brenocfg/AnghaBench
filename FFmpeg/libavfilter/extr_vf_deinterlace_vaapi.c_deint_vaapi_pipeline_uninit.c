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
struct TYPE_6__ {TYPE_1__* priv; } ;
struct TYPE_5__ {int queue_count; int /*<<< orphan*/ * frame_queue; } ;
typedef  TYPE_1__ DeintVAAPIContext ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_vaapi_vpp_pipeline_uninit (TYPE_2__*) ; 

__attribute__((used)) static void deint_vaapi_pipeline_uninit(AVFilterContext *avctx)
{
    DeintVAAPIContext *ctx   = avctx->priv;
    int i;

    for (i = 0; i < ctx->queue_count; i++)
        av_frame_free(&ctx->frame_queue[i]);
    ctx->queue_count = 0;

    ff_vaapi_vpp_pipeline_uninit(avctx);
}