#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ devmgr; } ;
struct TYPE_7__ {TYPE_1__* user_opaque; TYPE_3__* hwctx; } ;
struct TYPE_6__ {scalar_t__ device_handle; scalar_t__ dxva2lib; scalar_t__ d3dlib; scalar_t__ d3d9; scalar_t__ d3d9device; } ;
typedef  TYPE_1__ DXVA2DevicePriv ;
typedef  TYPE_2__ AVHWDeviceContext ;
typedef  TYPE_3__ AVDXVA2DeviceContext ;

/* Variables and functions */
 int /*<<< orphan*/  IDirect3D9_Release (scalar_t__) ; 
 int /*<<< orphan*/  IDirect3DDevice9_Release (scalar_t__) ; 
 int /*<<< orphan*/  IDirect3DDeviceManager9_CloseDeviceHandle (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  IDirect3DDeviceManager9_Release (scalar_t__) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 
 int /*<<< orphan*/  dlclose (scalar_t__) ; 

__attribute__((used)) static void dxva2_device_free(AVHWDeviceContext *ctx)
{
    AVDXVA2DeviceContext *hwctx = ctx->hwctx;
    DXVA2DevicePriv       *priv = ctx->user_opaque;

    if (hwctx->devmgr && priv->device_handle != INVALID_HANDLE_VALUE)
        IDirect3DDeviceManager9_CloseDeviceHandle(hwctx->devmgr, priv->device_handle);

    if (hwctx->devmgr)
        IDirect3DDeviceManager9_Release(hwctx->devmgr);

    if (priv->d3d9device)
        IDirect3DDevice9_Release(priv->d3d9device);

    if (priv->d3d9)
        IDirect3D9_Release(priv->d3d9);

    if (priv->d3dlib)
        dlclose(priv->d3dlib);

    if (priv->dxva2lib)
        dlclose(priv->dxva2lib);

    av_freep(&ctx->user_opaque);
}