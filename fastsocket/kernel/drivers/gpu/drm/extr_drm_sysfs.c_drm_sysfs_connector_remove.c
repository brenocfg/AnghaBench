#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * parent; int /*<<< orphan*/  kobj; } ;
struct drm_connector {TYPE_1__ kdev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * connector_attrs ; 
 int /*<<< orphan*/  device_remove_file (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_get_connector_name (struct drm_connector*) ; 
 int /*<<< orphan*/  edid_attr ; 
 int /*<<< orphan*/  sysfs_remove_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void drm_sysfs_connector_remove(struct drm_connector *connector)
{
	int i;

	if (!connector->kdev.parent)
		return;
	DRM_DEBUG("removing \"%s\" from sysfs\n",
		  drm_get_connector_name(connector));

	for (i = 0; i < ARRAY_SIZE(connector_attrs); i++)
		device_remove_file(&connector->kdev, &connector_attrs[i]);
	sysfs_remove_bin_file(&connector->kdev.kobj, &edid_attr);
	device_unregister(&connector->kdev);
	connector->kdev.parent = NULL;
}