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
struct TYPE_5__ {int mode; int /*<<< orphan*/ * name; } ;
struct TYPE_6__ {TYPE_2__ attr; int /*<<< orphan*/  store; int /*<<< orphan*/  show; } ;
struct sensor_device_attribute {TYPE_3__ dev_attr; int /*<<< orphan*/  index; } ;
struct rw_sensor_template {int /*<<< orphan*/  index; int /*<<< orphan*/  set; int /*<<< orphan*/  show; int /*<<< orphan*/ * label; } ;
struct device {int dummy; } ;
struct acpi_power_meter_resource {size_t num_sensors; struct sensor_device_attribute* sensors; TYPE_1__* acpi_dev; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int S_IRUGO ; 
 int S_IWUSR ; 
 int device_create_file (struct device*,TYPE_3__*) ; 

__attribute__((used)) static int register_rw_attrs(struct acpi_power_meter_resource *resource,
			     struct rw_sensor_template *rw)
{
	struct device *dev = &resource->acpi_dev->dev;
	struct sensor_device_attribute *sensors =
		&resource->sensors[resource->num_sensors];
	int res = 0;

	while (rw->label) {
		sensors->dev_attr.attr.name = rw->label;
		sensors->dev_attr.attr.mode = S_IRUGO | S_IWUSR;
		sensors->dev_attr.show = rw->show;
		sensors->dev_attr.store = rw->set;
		sensors->index = rw->index;

		res = device_create_file(dev, &sensors->dev_attr);
		if (res) {
			sensors->dev_attr.attr.name = NULL;
			goto error;
		}
		sensors++;
		resource->num_sensors++;
		rw++;
	}

error:
	return res;
}