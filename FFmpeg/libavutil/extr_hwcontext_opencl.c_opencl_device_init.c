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
typedef  scalar_t__ cl_context_properties ;
typedef  int /*<<< orphan*/ * VADisplay ;
struct TYPE_11__ {TYPE_1__* internal; TYPE_3__* hwctx; } ;
struct TYPE_10__ {int /*<<< orphan*/  context; int /*<<< orphan*/  device_id; scalar_t__ command_queue; } ;
struct TYPE_9__ {int beignet_drm_mapping_usable; int qsv_mapping_usable; int dxva2_mapping_usable; int d3d11_mapping_usable; int drm_arm_mapping_usable; int /*<<< orphan*/  dx9_media_adapter_type; int /*<<< orphan*/  platform_id; scalar_t__ command_queue; } ;
struct TYPE_8__ {TYPE_2__* priv; } ;
typedef  TYPE_2__ OpenCLDeviceContext ;
typedef  TYPE_3__ AVOpenCLDeviceContext ;
typedef  TYPE_4__ AVHWDeviceContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  CL_ADAPTER_D3D9EX_KHR ; 
 int /*<<< orphan*/  CL_CONTEXT_PROPERTIES ; 
 scalar_t__ CL_CONTEXT_VA_API_DISPLAY_INTEL ; 
 int /*<<< orphan*/  CL_DEVICE_PLATFORM ; 
 int /*<<< orphan*/  CL_FUNC (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CL_SUCCESS ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_free (scalar_t__*) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__* av_malloc (size_t) ; 
 scalar_t__ clCreateCommandQueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clCreateFromD3D11Texture2DKHR ; 
 int /*<<< orphan*/  clCreateFromDX9MediaSurfaceKHR ; 
 int /*<<< orphan*/  clCreateFromVA_APIMediaSurfaceINTEL ; 
 int /*<<< orphan*/  clCreateImageFromFdINTEL ; 
 int /*<<< orphan*/  clEnqueueAcquireD3D11ObjectsKHR ; 
 int /*<<< orphan*/  clEnqueueAcquireDX9MediaSurfacesKHR ; 
 int /*<<< orphan*/  clEnqueueAcquireVA_APIMediaSurfacesINTEL ; 
 int /*<<< orphan*/  clEnqueueReleaseD3D11ObjectsKHR ; 
 int /*<<< orphan*/  clEnqueueReleaseDX9MediaSurfacesKHR ; 
 int /*<<< orphan*/  clEnqueueReleaseVA_APIMediaSurfacesINTEL ; 
 int /*<<< orphan*/  clGetContextInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,scalar_t__*,size_t*) ; 
 int /*<<< orphan*/  clGetDeviceInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clRetainCommandQueue (scalar_t__) ; 
 int /*<<< orphan*/  opencl_check_extension (TYPE_4__*,char const*) ; 
 int /*<<< orphan*/  vaDisplayIsValid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int opencl_device_init(AVHWDeviceContext *hwdev)
{
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    OpenCLDeviceContext    *priv = hwdev->internal->priv;
    cl_int cle;

    if (hwctx->command_queue) {
        cle = clRetainCommandQueue(hwctx->command_queue);
        if (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to retain external "
                   "command queue: %d.\n", cle);
            return AVERROR(EIO);
        }
        priv->command_queue = hwctx->command_queue;
    } else {
        priv->command_queue = clCreateCommandQueue(hwctx->context,
                                                   hwctx->device_id,
                                                   0, &cle);
        if (!priv->command_queue) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to create internal "
                   "command queue: %d.\n", cle);
            return AVERROR(EIO);
        }
    }

    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_PLATFORM,
                          sizeof(priv->platform_id), &priv->platform_id,
                          NULL);
    if (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to determine the OpenCL "
               "platform containing the device.\n");
        return AVERROR(EIO);
    }

