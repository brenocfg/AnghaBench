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
struct TYPE_2__ {int (* add ) (struct acpi_device*) ;} ;
struct acpi_driver {TYPE_1__ ops; } ;
struct acpi_device {struct acpi_driver* driver; int /*<<< orphan*/ * driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOSYS ; 
 int stub1 (struct acpi_device*) ; 

__attribute__((used)) static int
acpi_bus_driver_init(struct acpi_device *device, struct acpi_driver *driver)
{
	int result = 0;

	if (!device || !driver)
		return -EINVAL;

	if (!driver->ops.add)
		return -ENOSYS;

	result = driver->ops.add(device);
	if (result) {
		device->driver = NULL;
		device->driver_data = NULL;
		return result;
	}

	device->driver = driver;

	/*
	 * TBD - Configuration Management: Assign resources to device based
	 * upon possible configuration and currently allocated resources.
	 */

	ACPI_DEBUG_PRINT((ACPI_DB_INFO,
			  "Driver successfully bound to device\n"));
	return 0;
}