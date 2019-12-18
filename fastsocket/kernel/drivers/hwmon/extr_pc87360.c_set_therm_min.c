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
struct pc87360_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * in_min; int /*<<< orphan*/  in_vref; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  IN_TO_REG (long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_IN ; 
 int /*<<< orphan*/  PC87365_REG_TEMP_MIN ; 
 struct pc87360_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pc87360_write_value (struct pc87360_data*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long simple_strtol (char const*,int /*<<< orphan*/ *,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_therm_min(struct device *dev, struct device_attribute *devattr, const char *buf,
	size_t count)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct pc87360_data *data = dev_get_drvdata(dev);
	long val = simple_strtol(buf, NULL, 10);

	mutex_lock(&data->update_lock);
	data->in_min[attr->index] = IN_TO_REG(val, data->in_vref);
	pc87360_write_value(data, LD_IN, attr->index, PC87365_REG_TEMP_MIN,
			    data->in_min[attr->index]);
	mutex_unlock(&data->update_lock);
	return count;
}