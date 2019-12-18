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
struct TYPE_3__ {int /*<<< orphan*/  num_crtc; int /*<<< orphan*/  crtc_list; int /*<<< orphan*/  mutex; } ;
struct drm_device {TYPE_1__ mode_config; } ;
struct drm_crtc_funcs {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * properties; } ;
struct drm_crtc {int invert_dimensions; int /*<<< orphan*/  head; int /*<<< orphan*/  properties; TYPE_2__ base; int /*<<< orphan*/  mutex; struct drm_crtc_funcs const* funcs; struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_OBJECT_CRTC ; 
 int drm_mode_object_get (struct drm_device*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_modeset_lock_all (struct drm_device*) ; 
 int /*<<< orphan*/  drm_modeset_unlock_all (struct drm_device*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock_nest_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int drm_crtc_init(struct drm_device *dev, struct drm_crtc *crtc,
		   const struct drm_crtc_funcs *funcs)
{
	int ret;

	crtc->dev = dev;
	crtc->funcs = funcs;
	crtc->invert_dimensions = false;

	drm_modeset_lock_all(dev);
	mutex_init(&crtc->mutex);
	mutex_lock_nest_lock(&crtc->mutex, &dev->mode_config.mutex);

	ret = drm_mode_object_get(dev, &crtc->base, DRM_MODE_OBJECT_CRTC);
	if (ret)
		goto out;

	crtc->base.properties = &crtc->properties;

	list_add_tail(&crtc->head, &dev->mode_config.crtc_list);
	dev->mode_config.num_crtc++;

 out:
	drm_modeset_unlock_all(dev);

	return ret;
}