#define CL_FUNC(name, desc) do {                                \
        if (fail)                                               \
            break;                                              \
        priv->name = clGetExtensionFunctionAddressForPlatform(  \
            priv->platform_id, #name);                          \
        if (!priv->name) {                                      \
            av_log(hwdev, AV_LOG_VERBOSE,                       \
                   desc " function not found (%s).\n", #name);  \
            fail = 1;                                           \
        } else {                                                \
            av_log(hwdev, AV_LOG_VERBOSE,                       \
                   desc " function found (%s).\n", #name);      \
        }                                                       \
    } while (0)

#if HAVE_OPENCL_DRM_BEIGNET
    {
        int fail = 0;

        CL_FUNC(clCreateImageFromFdINTEL,
                "Beignet DRM to OpenCL image mapping");

        if (fail) {
            av_log(hwdev, AV_LOG_WARNING, "Beignet DRM to OpenCL "
                   "mapping not usable.\n");
            priv->beignet_drm_mapping_usable = 0;
        } else {
            priv->beignet_drm_mapping_usable = 1;
        }
    }
#endif

#if HAVE_OPENCL_VAAPI_INTEL_MEDIA
    {
        size_t props_size;
        cl_context_properties *props = NULL;
        VADisplay va_display;
        const char *va_ext = "cl_intel_va_api_media_sharing";
        int i, fail = 0;

        if (!opencl_check_extension(hwdev, va_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for QSV to OpenCL mapping.\n", va_ext);
            goto no_qsv;
        }

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               0, NULL, &props_size);
        if (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            goto no_qsv;
        }
        if (props_size == 0) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            goto no_qsv;
        }

        props = av_malloc(props_size);
        if (!props)
            return AVERROR(ENOMEM);

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               props_size, props, NULL);
        if (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            goto no_qsv;
        }

        va_display = NULL;
        for (i = 0; i < (props_size / sizeof(*props) - 1); i++) {
            if (props[i] == CL_CONTEXT_VA_API_DISPLAY_INTEL) {
                va_display = (VADisplay)(intptr_t)props[i+1];
                break;
            }
        }
        if (!va_display) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            goto no_qsv;
        }
        if (!vaDisplayIsValid(va_display)) {
            av_log(hwdev, AV_LOG_VERBOSE, "A valid VADisplay is "
                   "required on context creation to use QSV to "
                   "OpenCL mapping.\n");
            goto no_qsv;
        }

        CL_FUNC(clCreateFromVA_APIMediaSurfaceINTEL,
                "Intel QSV to OpenCL mapping");
        CL_FUNC(clEnqueueAcquireVA_APIMediaSurfacesINTEL,
                "Intel QSV in OpenCL acquire");
        CL_FUNC(clEnqueueReleaseVA_APIMediaSurfacesINTEL,
                "Intel QSV in OpenCL release");

        if (fail) {
        no_qsv:
            av_log(hwdev, AV_LOG_WARNING, "QSV to OpenCL mapping "
                   "not usable.\n");
            priv->qsv_mapping_usable = 0;
        } else {
            priv->qsv_mapping_usable = 1;
        }
        av_free(props);
    }
#endif

#if HAVE_OPENCL_DXVA2
    {
        int fail = 0;

        CL_FUNC(clCreateFromDX9MediaSurfaceKHR,
                "DXVA2 to OpenCL mapping");
        CL_FUNC(clEnqueueAcquireDX9MediaSurfacesKHR,
                "DXVA2 in OpenCL acquire");
        CL_FUNC(clEnqueueReleaseDX9MediaSurfacesKHR,
                "DXVA2 in OpenCL release");

        if (fail) {
            av_log(hwdev, AV_LOG_WARNING, "DXVA2 to OpenCL mapping "
                   "not usable.\n");
            priv->dxva2_mapping_usable = 0;
        } else {
            priv->dx9_media_adapter_type = CL_ADAPTER_D3D9EX_KHR;
            priv->dxva2_mapping_usable = 1;
        }
    }
#endif

#if HAVE_OPENCL_D3D11
    {
        const char *d3d11_ext = "cl_khr_d3d11_sharing";
        const char *nv12_ext  = "cl_intel_d3d11_nv12_media_sharing";
        int fail = 0;

        if (!opencl_check_extension(hwdev, d3d11_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for D3D11 to OpenCL mapping.\n", d3d11_ext);
            fail = 1;
        } else if (!opencl_check_extension(hwdev, nv12_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension may be "
                   "required for D3D11 to OpenCL mapping.\n", nv12_ext);
            // Not fatal.
        }

        CL_FUNC(clCreateFromD3D11Texture2DKHR,
                "D3D11 to OpenCL mapping");
        CL_FUNC(clEnqueueAcquireD3D11ObjectsKHR,
                "D3D11 in OpenCL acquire");
        CL_FUNC(clEnqueueReleaseD3D11ObjectsKHR,
                "D3D11 in OpenCL release");

        if (fail) {
            av_log(hwdev, AV_LOG_WARNING, "D3D11 to OpenCL mapping "
                   "not usable.\n");
            priv->d3d11_mapping_usable = 0;
        } else {
            priv->d3d11_mapping_usable = 1;
        }
    }
#endif

#if HAVE_OPENCL_DRM_ARM
    {
        const char *drm_arm_ext = "cl_arm_import_memory";
        const char *image_ext   = "cl_khr_image2d_from_buffer";
        int fail = 0;

        if (!opencl_check_extension(hwdev, drm_arm_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for DRM to OpenCL mapping on ARM.\n",
                   drm_arm_ext);
            fail = 1;
        }
        if (!opencl_check_extension(hwdev, image_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for DRM to OpenCL mapping on ARM.\n",
                   image_ext);
            fail = 1;
        }

        // clImportMemoryARM() is linked statically.

        if (fail) {
            av_log(hwdev, AV_LOG_WARNING, "DRM to OpenCL mapping on ARM "
                   "not usable.\n");
            priv->drm_arm_mapping_usable = 0;
        } else {
            priv->drm_arm_mapping_usable = 1;
        }
    }
#endif

#undef CL_FUNC

    return 0;
}