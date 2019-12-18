#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct drm_mode_set {int dummy; } ;
struct drm_fb_helper {int crtc_count; TYPE_1__* crtc_info; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct drm_mode_set mode_set; } ;

/* Variables and functions */
 int drm_mode_set_config_internal (struct drm_mode_set*) ; 
 int /*<<< orphan*/  drm_warn_on_modeset_not_all_locked (int /*<<< orphan*/ ) ; 

bool drm_fb_helper_restore_fbdev_mode(struct drm_fb_helper *fb_helper)
{
	bool error = false;
	int i, ret;

	drm_warn_on_modeset_not_all_locked(fb_helper->dev);

	for (i = 0; i < fb_helper->crtc_count; i++) {
		struct drm_mode_set *mode_set = &fb_helper->crtc_info[i].mode_set;
		ret = drm_mode_set_config_internal(mode_set);
		if (ret)
			error = true;
	}
	return error;
}