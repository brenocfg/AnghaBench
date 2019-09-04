#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ surface_type; } ;
struct TYPE_10__ {int /*<<< orphan*/  pool; TYPE_1__* internal; TYPE_4__* hwctx; } ;
struct TYPE_9__ {int /*<<< orphan*/  device_handle; } ;
struct TYPE_8__ {TYPE_2__* priv; } ;
typedef  TYPE_2__ DXVA2FramesContext ;
typedef  TYPE_3__ AVHWFramesContext ;
typedef  TYPE_4__ AVDXVA2FramesContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ DXVA2_VideoDecoderRenderTarget ; 
 scalar_t__ DXVA2_VideoProcessorRenderTarget ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 int dxva2_init_pool (TYPE_3__*) ; 

__attribute__((used)) static int dxva2_frames_init(AVHWFramesContext *ctx)
{
    AVDXVA2FramesContext *hwctx = ctx->hwctx;
    DXVA2FramesContext       *s = ctx->internal->priv;
    int ret;

    if (hwctx->surface_type != DXVA2_VideoDecoderRenderTarget &&
        hwctx->surface_type != DXVA2_VideoProcessorRenderTarget) {
        av_log(ctx, AV_LOG_ERROR, "Unknown surface type: %lu\n",
               hwctx->surface_type);
        return AVERROR(EINVAL);
    }

    s->device_handle = INVALID_HANDLE_VALUE;

    /* init the frame pool if the caller didn't provide one */
    if (!ctx->pool) {
        ret = dxva2_init_pool(ctx);
        if (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Error creating an internal frame pool\n");
            return ret;
        }
    }

    return 0;
}