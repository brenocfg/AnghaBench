#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  cuda_dl; } ;
struct TYPE_9__ {TYPE_6__* internal; } ;
struct TYPE_8__ {TYPE_2__* hwctx; } ;
typedef  TYPE_1__ AVHWDeviceContext ;
typedef  TYPE_2__ AVCUDADeviceContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_6__* av_mallocz (int) ; 
 int /*<<< orphan*/  cuda_device_uninit (TYPE_1__*) ; 
 int cuda_load_functions (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int cuda_device_init(AVHWDeviceContext *ctx)
{
    AVCUDADeviceContext *hwctx = ctx->hwctx;
    int ret;

    if (!hwctx->internal) {
        hwctx->internal = av_mallocz(sizeof(*hwctx->internal));
        if (!hwctx->internal)
            return AVERROR(ENOMEM);
    }

    if (!hwctx->internal->cuda_dl) {
        ret = cuda_load_functions(&hwctx->internal->cuda_dl, ctx);
        if (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Could not dynamically load CUDA\n");
            goto error;
        }
    }

    return 0;

error:
    cuda_device_uninit(ctx);
    return ret;
}