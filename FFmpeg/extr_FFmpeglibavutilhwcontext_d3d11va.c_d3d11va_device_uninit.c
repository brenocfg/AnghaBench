#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * lock; int /*<<< orphan*/  lock_ctx; int /*<<< orphan*/ * video_context; int /*<<< orphan*/ * video_device; int /*<<< orphan*/ * device_context; int /*<<< orphan*/ * device; } ;
struct TYPE_4__ {TYPE_2__* hwctx; } ;
typedef  TYPE_1__ AVHWDeviceContext ;
typedef  TYPE_2__ AVD3D11VADeviceContext ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ID3D11DeviceContext_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D11Device_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D11VideoContext_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D11VideoDevice_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/ * d3d11va_default_lock ; 

__attribute__((used)) static void d3d11va_device_uninit(AVHWDeviceContext *hwdev)
{
    AVD3D11VADeviceContext *device_hwctx = hwdev->hwctx;

    if (device_hwctx->device) {
        ID3D11Device_Release(device_hwctx->device);
        device_hwctx->device = NULL;
    }

    if (device_hwctx->device_context) {
        ID3D11DeviceContext_Release(device_hwctx->device_context);
        device_hwctx->device_context = NULL;
    }

    if (device_hwctx->video_device) {
        ID3D11VideoDevice_Release(device_hwctx->video_device);
        device_hwctx->video_device = NULL;
    }

    if (device_hwctx->video_context) {
        ID3D11VideoContext_Release(device_hwctx->video_context);
        device_hwctx->video_context = NULL;
    }

    if (device_hwctx->lock == d3d11va_default_lock) {
        CloseHandle(device_hwctx->lock_ctx);
        device_hwctx->lock_ctx = INVALID_HANDLE_VALUE;
        device_hwctx->lock = NULL;
    }
}