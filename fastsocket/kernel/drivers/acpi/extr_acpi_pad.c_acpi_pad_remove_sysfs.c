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
struct acpi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_idlecpus ; 
 int /*<<< orphan*/  dev_attr_idlepct ; 
 int /*<<< orphan*/  dev_attr_rrtime ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acpi_pad_remove_sysfs(struct acpi_device *device)
{
	device_remove_file(&device->dev, &dev_attr_idlecpus);
	device_remove_file(&device->dev, &dev_attr_idlepct);
	device_remove_file(&device->dev, &dev_attr_rrtime);
}