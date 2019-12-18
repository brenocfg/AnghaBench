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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adm1031_data {int /*<<< orphan*/ * fan_div; int /*<<< orphan*/ * fan; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAN_DIV_FROM_REG (int /*<<< orphan*/ ) ; 
 int FAN_FROM_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct adm1031_data* adm1031_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 
 scalar_t__ trust_fan_readings (struct adm1031_data*,int) ; 

__attribute__((used)) static ssize_t show_fan(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	int nr = to_sensor_dev_attr(attr)->index;
	struct adm1031_data *data = adm1031_update_device(dev);
	int value;

	value = trust_fan_readings(data, nr) ? FAN_FROM_REG(data->fan[nr],
				 FAN_DIV_FROM_REG(data->fan_div[nr])) : 0;
	return sprintf(buf, "%d\n", value);
}