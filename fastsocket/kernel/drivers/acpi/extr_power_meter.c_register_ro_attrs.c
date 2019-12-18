#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * name; int /*<<< orphan*/  mode; } ;
struct TYPE_6__ {TYPE_2__ attr; int /*<<< orphan*/  show; } ;
struct sensor_device_attribute {TYPE_3__ dev_attr; int /*<<< orphan*/  index; } ;
struct ro_sensor_template {int /*<<< orphan*/  index; int /*<<< orphan*/  show; int /*<<< orphan*/ * label; } ;
struct device {int dummy; } ;
struct acpi_power_meter_resource {size_t num_sensors; struct sensor_device_attribute* sensors; TYPE_1__* acpi_dev; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_IRUGO ; 
 int device_create_file (struct device*,TYPE_3__*) ; 

__attribute__((used)) static int register_ro_attrs(struct acpi_power_meter_resource *resource,
			     struct ro_sensor_template *ro)
{
	struct device *dev = &resource->acpi_dev->dev;
	struct sensor_device_attribute *sensors =
		&resource->sensors[resource->num_sensors];
	int res = 0;

	while (ro->label) {
		sensors->dev_attr.attr.name = ro->label;
		sensors->dev_attr.attr.mode = S_IRUGO;
		sensors->dev_attr.show = ro->show;
		sensors->index = ro->index;

		res = device_create_file(dev, &sensors->dev_attr);
		if (res) {
			sensors->dev_attr.attr.name = NULL;
			goto error;
		}
		sensors++;
		resource->num_sensors++;
		ro++;
	}

error:
	return res;
}