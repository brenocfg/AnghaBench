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
struct platform_device {int dummy; } ;
struct TYPE_2__ {struct platform_device* platform_device; } ;
struct drm_driver {int /*<<< orphan*/  device_list; int /*<<< orphan*/ * bus; TYPE_1__ kdriver; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int drm_get_platform_dev (struct platform_device*,struct drm_driver*) ; 
 int /*<<< orphan*/  drm_platform_bus ; 

int drm_platform_init(struct drm_driver *driver, struct platform_device *platform_device)
{
	DRM_DEBUG("\n");

	driver->kdriver.platform_device = platform_device;
	driver->bus = &drm_platform_bus;
	INIT_LIST_HEAD(&driver->device_list);
	return drm_get_platform_dev(platform_device, driver);
}