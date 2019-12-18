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
struct tmp421_data {int config; int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * temp; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int TMP421_CONFIG_RANGE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int temp_from_s16 (int /*<<< orphan*/ ) ; 
 int temp_from_u16 (int /*<<< orphan*/ ) ; 
 struct tmp421_data* tmp421_update_device (struct device*) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t show_temp_value(struct device *dev,
			       struct device_attribute *devattr, char *buf)
{
	int index = to_sensor_dev_attr(devattr)->index;
	struct tmp421_data *data = tmp421_update_device(dev);
	int temp;

	mutex_lock(&data->update_lock);
	if (data->config & TMP421_CONFIG_RANGE)
		temp = temp_from_u16(data->temp[index]);
	else
		temp = temp_from_s16(data->temp[index]);
	mutex_unlock(&data->update_lock);

	return sprintf(buf, "%d\n", temp);
}