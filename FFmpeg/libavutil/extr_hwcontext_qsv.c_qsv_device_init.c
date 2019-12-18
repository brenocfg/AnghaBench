#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ mfxStatus ;
struct TYPE_12__ {int /*<<< orphan*/  pix_fmt; int /*<<< orphan*/  device_type; scalar_t__ handle_type; } ;
struct TYPE_11__ {TYPE_1__* internal; TYPE_3__* hwctx; } ;
struct TYPE_10__ {int /*<<< orphan*/  session; } ;
struct TYPE_9__ {int /*<<< orphan*/  ver; int /*<<< orphan*/  impl; int /*<<< orphan*/  handle; int /*<<< orphan*/  child_pix_fmt; int /*<<< orphan*/  child_device_type; scalar_t__ handle_type; } ;
struct TYPE_8__ {TYPE_2__* priv; } ;
typedef  TYPE_2__ QSVDeviceContext ;
typedef  TYPE_3__ AVQSVDeviceContext ;
typedef  TYPE_4__ AVHWDeviceContext ;

/* Variables and functions */
 int AVERROR_UNKNOWN ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 scalar_t__ MFXQueryIMPL (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ MFXQueryVersion (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ MFXVideoCORE_GetHandle (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ MFX_ERR_NONE ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_5__* supported_handle_types ; 

__attribute__((used)) static int qsv_device_init(AVHWDeviceContext *ctx)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;
    QSVDeviceContext       *s = ctx->internal->priv;

    mfxStatus err;
    int i;

    for (i = 0; supported_handle_types[i].handle_type; i++) {
        err = MFXVideoCORE_GetHandle(hwctx->session, supported_handle_types[i].handle_type,
                                     &s->handle);
        if (err == MFX_ERR_NONE) {
            s->handle_type       = supported_handle_types[i].handle_type;
            s->child_device_type = supported_handle_types[i].device_type;
            s->child_pix_fmt     = supported_handle_types[i].pix_fmt;
            break;
        }
    }
    if (!s->handle) {
        av_log(ctx, AV_LOG_VERBOSE, "No supported hw handle could be retrieved "
               "from the session\n");
    }

    err = MFXQueryIMPL(hwctx->session, &s->impl);
    if (err == MFX_ERR_NONE)
        err = MFXQueryVersion(hwctx->session, &s->ver);
    if (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes\n");
        return AVERROR_UNKNOWN;
    }

    return 0;
}