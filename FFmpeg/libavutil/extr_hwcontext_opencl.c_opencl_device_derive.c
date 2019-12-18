#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  intptr_t cl_context_properties ;
struct TYPE_13__ {int type; TYPE_2__* hwctx; } ;
struct TYPE_12__ {int /*<<< orphan*/ * device; int /*<<< orphan*/  devmgr; int /*<<< orphan*/ * display; } ;
struct TYPE_11__ {int platform_index; int device_index; int /*<<< orphan*/ * filter_device; int /*<<< orphan*/ * enumerate_devices; int /*<<< orphan*/ * filter_platform; int /*<<< orphan*/ * enumerate_platforms; int /*<<< orphan*/ * context; } ;
typedef  TYPE_1__ OpenCLDeviceSelector ;
typedef  int /*<<< orphan*/  IDirect3DDevice9 ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  TYPE_2__ AVVAAPIDeviceContext ;
typedef  TYPE_3__ AVHWDeviceContext ;
typedef  int /*<<< orphan*/  AVDictionary ;
typedef  TYPE_2__ AVDXVA2DeviceContext ;
typedef  TYPE_2__ AVD3D11VADeviceContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_UNKNOWN ; 
#define  AV_HWDEVICE_TYPE_D3D11VA 131 
#define  AV_HWDEVICE_TYPE_DRM 130 
#define  AV_HWDEVICE_TYPE_DXVA2 129 
#define  AV_HWDEVICE_TYPE_VAAPI 128 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 intptr_t CL_CONTEXT_ADAPTER_D3D9EX_KHR ; 
 intptr_t CL_CONTEXT_D3D11_DEVICE_KHR ; 
 intptr_t CL_CONTEXT_INTEROP_USER_SYNC ; 
 intptr_t CL_CONTEXT_PLATFORM ; 
 intptr_t CL_CONTEXT_VA_API_DISPLAY_INTEL ; 
 intptr_t CL_FALSE ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IDirect3DDeviceManager9_CloseDeviceHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IDirect3DDeviceManager9_LockDevice (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ IDirect3DDeviceManager9_OpenDeviceHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DDeviceManager9_UnlockDevice (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUCCEEDED (scalar_t__) ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 int av_dict_set (int /*<<< orphan*/ **,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,unsigned long) ; 
 int opencl_device_create_internal (TYPE_3__*,TYPE_1__*,intptr_t*) ; 
 int /*<<< orphan*/  opencl_enumerate_d3d11_devices ; 
 int /*<<< orphan*/  opencl_enumerate_devices ; 
 int /*<<< orphan*/  opencl_enumerate_dxva2_devices ; 
 int /*<<< orphan*/  opencl_enumerate_intel_media_vaapi_devices ; 
 int /*<<< orphan*/  opencl_enumerate_platforms ; 
 int /*<<< orphan*/  opencl_filter_d3d11_platform ; 
 int /*<<< orphan*/  opencl_filter_drm_arm_device ; 
 int /*<<< orphan*/  opencl_filter_drm_arm_platform ; 
 int /*<<< orphan*/  opencl_filter_dxva2_platform ; 
 int /*<<< orphan*/  opencl_filter_gpu_device ; 
 int /*<<< orphan*/  opencl_filter_intel_media_vaapi_device ; 
 int /*<<< orphan*/  opencl_filter_intel_media_vaapi_platform ; 
 int /*<<< orphan*/  opencl_filter_platform ; 

__attribute__((used)) static int opencl_device_derive(AVHWDeviceContext *hwdev,
                                AVHWDeviceContext *src_ctx,
                                int flags)
{
    int err;
    switch (src_ctx->type) {

#if HAVE_OPENCL_DRM_BEIGNET
    case AV_HWDEVICE_TYPE_DRM:
    case AV_HWDEVICE_TYPE_VAAPI:
        {
            // Surface mapping works via DRM PRIME fds with no special
            // initialisation required in advance.  This just finds the
            // Beignet ICD by name.
            AVDictionary *opts = NULL;

            err = av_dict_set(&opts, "platform_vendor", "Intel", 0);
            if (err >= 0)
                err = av_dict_set(&opts, "platform_version", "beignet", 0);
            if (err >= 0) {
                OpenCLDeviceSelector selector = {
                    .platform_index      = -1,
                    .device_index        = 0,
                    .context             = opts,
                    .enumerate_platforms = &opencl_enumerate_platforms,
                    .filter_platform     = &opencl_filter_platform,
                    .enumerate_devices   = &opencl_enumerate_devices,
                    .filter_device       = NULL,
                };
                err = opencl_device_create_internal(hwdev, &selector, NULL);
            }
            av_dict_free(&opts);
        }
        break;
#endif

#if HAVE_OPENCL_VAAPI_INTEL_MEDIA
        // The generic code automatically attempts to derive from all
        // ancestors of the given device, so we can ignore QSV devices here
        // and just consider the inner VAAPI device it was derived from.
    case AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIDeviceContext *src_hwctx = src_ctx->hwctx;
            cl_context_properties props[7] = {
                CL_CONTEXT_PLATFORM,
                0,
                CL_CONTEXT_VA_API_DISPLAY_INTEL,
                (intptr_t)src_hwctx->display,
                CL_CONTEXT_INTEROP_USER_SYNC,
                CL_FALSE,
                0,
            };
            OpenCLDeviceSelector selector = {
                .platform_index      = -1,
                .device_index        = -1,
                .context             = src_hwctx->display,
                .enumerate_platforms = &opencl_enumerate_platforms,
                .filter_platform     = &opencl_filter_intel_media_vaapi_platform,
                .enumerate_devices   = &opencl_enumerate_intel_media_vaapi_devices,
                .filter_device       = &opencl_filter_intel_media_vaapi_device,
            };

            err = opencl_device_create_internal(hwdev, &selector, props);
        }
        break;
#endif

#if HAVE_OPENCL_DXVA2
    case AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2DeviceContext *src_hwctx = src_ctx->hwctx;
            IDirect3DDevice9 *device;
            HANDLE device_handle;
            HRESULT hr;

            hr = IDirect3DDeviceManager9_OpenDeviceHandle(src_hwctx->devmgr,
                                                          &device_handle);
            if (FAILED(hr)) {
                av_log(hwdev, AV_LOG_ERROR, "Failed to open device handle "
                       "for Direct3D9 device: %lx.\n", (unsigned long)hr);
                err = AVERROR_UNKNOWN;
                break;
            }

            hr = IDirect3DDeviceManager9_LockDevice(src_hwctx->devmgr,
                                                    device_handle,
                                                    &device, FALSE);
            if (SUCCEEDED(hr)) {
                cl_context_properties props[5] = {
                    CL_CONTEXT_PLATFORM,
                    0,
                    CL_CONTEXT_ADAPTER_D3D9EX_KHR,
                    (intptr_t)device,
                    0,
                };
                OpenCLDeviceSelector selector = {
                    .platform_index      = -1,
                    .device_index        = -1,
                    .context             = device,
                    .enumerate_platforms = &opencl_enumerate_platforms,
                    .filter_platform     = &opencl_filter_dxva2_platform,
                    .enumerate_devices   = &opencl_enumerate_dxva2_devices,
                    .filter_device       = &opencl_filter_gpu_device,
                };

                err = opencl_device_create_internal(hwdev, &selector, props);

                IDirect3DDeviceManager9_UnlockDevice(src_hwctx->devmgr,
                                                     device_handle, FALSE);
            } else {
                av_log(hwdev, AV_LOG_ERROR, "Failed to lock device handle "
                       "for Direct3D9 device: %lx.\n", (unsigned long)hr);
                err = AVERROR_UNKNOWN;
            }

            IDirect3DDeviceManager9_CloseDeviceHandle(src_hwctx->devmgr,
                                                      device_handle);
        }
        break;
#endif

#if HAVE_OPENCL_D3D11
    case AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VADeviceContext *src_hwctx = src_ctx->hwctx;
            cl_context_properties props[5] = {
                CL_CONTEXT_PLATFORM,
                0,
                CL_CONTEXT_D3D11_DEVICE_KHR,
                (intptr_t)src_hwctx->device,
                0,
            };
            OpenCLDeviceSelector selector = {
                .platform_index      = -1,
                .device_index        = -1,
                .context             = src_hwctx->device,
                .enumerate_platforms = &opencl_enumerate_platforms,
                .filter_platform     = &opencl_filter_d3d11_platform,
                .enumerate_devices   = &opencl_enumerate_d3d11_devices,
                .filter_device       = &opencl_filter_gpu_device,
            };

            err = opencl_device_create_internal(hwdev, &selector, props);
        }
        break;
#endif

#if HAVE_OPENCL_DRM_ARM
    case AV_HWDEVICE_TYPE_DRM:
        {
            OpenCLDeviceSelector selector = {
                .platform_index      = -1,
                .device_index        = -1,
                .context             = NULL,
                .enumerate_platforms = &opencl_enumerate_platforms,
                .filter_platform     = &opencl_filter_drm_arm_platform,
                .enumerate_devices   = &opencl_enumerate_devices,
                .filter_device       = &opencl_filter_drm_arm_device,
            };

            err = opencl_device_create_internal(hwdev, &selector, NULL);
        }
        break;
#endif

    default:
        err = AVERROR(ENOSYS);
        break;
    }

    return err;
}