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
struct acpi_device {int /*<<< orphan*/  dev; scalar_t__ handle; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_get_handle (scalar_t__,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_attr_eject ; 
 int /*<<< orphan*/  dev_attr_hid ; 
 int /*<<< orphan*/  dev_attr_modalias ; 
 int /*<<< orphan*/  dev_attr_path ; 
 int /*<<< orphan*/  dev_attr_sun ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acpi_device_remove_files(struct acpi_device *dev)
{
	acpi_status status;
	acpi_handle temp;

	/*
	 * If device has _EJ0, 'eject' file is created that is used to trigger
	 * hot-removal function from userland.
	 */
	status = acpi_get_handle(dev->handle, "_EJ0", &temp);
	if (ACPI_SUCCESS(status))
		device_remove_file(&dev->dev, &dev_attr_eject);

	status = acpi_get_handle(dev->handle, "_SUN", &temp);
	if (ACPI_SUCCESS(status))
		device_remove_file(&dev->dev, &dev_attr_sun);

	device_remove_file(&dev->dev, &dev_attr_modalias);
	device_remove_file(&dev->dev, &dev_attr_hid);
	if (dev->handle)
		device_remove_file(&dev->dev, &dev_attr_path);
}