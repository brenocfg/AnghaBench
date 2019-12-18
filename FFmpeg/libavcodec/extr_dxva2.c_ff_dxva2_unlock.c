#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ context_mutex; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock_ctx; int /*<<< orphan*/  (* unlock ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {TYPE_1__* device_ctx; } ;
struct TYPE_6__ {TYPE_3__* hwctx; } ;
typedef  TYPE_2__ FFDXVASharedContext ;
typedef  int /*<<< orphan*/  AVDXVAContext ;
typedef  TYPE_3__ AVD3D11VADeviceContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 TYPE_5__* D3D11VA_CONTEXT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DXVA_CONTEXT (int /*<<< orphan*/ *) ; 
 TYPE_2__* DXVA_SHARED_CONTEXT (int /*<<< orphan*/ *) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  ReleaseMutex (scalar_t__) ; 
 scalar_t__ ff_dxva2_is_d3d11 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ff_dxva2_unlock(AVCodecContext *avctx)
{
#if CONFIG_D3D11VA
    if (ff_dxva2_is_d3d11(avctx)) {
        FFDXVASharedContext *sctx = DXVA_SHARED_CONTEXT(avctx);
        AVDXVAContext *ctx = DXVA_CONTEXT(avctx);
        if (D3D11VA_CONTEXT(ctx)->context_mutex != INVALID_HANDLE_VALUE)
            ReleaseMutex(D3D11VA_CONTEXT(ctx)->context_mutex);
        if (sctx->device_ctx) {
            AVD3D11VADeviceContext *hwctx = sctx->device_ctx->hwctx;
            hwctx->unlock(hwctx->lock_ctx);
        }
    }
#endif
}