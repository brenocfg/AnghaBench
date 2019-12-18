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
struct sensor_device_attribute_2 {int nr; int index; } ;
struct k8temp_data {int temp_offset; int /*<<< orphan*/ ** temp; scalar_t__ swap_core_select; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int TEMP_FROM_REG (int /*<<< orphan*/ ) ; 
 struct k8temp_data* k8temp_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t show_temp(struct device *dev,
			 struct device_attribute *devattr, char *buf)
{
	struct sensor_device_attribute_2 *attr =
	    to_sensor_dev_attr_2(devattr);
	int core = attr->nr;
	int place = attr->index;
	int temp;
	struct k8temp_data *data = k8temp_update_device(dev);

	if (data->swap_core_select)
		core = core ? 0 : 1;

	temp = TEMP_FROM_REG(data->temp[core][place]) + data->temp_offset;

	return sprintf(buf, "%d\n", temp);
}