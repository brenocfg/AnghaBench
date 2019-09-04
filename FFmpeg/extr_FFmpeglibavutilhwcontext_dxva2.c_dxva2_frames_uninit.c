#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  devmgr; } ;
struct TYPE_12__ {int nb_surfaces; scalar_t__ decoder_to_release; } ;
struct TYPE_11__ {TYPE_2__* internal; TYPE_5__* hwctx; TYPE_1__* device_ctx; } ;
struct TYPE_10__ {scalar_t__ device_handle; int /*<<< orphan*/ * service; scalar_t__* surfaces_internal; } ;
struct TYPE_9__ {TYPE_3__* priv; } ;
struct TYPE_8__ {TYPE_6__* hwctx; } ;
typedef  TYPE_3__ DXVA2FramesContext ;
typedef  TYPE_4__ AVHWFramesContext ;
typedef  TYPE_5__ AVDXVA2FramesContext ;
typedef  TYPE_6__ AVDXVA2DeviceContext ;

/* Variables and functions */
 int /*<<< orphan*/  IDirect3DDeviceManager9_CloseDeviceHandle (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  IDirect3DSurface9_Release (scalar_t__) ; 
 int /*<<< orphan*/  IDirectXVideoAccelerationService_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirectXVideoDecoder_Release (scalar_t__) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  av_freep (scalar_t__**) ; 

__attribute__((used)) static void dxva2_frames_uninit(AVHWFramesContext *ctx)
{
    AVDXVA2DeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    AVDXVA2FramesContext *frames_hwctx = ctx->hwctx;
    DXVA2FramesContext *s = ctx->internal->priv;
    int i;

    if (frames_hwctx->decoder_to_release)
        IDirectXVideoDecoder_Release(frames_hwctx->decoder_to_release);

    if (s->surfaces_internal) {
        for (i = 0; i < frames_hwctx->nb_surfaces; i++) {
            if (s->surfaces_internal[i])
                IDirect3DSurface9_Release(s->surfaces_internal[i]);
        }
    }
    av_freep(&s->surfaces_internal);

    if (s->service) {
        IDirectXVideoAccelerationService_Release(s->service);
        s->service = NULL;
    }

    if (s->device_handle != INVALID_HANDLE_VALUE) {
        IDirect3DDeviceManager9_CloseDeviceHandle(device_hwctx->devmgr, s->device_handle);
        s->device_handle = INVALID_HANDLE_VALUE;
    }
}