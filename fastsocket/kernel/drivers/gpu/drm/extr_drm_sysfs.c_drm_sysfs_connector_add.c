#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct drm_device {TYPE_1__* primary; } ;
struct TYPE_9__ {int /*<<< orphan*/  kobj; int /*<<< orphan*/  release; int /*<<< orphan*/  class; int /*<<< orphan*/ * parent; } ;
struct drm_connector {int connector_type; TYPE_2__ kdev; struct drm_device* dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  index; int /*<<< orphan*/  kdev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
#define  DRM_MODE_CONNECTOR_Component 132 
#define  DRM_MODE_CONNECTOR_Composite 131 
#define  DRM_MODE_CONNECTOR_DVII 130 
#define  DRM_MODE_CONNECTOR_SVIDEO 129 
#define  DRM_MODE_CONNECTOR_TV 128 
 int /*<<< orphan*/ * connector_attrs ; 
 int /*<<< orphan*/ * connector_attrs_opt1 ; 
 int /*<<< orphan*/  dev_set_name (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int device_create_file (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_is_registered (TYPE_2__*) ; 
 int device_register (TYPE_2__*) ; 
 int /*<<< orphan*/  device_remove_file (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  drm_class ; 
 int /*<<< orphan*/  drm_get_connector_name (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_sysfs_device_release ; 
 int /*<<< orphan*/  drm_sysfs_hotplug_event (struct drm_device*) ; 
 int /*<<< orphan*/  edid_attr ; 
 int sysfs_create_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int drm_sysfs_connector_add(struct drm_connector *connector)
{
	struct drm_device *dev = connector->dev;
	int attr_cnt = 0;
	int opt_cnt = 0;
	int i;
	int ret;

	/* We shouldn't get called more than once for the same connector */
	BUG_ON(device_is_registered(&connector->kdev));

	connector->kdev.parent = &dev->primary->kdev;
	connector->kdev.class = drm_class;
	connector->kdev.release = drm_sysfs_device_release;

	DRM_DEBUG("adding \"%s\" to sysfs\n",
		  drm_get_connector_name(connector));

	dev_set_name(&connector->kdev, "card%d-%s",
		     dev->primary->index, drm_get_connector_name(connector));
	ret = device_register(&connector->kdev);

	if (ret) {
		DRM_ERROR("failed to register connector device: %d\n", ret);
		goto out;
	}

	/* Standard attributes */

	for (attr_cnt = 0; attr_cnt < ARRAY_SIZE(connector_attrs); attr_cnt++) {
		ret = device_create_file(&connector->kdev, &connector_attrs[attr_cnt]);
		if (ret)
			goto err_out_files;
	}

	/* Optional attributes */
	/*
	 * In the long run it maybe a good idea to make one set of
	 * optionals per connector type.
	 */
	switch (connector->connector_type) {
		case DRM_MODE_CONNECTOR_DVII:
		case DRM_MODE_CONNECTOR_Composite:
		case DRM_MODE_CONNECTOR_SVIDEO:
		case DRM_MODE_CONNECTOR_Component:
		case DRM_MODE_CONNECTOR_TV:
			for (opt_cnt = 0; opt_cnt < ARRAY_SIZE(connector_attrs_opt1); opt_cnt++) {
				ret = device_create_file(&connector->kdev, &connector_attrs_opt1[opt_cnt]);
				if (ret)
					goto err_out_files;
			}
			break;
		default:
			break;
	}

	ret = sysfs_create_bin_file(&connector->kdev.kobj, &edid_attr);
	if (ret)
		goto err_out_files;

	/* Let userspace know we have a new connector */
	drm_sysfs_hotplug_event(dev);

	return 0;

err_out_files:
	for (i = 0; i < opt_cnt; i++)
		device_remove_file(&connector->kdev, &connector_attrs_opt1[i]);
	for (i = 0; i < attr_cnt; i++)
		device_remove_file(&connector->kdev, &connector_attrs[i]);
	device_unregister(&connector->kdev);

out:
	return ret;
}