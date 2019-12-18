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
struct sensor_device_attribute {size_t index; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adm9240_data {int /*<<< orphan*/ * in_max; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int IN_FROM_REG (int /*<<< orphan*/ ,size_t) ; 
 struct adm9240_data* adm9240_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t show_in_max(struct device *dev,
		struct device_attribute *devattr, char *buf)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct adm9240_data *data = adm9240_update_device(dev);
	return sprintf(buf, "%d\n", IN_FROM_REG(data->in_max[attr->index],
				attr->index));
}