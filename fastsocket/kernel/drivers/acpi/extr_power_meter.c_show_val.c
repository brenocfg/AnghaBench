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
struct sensor_device_attribute {int index; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int min_avg_interval; int max_avg_interval; int min_cap; int max_cap; int hysteresis; int flags; } ;
struct acpi_power_meter_resource {int* trip; int /*<<< orphan*/  cap; int /*<<< orphan*/  power; TYPE_1__ caps; } ;
struct acpi_device {struct acpi_power_meter_resource* driver_data; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int acpi_integer ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int POWER_METER_IS_BATTERY ; 
 int UNKNOWN_HYSTERESIS ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 struct acpi_device* to_acpi_device (struct device*) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t show_val(struct device *dev,
			struct device_attribute *devattr,
			char *buf)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct acpi_device *acpi_dev = to_acpi_device(dev);
	struct acpi_power_meter_resource *resource = acpi_dev->driver_data;
	acpi_integer val = 0;

	switch (attr->index) {
	case 0:
		val = resource->caps.min_avg_interval;
		break;
	case 1:
		val = resource->caps.max_avg_interval;
		break;
	case 2:
		val = resource->caps.min_cap * 1000;
		break;
	case 3:
		val = resource->caps.max_cap * 1000;
		break;
	case 4:
		if (resource->caps.hysteresis == UNKNOWN_HYSTERESIS)
			return sprintf(buf, "unknown\n");

		val = resource->caps.hysteresis * 1000;
		break;
	case 5:
		if (resource->caps.flags & POWER_METER_IS_BATTERY)
			val = 1;
		else
			val = 0;
		break;
	case 6:
		if (resource->power > resource->cap)
			val = 1;
		else
			val = 0;
		break;
	case 7:
	case 8:
		if (resource->trip[attr->index - 7] < 0)
			return sprintf(buf, "unknown\n");

		val = resource->trip[attr->index - 7] * 1000;
		break;
	default:
		BUG();
	}

	return sprintf(buf, "%llu\n", val);
}