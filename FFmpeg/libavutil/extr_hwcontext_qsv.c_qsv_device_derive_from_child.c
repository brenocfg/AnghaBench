#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int member_0; int member_1; } ;
struct TYPE_13__ {int /*<<< orphan*/  Minor; int /*<<< orphan*/  Major; TYPE_1__ member_0; } ;
typedef  TYPE_2__ mfxVersion ;
typedef  scalar_t__ mfxStatus ;
typedef  int /*<<< orphan*/  mfxIMPL ;
typedef  int /*<<< orphan*/  mfxHandleType ;
typedef  int /*<<< orphan*/  mfxHDL ;
struct TYPE_15__ {int type; TYPE_3__* hwctx; } ;
struct TYPE_14__ {scalar_t__ session; int /*<<< orphan*/  devmgr; int /*<<< orphan*/  display; } ;
typedef  TYPE_3__ AVVAAPIDeviceContext ;
typedef  TYPE_3__ AVQSVDeviceContext ;
typedef  TYPE_5__ AVHWDeviceContext ;
typedef  TYPE_3__ AVDXVA2DeviceContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_UNKNOWN ; 
#define  AV_HWDEVICE_TYPE_DXVA2 129 
#define  AV_HWDEVICE_TYPE_VAAPI 128 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  MFXClose (scalar_t__) ; 
 scalar_t__ MFXInit (int /*<<< orphan*/ ,TYPE_2__*,scalar_t__*) ; 
 scalar_t__ MFXQueryVersion (scalar_t__,TYPE_2__*) ; 
 scalar_t__ MFXVideoCORE_SetHandle (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MFX_ERR_NONE ; 
 int /*<<< orphan*/  MFX_HANDLE_D3D9_DEVICE_MANAGER ; 
 int /*<<< orphan*/  MFX_HANDLE_VA_DISPLAY ; 
 int /*<<< orphan*/  MFX_VERSION_MAJOR ; 
 int /*<<< orphan*/  MFX_VERSION_MINOR ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,scalar_t__,...) ; 

__attribute__((used)) static int qsv_device_derive_from_child(AVHWDeviceContext *ctx,
                                        mfxIMPL implementation,
                                        AVHWDeviceContext *child_device_ctx,
                                        int flags)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;

    mfxVersion    ver = { { 3, 1 } };
    mfxHDL        handle;
    mfxHandleType handle_type;
    mfxStatus     err;
    int ret;

    switch (child_device_ctx->type) {
#if CONFIG_VAAPI
    case AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIDeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_VA_DISPLAY;
            handle = (mfxHDL)child_device_hwctx->display;
        }
        break;
#endif
#if CONFIG_DXVA2
    case AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2DeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
            handle = (mfxHDL)child_device_hwctx->devmgr;
        }
        break;
#endif
    default:
        ret = AVERROR(ENOSYS);
        goto fail;
    }

    err = MFXInit(implementation, &ver, &hwctx->session);
    if (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", err);
        ret = AVERROR_UNKNOWN;
        goto fail;
    }

    err = MFXQueryVersion(hwctx->session, &ver);
    if (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying an MFX session: %d.\n", err);
        ret = AVERROR_UNKNOWN;
        goto fail;
    }

    av_log(ctx, AV_LOG_VERBOSE,
           "Initialize MFX session: API version is %d.%d, implementation version is %d.%d\n",
           MFX_VERSION_MAJOR, MFX_VERSION_MINOR, ver.Major, ver.Minor);

    MFXClose(hwctx->session);

    err = MFXInit(implementation, &ver, &hwctx->session);
    if (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "Error initializing an MFX session: %d.\n", err);
        ret = AVERROR_UNKNOWN;
        goto fail;
    }

    err = MFXVideoCORE_SetHandle(hwctx->session, handle_type, handle);
    if (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error setting child device handle: "
               "%d\n", err);
        ret = AVERROR_UNKNOWN;
        goto fail;
    }

    return 0;

fail:
    if (hwctx->session)
        MFXClose(hwctx->session);
    return ret;
}