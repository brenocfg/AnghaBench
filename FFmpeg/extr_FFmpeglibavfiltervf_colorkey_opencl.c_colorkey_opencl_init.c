#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cl_int ;
struct TYPE_12__ {TYPE_4__* priv; } ;
struct TYPE_10__ {float* s; } ;
struct TYPE_9__ {int /*<<< orphan*/  program; TYPE_1__* hwctx; } ;
struct TYPE_11__ {double blend; int initialized; void* kernel_colorkey; scalar_t__ command_queue; scalar_t__* colorkey_rgba; TYPE_3__ colorkey_rgba_float; TYPE_2__ ocf; } ;
struct TYPE_8__ {int /*<<< orphan*/  device_id; int /*<<< orphan*/  context; } ;
typedef  TYPE_4__ ColorkeyOpenCLContext ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CL_FAIL_ON_ERROR (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EIO ; 
 scalar_t__ clCreateCommandQueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* clCreateKernel (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clReleaseCommandQueue (scalar_t__) ; 
 int /*<<< orphan*/  clReleaseKernel (void*) ; 
 int ff_opencl_filter_load_program (TYPE_5__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ff_opencl_source_colorkey ; 

__attribute__((used)) static int colorkey_opencl_init(AVFilterContext *avctx)
{
    ColorkeyOpenCLContext *ctx = avctx->priv;
    cl_int cle;
    int err;

    err = ff_opencl_filter_load_program(avctx, &ff_opencl_source_colorkey, 1);
    if (err < 0)
        goto fail;

    ctx->command_queue = clCreateCommandQueue(
        ctx->ocf.hwctx->context,
        ctx->ocf.hwctx->device_id,
        0,
        &cle
    );

    CL_FAIL_ON_ERROR(AVERROR(EIO), "Failed to create OpenCL command queue %d.\n", cle);

    if (ctx->blend > 0.0001) {
        ctx->kernel_colorkey = clCreateKernel(ctx->ocf.program, "colorkey_blend", &cle);
        CL_FAIL_ON_ERROR(AVERROR(EIO), "Failed to create colorkey_blend kernel: %d.\n", cle);
    } else {
        ctx->kernel_colorkey = clCreateKernel(ctx->ocf.program, "colorkey", &cle);
        CL_FAIL_ON_ERROR(AVERROR(EIO), "Failed to create colorkey kernel: %d.\n", cle);
    }

    for (int i = 0; i < 4; ++i) {
        ctx->colorkey_rgba_float.s[i] = (float)ctx->colorkey_rgba[i] / 255.0;
    }

    ctx->initialized = 1;
    return 0;

fail:
    if (ctx->command_queue)
        clReleaseCommandQueue(ctx->command_queue);
    if (ctx->kernel_colorkey)
        clReleaseKernel(ctx->kernel_colorkey);
    return err;
}