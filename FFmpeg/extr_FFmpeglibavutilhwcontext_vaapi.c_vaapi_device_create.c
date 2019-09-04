#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * VADisplay ;
struct TYPE_7__ {int drm_fd; } ;
typedef  TYPE_1__ VAAPIDevicePriv ;
struct TYPE_8__ {int /*<<< orphan*/  free; TYPE_1__* user_opaque; } ;
typedef  TYPE_2__ AVHWDeviceContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,char const*) ; 
 TYPE_1__* av_mallocz (int) ; 
 int vaapi_device_connect (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vaapi_device_free ; 

__attribute__((used)) static int vaapi_device_create(AVHWDeviceContext *ctx, const char *device,
                               AVDictionary *opts, int flags)
{
    VAAPIDevicePriv *priv;
    VADisplay display = NULL;

    priv = av_mallocz(sizeof(*priv));
    if (!priv)
        return AVERROR(ENOMEM);

    priv->drm_fd = -1;

    ctx->user_opaque = priv;
    ctx->free        = vaapi_device_free;

#if HAVE_VAAPI_X11
    if (!display && !(device && device[0] == '/')) {
        // Try to open the device as an X11 display.
        priv->x11_display = XOpenDisplay(device);
        if (!priv->x11_display) {
            av_log(ctx, AV_LOG_VERBOSE, "Cannot open X11 display "
                   "%s.\n", XDisplayName(device));
        } else {
            display = vaGetDisplay(priv->x11_display);
            if (!display) {
                av_log(ctx, AV_LOG_ERROR, "Cannot open a VA display "
                       "from X11 display %s.\n", XDisplayName(device));
                return AVERROR_UNKNOWN;
            }

            av_log(ctx, AV_LOG_VERBOSE, "Opened VA display via "
                   "X11 display %s.\n", XDisplayName(device));
        }
    }
#endif

#if HAVE_VAAPI_DRM
    if (!display) {
        // Try to open the device as a DRM path.
        // Default to using the first render node if the user did not
        // supply a path.
        const char *path = device ? device : "/dev/dri/renderD128";
        priv->drm_fd = open(path, O_RDWR);
        if (priv->drm_fd < 0) {
            av_log(ctx, AV_LOG_VERBOSE, "Cannot open DRM device %s.\n",
                   path);
        } else {
            display = vaGetDisplayDRM(priv->drm_fd);
            if (!display) {
                av_log(ctx, AV_LOG_ERROR, "Cannot open a VA display "
                       "from DRM device %s.\n", path);
                return AVERROR_UNKNOWN;
            }

            av_log(ctx, AV_LOG_VERBOSE, "Opened VA display via "
                   "DRM device %s.\n", path);
        }
    }
#endif

    if (!display) {
        av_log(ctx, AV_LOG_ERROR, "No VA display found for "
               "device: %s.\n", device ? device : "");
        return AVERROR(EINVAL);
    }

    return vaapi_device_connect(ctx, display);
}