#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mfxVersion ;
typedef  scalar_t__ mfxStatus ;
typedef  int /*<<< orphan*/  mfxSession ;
typedef  int /*<<< orphan*/  mfxIMPL ;
typedef  int /*<<< orphan*/  mfxHandleType ;
typedef  int /*<<< orphan*/ * mfxHDL ;
struct TYPE_7__ {scalar_t__ data; } ;
struct TYPE_6__ {TYPE_1__* hwctx; } ;
struct TYPE_5__ {int /*<<< orphan*/  session; } ;
typedef  TYPE_1__ AVQSVDeviceContext ;
typedef  TYPE_2__ AVHWDeviceContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;
typedef  TYPE_3__ AVBufferRef ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int FF_ARRAY_ELEMS (int /*<<< orphan*/  const*) ; 
 scalar_t__ MFXInit (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ MFXJoinSession (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MFXQueryIMPL (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ MFXQueryVersion (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ MFXVideoCORE_GetHandle (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ **) ; 
 scalar_t__ MFXVideoCORE_SetHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ MFX_ERR_NONE ; 
#define  MFX_HANDLE_D3D11_DEVICE 130 
#define  MFX_HANDLE_D3D9_DEVICE_MANAGER 129 
#define  MFX_HANDLE_VA_DISPLAY 128 
 scalar_t__ QSV_RUNTIME_VERSION_ATLEAST (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int ff_qsv_print_error (int /*<<< orphan*/ *,scalar_t__,char*) ; 
 int qsv_load_plugins (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

int ff_qsv_init_session_device(AVCodecContext *avctx, mfxSession *psession,
                               AVBufferRef *device_ref, const char *load_plugins)
{
    static const mfxHandleType handle_types[] = {
        MFX_HANDLE_VA_DISPLAY,
        MFX_HANDLE_D3D9_DEVICE_MANAGER,
        MFX_HANDLE_D3D11_DEVICE,
    };
    AVHWDeviceContext    *device_ctx = (AVHWDeviceContext*)device_ref->data;
    AVQSVDeviceContext *device_hwctx = device_ctx->hwctx;
    mfxSession        parent_session = device_hwctx->session;

    mfxSession    session;
    mfxVersion    ver;
    mfxIMPL       impl;
    mfxHDL        handle = NULL;
    mfxHandleType handle_type;
    mfxStatus err;

    int i, ret;

    err = MFXQueryIMPL(parent_session, &impl);
    if (err == MFX_ERR_NONE)
        err = MFXQueryVersion(parent_session, &ver);
    if (err != MFX_ERR_NONE)
        return ff_qsv_print_error(avctx, err,
                                  "Error querying the session attributes");

    for (i = 0; i < FF_ARRAY_ELEMS(handle_types); i++) {
        err = MFXVideoCORE_GetHandle(parent_session, handle_types[i], &handle);
        if (err == MFX_ERR_NONE) {
            handle_type = handle_types[i];
            break;
        }
        handle = NULL;
    }
    if (!handle) {
        av_log(avctx, AV_LOG_VERBOSE, "No supported hw handle could be retrieved "
               "from the session\n");
    }

    err = MFXInit(impl, &ver, &session);
    if (err != MFX_ERR_NONE)
        return ff_qsv_print_error(avctx, err,
                                  "Error initializing a child MFX session");

    if (handle) {
        err = MFXVideoCORE_SetHandle(session, handle_type, handle);
        if (err != MFX_ERR_NONE)
            return ff_qsv_print_error(avctx, err,
                                      "Error setting a HW handle");
    }

    if (QSV_RUNTIME_VERSION_ATLEAST(ver, 1, 25)) {
        err = MFXJoinSession(parent_session, session);
        if (err != MFX_ERR_NONE)
            return ff_qsv_print_error(avctx, err,
                                      "Error joining session");
    }

    ret = qsv_load_plugins(session, load_plugins, avctx);
    if (ret < 0) {
        av_log(avctx, AV_LOG_ERROR, "Error loading plugins\n");
        return ret;
    }

    *psession = session;
    return 0;
}