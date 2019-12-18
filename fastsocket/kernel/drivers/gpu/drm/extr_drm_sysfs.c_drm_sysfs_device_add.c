#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * type; int /*<<< orphan*/  devt; int /*<<< orphan*/  release; int /*<<< orphan*/  class; int /*<<< orphan*/  parent; } ;
struct drm_minor {scalar_t__ type; TYPE_2__ kdev; int /*<<< orphan*/  index; int /*<<< orphan*/  device; TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 scalar_t__ DRM_MINOR_CONTROL ; 
 scalar_t__ DRM_MINOR_RENDER ; 
 int /*<<< orphan*/  dev_set_name (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int device_register (TYPE_2__*) ; 
 int /*<<< orphan*/  drm_class ; 
 int /*<<< orphan*/  drm_sysfs_device_minor ; 
 int /*<<< orphan*/  drm_sysfs_device_release ; 

int drm_sysfs_device_add(struct drm_minor *minor)
{
	int err;
	char *minor_str;

	minor->kdev.parent = minor->dev->dev;

	minor->kdev.class = drm_class;
	minor->kdev.release = drm_sysfs_device_release;
	minor->kdev.devt = minor->device;
	minor->kdev.type = &drm_sysfs_device_minor;
	if (minor->type == DRM_MINOR_CONTROL)
		minor_str = "controlD%d";
        else if (minor->type == DRM_MINOR_RENDER)
                minor_str = "renderD%d";
        else
                minor_str = "card%d";

	dev_set_name(&minor->kdev, minor_str, minor->index);

	err = device_register(&minor->kdev);
	if (err) {
		DRM_ERROR("device add failed: %d\n", err);
		goto err_out;
	}

	return 0;

err_out:
	return err;
}