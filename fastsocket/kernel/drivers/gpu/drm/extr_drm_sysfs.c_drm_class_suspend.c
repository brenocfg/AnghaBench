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
struct drm_minor {scalar_t__ type; struct drm_device* dev; } ;
struct drm_device {TYPE_1__* driver; } ;
struct device {int /*<<< orphan*/ * type; } ;
typedef  int /*<<< orphan*/  pm_message_t ;
struct TYPE_2__ {int (* suspend ) (struct drm_device*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_MODESET ; 
 scalar_t__ DRM_MINOR_LEGACY ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_sysfs_device_minor ; 
 int stub1 (struct drm_device*,int /*<<< orphan*/ ) ; 
 struct drm_minor* to_drm_minor (struct device*) ; 

__attribute__((used)) static int drm_class_suspend(struct device *dev, pm_message_t state)
{
	if (dev->type == &drm_sysfs_device_minor) {
		struct drm_minor *drm_minor = to_drm_minor(dev);
		struct drm_device *drm_dev = drm_minor->dev;

		if (drm_minor->type == DRM_MINOR_LEGACY &&
		    !drm_core_check_feature(drm_dev, DRIVER_MODESET) &&
		    drm_dev->driver->suspend)
			return drm_dev->driver->suspend(drm_dev, state);
	}
	return 0;
}