#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_10__ {int /*<<< orphan*/  cuda_ctx; TYPE_1__* internal; } ;
struct TYPE_9__ {TYPE_5__* hwctx; } ;
struct TYPE_8__ {TYPE_4__* device_ctx; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* cuCtxPopCurrent ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* cuMemFree ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* cuCtxPushCurrent ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {TYPE_2__* cuda_dl; } ;
typedef  TYPE_2__ CudaFunctions ;
typedef  int /*<<< orphan*/  CUdeviceptr ;
typedef  int /*<<< orphan*/  CUcontext ;
typedef  TYPE_3__ AVHWFramesContext ;
typedef  TYPE_4__ AVHWDeviceContext ;
typedef  TYPE_5__ AVCUDADeviceContext ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cuda_buffer_free(void *opaque, uint8_t *data)
{
    AVHWFramesContext        *ctx = opaque;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    CUcontext dummy;

    CHECK_CU(cu->cuCtxPushCurrent(hwctx->cuda_ctx));

    CHECK_CU(cu->cuMemFree((CUdeviceptr)data));

    CHECK_CU(cu->cuCtxPopCurrent(&dummy));
}