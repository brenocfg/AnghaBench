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
struct TYPE_11__ {TYPE_1__* internal; int /*<<< orphan*/ * stream; int /*<<< orphan*/  cuda_ctx; } ;
struct TYPE_10__ {TYPE_4__* hwctx; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* cuCtxPopCurrent ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* cuCtxCreate ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* cuDeviceGet ) (int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  (* cuInit ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {int is_allocated; TYPE_2__* cuda_dl; } ;
typedef  TYPE_2__ CudaFunctions ;
typedef  int /*<<< orphan*/  CUdevice ;
typedef  int /*<<< orphan*/  CUcontext ;
typedef  TYPE_3__ AVHWDeviceContext ;
typedef  int /*<<< orphan*/  AVDictionary ;
typedef  TYPE_4__ AVCUDADeviceContext ;

/* Variables and functions */
 int AVERROR_UNKNOWN ; 
 int CHECK_CU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CU_CTX_SCHED_BLOCKING_SYNC ; 
 scalar_t__ cuda_device_init (TYPE_3__*) ; 
 int /*<<< orphan*/  cuda_device_uninit (TYPE_3__*) ; 
 int strtol (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cuda_device_create(AVHWDeviceContext *device_ctx,
                              const char *device,
                              AVDictionary *opts, int flags)
{
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    CUdevice cu_device;
    CUcontext dummy;
    int ret, device_idx = 0;

    if (device)
        device_idx = strtol(device, NULL, 0);

    if (cuda_device_init(device_ctx) < 0)
        goto error;

    cu = hwctx->internal->cuda_dl;

    ret = CHECK_CU(cu->cuInit(0));
    if (ret < 0)
        goto error;

    ret = CHECK_CU(cu->cuDeviceGet(&cu_device, device_idx));
    if (ret < 0)
        goto error;

    ret = CHECK_CU(cu->cuCtxCreate(&hwctx->cuda_ctx, CU_CTX_SCHED_BLOCKING_SYNC, cu_device));
    if (ret < 0)
        goto error;

    // Setting stream to NULL will make functions automatically use the default CUstream
    hwctx->stream = NULL;

    CHECK_CU(cu->cuCtxPopCurrent(&dummy));

    hwctx->internal->is_allocated = 1;

    return 0;

error:
    cuda_device_uninit(device_ctx);
    return AVERROR_UNKNOWN;
}