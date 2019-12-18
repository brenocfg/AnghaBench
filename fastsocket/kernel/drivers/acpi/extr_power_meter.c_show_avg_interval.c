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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct acpi_power_meter_resource {int /*<<< orphan*/  avg_interval; int /*<<< orphan*/  lock; } ;
struct acpi_device {struct acpi_power_meter_resource* driver_data; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 struct acpi_device* to_acpi_device (struct device*) ; 
 int /*<<< orphan*/  update_avg_interval (struct acpi_power_meter_resource*) ; 

__attribute__((used)) static ssize_t show_avg_interval(struct device *dev,
				 struct device_attribute *devattr,
				 char *buf)
{
	struct acpi_device *acpi_dev = to_acpi_device(dev);
	struct acpi_power_meter_resource *resource = acpi_dev->driver_data;

	mutex_lock(&resource->lock);
	update_avg_interval(resource);
	mutex_unlock(&resource->lock);

	return sprintf(buf, "%llu\n", resource->avg_interval);
}