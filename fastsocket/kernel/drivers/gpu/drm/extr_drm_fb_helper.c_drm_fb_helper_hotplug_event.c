#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct drm_fb_helper {int delayed_hotplug; int /*<<< orphan*/  fbdev; struct drm_device* dev; TYPE_1__* fb; } ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;
struct drm_device {TYPE_2__ mode_config; } ;
struct TYPE_3__ {int /*<<< orphan*/  bits_per_pixel; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  drm_fb_helper_is_bound (struct drm_fb_helper*) ; 
 int drm_fb_helper_probe_connector_modes (struct drm_fb_helper*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_fb_helper_set_par (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_modeset_lock_all (struct drm_device*) ; 
 int /*<<< orphan*/  drm_modeset_unlock_all (struct drm_device*) ; 
 int /*<<< orphan*/  drm_setup_crtcs (struct drm_fb_helper*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int drm_fb_helper_hotplug_event(struct drm_fb_helper *fb_helper)
{
	struct drm_device *dev = fb_helper->dev;
	int count = 0;
	u32 max_width, max_height, bpp_sel;

	if (!fb_helper->fb)
		return 0;

	mutex_lock(&fb_helper->dev->mode_config.mutex);
	if (!drm_fb_helper_is_bound(fb_helper)) {
		fb_helper->delayed_hotplug = true;
		mutex_unlock(&fb_helper->dev->mode_config.mutex);
		return 0;
	}
	DRM_DEBUG_KMS("\n");

	max_width = fb_helper->fb->width;
	max_height = fb_helper->fb->height;
	bpp_sel = fb_helper->fb->bits_per_pixel;

	count = drm_fb_helper_probe_connector_modes(fb_helper, max_width,
						    max_height);
	mutex_unlock(&fb_helper->dev->mode_config.mutex);

	drm_modeset_lock_all(dev);
	drm_setup_crtcs(fb_helper);
	drm_modeset_unlock_all(dev);
	drm_fb_helper_set_par(fb_helper->fbdev);

	return 0;
}