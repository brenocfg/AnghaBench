#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VADisplay ;
struct TYPE_9__ {int drm_fd; } ;
typedef  TYPE_1__ VAAPIDevicePriv ;
struct TYPE_11__ {scalar_t__ fd; } ;
struct TYPE_10__ {scalar_t__ type; int /*<<< orphan*/ * free; TYPE_1__* user_opaque; TYPE_3__* hwctx; } ;
typedef  TYPE_2__ AVHWDeviceContext ;
typedef  TYPE_3__ AVDRMDeviceContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_HWDEVICE_TYPE_DRM ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* av_mallocz (int) ; 
 int /*<<< orphan*/ * vaGetDisplayDRM (scalar_t__) ; 
 int vaapi_device_connect (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vaapi_device_free ; 

__attribute__((used)) static int vaapi_device_derive(AVHWDeviceContext *ctx,
                               AVHWDeviceContext *src_ctx, int flags)
{
#if HAVE_VAAPI_DRM
    if (src_ctx->type == AV_HWDEVICE_TYPE_DRM) {
        AVDRMDeviceContext *src_hwctx = src_ctx->hwctx;
        VADisplay *display;
        VAAPIDevicePriv *priv;

        if (src_hwctx->fd < 0) {
            av_log(ctx, AV_LOG_ERROR, "DRM instance requires an associated "
                   "device to derive a VA display from.\n");
            return AVERROR(EINVAL);
        }

        priv = av_mallocz(sizeof(*priv));
        if (!priv)
            return AVERROR(ENOMEM);

        // Inherits the fd from the source context, which will close it.
        priv->drm_fd = -1;

        ctx->user_opaque = priv;
        ctx->free        = &vaapi_device_free;

        display = vaGetDisplayDRM(src_hwctx->fd);
        if (!display) {
            av_log(ctx, AV_LOG_ERROR, "Failed to open a VA display from "
                   "DRM device.\n");
            return AVERROR(EIO);
        }

        return vaapi_device_connect(ctx, display);
    }
#endif
    return AVERROR(ENOSYS);
}