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
typedef  int /*<<< orphan*/  cl_int ;
struct TYPE_11__ {TYPE_3__* priv; } ;
struct TYPE_9__ {TYPE_1__* hwctx; int /*<<< orphan*/  program; } ;
struct TYPE_10__ {int h; int sigma; int research_size; int patch_size; int research_size_uv; int patch_size_uv; int initialised; int /*<<< orphan*/  command_queue; void* overflow; void* sum; void* weight; void* integral_img; void* average_kernel; void* accum_kernel; void* horiz_kernel; void* vert_kernel; TYPE_2__ ocf; } ;
struct TYPE_8__ {int /*<<< orphan*/  context; int /*<<< orphan*/  device_id; } ;
typedef  TYPE_3__ NLMeansOpenCLContext ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  CL_FAIL_ON_ERROR (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CL_RELEASE_KERNEL (void*) ; 
 int /*<<< orphan*/  CL_RELEASE_MEMORY (void*) ; 
 int /*<<< orphan*/  CL_RELEASE_QUEUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,int) ; 
 void* clCreateBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clCreateCommandQueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* clCreateKernel (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int ff_opencl_filter_load_program (TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ff_opencl_source_nlmeans ; 

__attribute__((used)) static int nlmeans_opencl_init(AVFilterContext *avctx, int width, int height)
{
    NLMeansOpenCLContext *ctx = avctx->priv;
    cl_int cle;
    int err;
    int weight_buf_size = width * height * sizeof(float);

    ctx->h = ctx->sigma * 10;
    if (!(ctx->research_size & 1)) {
        ctx->research_size |= 1;
        av_log(avctx, AV_LOG_WARNING,
               "research_size should be odd, set to %d",
               ctx->research_size);
    }

    if (!(ctx->patch_size & 1)) {
        ctx->patch_size |= 1;
        av_log(avctx, AV_LOG_WARNING,
               "patch_size should be odd, set to %d",
               ctx->patch_size);
    }

    if (!ctx->research_size_uv)
        ctx->research_size_uv = ctx->research_size;
    if (!ctx->patch_size_uv)
        ctx->patch_size_uv = ctx->patch_size;

    err = ff_opencl_filter_load_program(avctx, &ff_opencl_source_nlmeans, 1);
    if (err < 0)
        goto fail;

    ctx->command_queue = clCreateCommandQueue(ctx->ocf.hwctx->context,
                                              ctx->ocf.hwctx->device_id,
                                              0, &cle);
    CL_FAIL_ON_ERROR(AVERROR(EIO), "Failed to create OpenCL "
                     "command queue %d.\n", cle);

    ctx->vert_kernel = clCreateKernel(ctx->ocf.program,
                                      "vert_sum", &cle);
    CL_FAIL_ON_ERROR(AVERROR(EIO), "Failed to create "
                     "vert_sum kernel %d.\n", cle);

    ctx->horiz_kernel = clCreateKernel(ctx->ocf.program,
                                       "horiz_sum", &cle);
    CL_FAIL_ON_ERROR(AVERROR(EIO), "Failed to create "
                     "horiz_sum kernel %d.\n", cle);

    ctx->accum_kernel = clCreateKernel(ctx->ocf.program,
                                       "weight_accum", &cle);
    CL_FAIL_ON_ERROR(AVERROR(EIO), "Failed to create "
                     "accum kernel %d.\n", cle);

    ctx->average_kernel = clCreateKernel(ctx->ocf.program,
                                         "average", &cle);
    CL_FAIL_ON_ERROR(AVERROR(EIO), "Failed to create "
                     "average kernel %d.\n", cle);

    ctx->integral_img = clCreateBuffer(ctx->ocf.hwctx->context, 0,
                                       4 * width * height * sizeof(cl_int),
                                       NULL, &cle);
    CL_FAIL_ON_ERROR(AVERROR(EIO), "Failed to create "
                     "integral image %d.\n", cle);

    ctx->weight = clCreateBuffer(ctx->ocf.hwctx->context, 0,
                                 weight_buf_size, NULL, &cle);
    CL_FAIL_ON_ERROR(AVERROR(EIO), "Failed to create "
                     "weight buffer %d.\n", cle);

    ctx->sum = clCreateBuffer(ctx->ocf.hwctx->context, 0,
                              weight_buf_size, NULL, &cle);
    CL_FAIL_ON_ERROR(AVERROR(EIO), "Failed to create "
                     "sum buffer %d.\n", cle);

    ctx->overflow = clCreateBuffer(ctx->ocf.hwctx->context, 0,
                                   sizeof(cl_int), NULL, &cle);
    CL_FAIL_ON_ERROR(AVERROR(EIO), "Failed to create "
                     "overflow buffer %d.\n", cle);

    ctx->initialised = 1;
    return 0;

fail:
    CL_RELEASE_KERNEL(ctx->vert_kernel);
    CL_RELEASE_KERNEL(ctx->horiz_kernel);
    CL_RELEASE_KERNEL(ctx->accum_kernel);
    CL_RELEASE_KERNEL(ctx->average_kernel);

    CL_RELEASE_MEMORY(ctx->integral_img);
    CL_RELEASE_MEMORY(ctx->weight);
    CL_RELEASE_MEMORY(ctx->sum);
    CL_RELEASE_MEMORY(ctx->overflow);

    CL_RELEASE_QUEUE(ctx->command_queue);
    return err;
}