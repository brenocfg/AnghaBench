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
typedef  scalar_t__ cl_int ;
struct TYPE_11__ {TYPE_3__* priv; } ;
struct TYPE_9__ {int /*<<< orphan*/  program; TYPE_1__* hwctx; } ;
struct TYPE_10__ {scalar_t__ kernel_name; int loaded; int /*<<< orphan*/  kernel; TYPE_2__ ocf; int /*<<< orphan*/  command_queue; int /*<<< orphan*/  source_file; } ;
struct TYPE_8__ {int /*<<< orphan*/  device_id; int /*<<< orphan*/  context; } ;
typedef  TYPE_3__ ProgramOpenCLContext ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ CL_INVALID_KERNEL_NAME ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  clCreateCommandQueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  clCreateKernel (int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int ff_opencl_filter_load_program_from_file (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int program_opencl_load(AVFilterContext *avctx)
{
    ProgramOpenCLContext *ctx = avctx->priv;
    cl_int cle;
    int err;

    err = ff_opencl_filter_load_program_from_file(avctx, ctx->source_file);
    if (err < 0)
        return err;

    ctx->command_queue = clCreateCommandQueue(ctx->ocf.hwctx->context,
                                              ctx->ocf.hwctx->device_id,
                                              0, &cle);
    if (!ctx->command_queue) {
        av_log(avctx, AV_LOG_ERROR, "Failed to create OpenCL "
               "command queue: %d.\n", cle);
        return AVERROR(EIO);
    }

    ctx->kernel = clCreateKernel(ctx->ocf.program, ctx->kernel_name, &cle);
    if (!ctx->kernel) {
        if (cle == CL_INVALID_KERNEL_NAME) {
            av_log(avctx, AV_LOG_ERROR, "Kernel function '%s' not found in "
                   "program.\n", ctx->kernel_name);
        } else {
            av_log(avctx, AV_LOG_ERROR, "Failed to create kernel: %d.\n", cle);
        }
        return AVERROR(EIO);
    }

    ctx->loaded = 1;
    return 0;
}