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
struct via686a_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * temp_over; } ;
struct sensor_device_attribute {int index; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEMP_TO_REG (int) ; 
 int /*<<< orphan*/ * VIA686A_REG_TEMP_OVER ; 
 struct via686a_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int simple_strtol (char const*,int /*<<< orphan*/ *,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 
 int /*<<< orphan*/  via686a_write_value (struct via686a_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t set_temp_over(struct device *dev, struct device_attribute *da,
		const char *buf, size_t count) {
	struct via686a_data *data = dev_get_drvdata(dev);
	struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
	int nr = attr->index;
	int val = simple_strtol(buf, NULL, 10);

	mutex_lock(&data->update_lock);
	data->temp_over[nr] = TEMP_TO_REG(val);
	via686a_write_value(data, VIA686A_REG_TEMP_OVER[nr],
			    data->temp_over[nr]);
	mutex_unlock(&data->update_lock);
	return count;
}