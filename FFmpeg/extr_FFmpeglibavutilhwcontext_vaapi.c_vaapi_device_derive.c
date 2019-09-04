#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  AVHWDeviceContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOSYS ; 

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