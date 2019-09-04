#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */

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