#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_9__ {int /*<<< orphan*/  device; } ;
struct TYPE_8__ {TYPE_3__* hwctx; } ;
struct TYPE_7__ {int /*<<< orphan*/  Description; int /*<<< orphan*/  DeviceId; int /*<<< orphan*/  VendorId; } ;
typedef  int /*<<< orphan*/  IDXGIFactory2 ;
typedef  int /*<<< orphan*/  IDXGIAdapter ;
typedef  int /*<<< orphan*/  ID3D10Multithread ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_1__ DXGI_ADAPTER_DESC ;
typedef  TYPE_2__ AVHWDeviceContext ;
typedef  int /*<<< orphan*/  AVDictionary ;
typedef  TYPE_3__ AVD3D11VADeviceContext ;

/* Variables and functions */
 int AVERROR_UNKNOWN ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  D3D11_CREATE_DEVICE_DEBUG ; 
 int /*<<< orphan*/  D3D11_CREATE_DEVICE_VIDEO_SUPPORT ; 
 int /*<<< orphan*/  D3D11_SDK_VERSION ; 
 int /*<<< orphan*/  D3D_DRIVER_TYPE_HARDWARE ; 
 int /*<<< orphan*/  D3D_DRIVER_TYPE_UNKNOWN ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  ID3D10Multithread_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D10Multithread_SetMultithreadProtected (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ID3D11Device_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IDXGIAdapter2_GetDesc (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  IDXGIAdapter_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IDXGIFactory2_EnumAdapters (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IDXGIFactory2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_ID3D10Multithread ; 
 int /*<<< orphan*/  IID_IDXGIFactory2 ; 
 int /*<<< orphan*/  LoadLibrary (char*) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int atoi (char const*) ; 
 int /*<<< orphan*/  av_dict_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 int ff_thread_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  functions_loaded ; 
 int /*<<< orphan*/  load_functions ; 
 scalar_t__ mCreateDXGIFactory (int /*<<< orphan*/ *,void**) ; 
 scalar_t__ mD3D11CreateDevice (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int d3d11va_device_create(AVHWDeviceContext *ctx, const char *device,
                                 AVDictionary *opts, int flags)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->hwctx;

    HRESULT hr;
    IDXGIAdapter           *pAdapter = NULL;
    ID3D10Multithread      *pMultithread;
    UINT creationFlags = D3D11_CREATE_DEVICE_VIDEO_SUPPORT;
    int is_debug       = !!av_dict_get(opts, "debug", NULL, 0);
    int ret;

    // (On UWP we can't check this.)
#if !HAVE_UWP
    if (!LoadLibrary("d3d11_1sdklayers.dll"))
        is_debug = 0;
#endif

    if (is_debug)
        creationFlags |= D3D11_CREATE_DEVICE_DEBUG;

    if ((ret = ff_thread_once(&functions_loaded, load_functions)) != 0)
        return AVERROR_UNKNOWN;
    if (!mD3D11CreateDevice || !mCreateDXGIFactory) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load D3D11 library or its functions\n");
        return AVERROR_UNKNOWN;
    }

    if (device) {
        IDXGIFactory2 *pDXGIFactory;
        hr = mCreateDXGIFactory(&IID_IDXGIFactory2, (void **)&pDXGIFactory);
        if (SUCCEEDED(hr)) {
            int adapter = atoi(device);
            if (FAILED(IDXGIFactory2_EnumAdapters(pDXGIFactory, adapter, &pAdapter)))
                pAdapter = NULL;
            IDXGIFactory2_Release(pDXGIFactory);
        }
    }

    if (pAdapter) {
        DXGI_ADAPTER_DESC desc;
        hr = IDXGIAdapter2_GetDesc(pAdapter, &desc);
        if (!FAILED(hr)) {
            av_log(ctx, AV_LOG_INFO, "Using device %04x:%04x (%ls).\n",
                   desc.VendorId, desc.DeviceId, desc.Description);
        }
    }

    hr = mD3D11CreateDevice(pAdapter, pAdapter ? D3D_DRIVER_TYPE_UNKNOWN : D3D_DRIVER_TYPE_HARDWARE, NULL, creationFlags, NULL, 0,
                   D3D11_SDK_VERSION, &device_hwctx->device, NULL, NULL);
    if (pAdapter)
        IDXGIAdapter_Release(pAdapter);
    if (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device (%lx)\n", (long)hr);
        return AVERROR_UNKNOWN;
    }

    hr = ID3D11Device_QueryInterface(device_hwctx->device, &IID_ID3D10Multithread, (void **)&pMultithread);
    if (SUCCEEDED(hr)) {
        ID3D10Multithread_SetMultithreadProtected(pMultithread, TRUE);
        ID3D10Multithread_Release(pMultithread);
    }

#if !HAVE_UWP && HAVE_DXGIDEBUG_H
    if (is_debug) {
        HANDLE dxgidebug_dll = LoadLibrary("dxgidebug.dll");
        if (dxgidebug_dll) {
            HRESULT (WINAPI  * pf_DXGIGetDebugInterface)(const GUID *riid, void **ppDebug)
                = (void *)GetProcAddress(dxgidebug_dll, "DXGIGetDebugInterface");
            if (pf_DXGIGetDebugInterface) {
                IDXGIDebug *dxgi_debug = NULL;
                hr = pf_DXGIGetDebugInterface(&IID_IDXGIDebug, (void**)&dxgi_debug);
                if (SUCCEEDED(hr) && dxgi_debug)
                    IDXGIDebug_ReportLiveObjects(dxgi_debug, DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
            }
        }
    }
#endif

    return 0;
}