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
struct TYPE_12__ {TYPE_2__* filter; TYPE_4__* priv; } ;
struct TYPE_10__ {int /*<<< orphan*/  program; TYPE_1__* hwctx; } ;
struct TYPE_11__ {int initialised; scalar_t__ kernel; scalar_t__ command_queue; TYPE_3__ ocf; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int /*<<< orphan*/  device_id; int /*<<< orphan*/  context; } ;
typedef  TYPE_4__ ConvolutionOpenCLContext ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CL_FAIL_ON_ERROR (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EIO ; 
 scalar_t__ clCreateCommandQueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ clCreateKernel (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clReleaseCommandQueue (scalar_t__) ; 
 int /*<<< orphan*/  clReleaseKernel (scalar_t__) ; 
 int ff_opencl_filter_load_program (TYPE_5__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ff_opencl_source_convolution ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int convolution_opencl_init(AVFilterContext *avctx)
{
    ConvolutionOpenCLContext *ctx = avctx->priv;
    const char *kernel_name;
    cl_int cle;
    int err;

    err = ff_opencl_filter_load_program(avctx, &ff_opencl_source_convolution, 1);
    if (err < 0)
        goto fail;

    ctx->command_queue = clCreateCommandQueue(ctx->ocf.hwctx->context,
                                              ctx->ocf.hwctx->device_id,
                                              0, &cle);
    CL_FAIL_ON_ERROR(AVERROR(EIO), "Failed to create OpenCL "
                     "command queue %d.\n", cle);

    if (!strcmp(avctx->filter->name, "convolution_opencl")) {
        kernel_name = "convolution_global";
    } else if (!strcmp(avctx->filter->name, "sobel_opencl")) {
        kernel_name = "sobel_global";
    } else if (!strcmp(avctx->filter->name, "prewitt_opencl")){
        kernel_name = "prewitt_global";
    } else if (!strcmp(avctx->filter->name, "roberts_opencl")){
        kernel_name = "roberts_global";
    }
    ctx->kernel = clCreateKernel(ctx->ocf.program, kernel_name, &cle);
    CL_FAIL_ON_ERROR(AVERROR(EIO), "Failed to create "
                     "kernel %d.\n", cle);

    ctx->initialised = 1;
    return 0;

fail:
    if (ctx->command_queue)
        clReleaseCommandQueue(ctx->command_queue);
    if (ctx->kernel)
        clReleaseKernel(ctx->kernel);
    return err;
}