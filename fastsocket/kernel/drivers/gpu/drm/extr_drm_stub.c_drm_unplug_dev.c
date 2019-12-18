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
struct drm_device {scalar_t__ open_count; int /*<<< orphan*/  primary; int /*<<< orphan*/  control; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_MODESET ; 
 scalar_t__ drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_device_set_unplugged (struct drm_device*) ; 
 int /*<<< orphan*/  drm_global_mutex ; 
 int /*<<< orphan*/  drm_put_dev (struct drm_device*) ; 
 int /*<<< orphan*/  drm_unplug_minor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void drm_unplug_dev(struct drm_device *dev)
{
	/* for a USB device */
	if (drm_core_check_feature(dev, DRIVER_MODESET))
		drm_unplug_minor(dev->control);
	drm_unplug_minor(dev->primary);

	mutex_lock(&drm_global_mutex);

	drm_device_set_unplugged(dev);

	if (dev->open_count == 0) {
		drm_put_dev(dev);
	}
	mutex_unlock(&drm_global_mutex);
}