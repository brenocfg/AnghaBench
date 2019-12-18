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
struct TYPE_4__ {int /*<<< orphan*/ * acpi_handle; } ;
struct device {TYPE_2__ archdata; int /*<<< orphan*/  kobj; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct acpi_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_bus_get_device (int /*<<< orphan*/ *,struct acpi_device**) ; 
 int /*<<< orphan*/  acpi_detach_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct device* acpi_get_physical_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_glue_data_handler ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int acpi_unbind_one(struct device *dev)
{
	if (!dev->archdata.acpi_handle)
		return 0;
	if (dev == acpi_get_physical_device(dev->archdata.acpi_handle)) {
		struct acpi_device *acpi_dev;

		/* acpi_get_physical_device increase refcnt by one */
		put_device(dev);

		if (!acpi_bus_get_device(dev->archdata.acpi_handle,
					&acpi_dev)) {
			sysfs_remove_link(&dev->kobj, "firmware_node");
			sysfs_remove_link(&acpi_dev->dev.kobj, "physical_node");
		}

		acpi_detach_data(dev->archdata.acpi_handle,
				 acpi_glue_data_handler);
		dev->archdata.acpi_handle = NULL;
		/* acpi_bind_one increase refcnt by one */
		put_device(dev);
	} else {
		dev_err(dev, "Oops, 'acpi_handle' corrupt\n");
	}
	return 0;
}