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
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adt7462_data {int* pwm_tmin; int* pwm_trange; int /*<<< orphan*/  lock; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int ADT7462_PWM_HYST_MASK ; 
 int ADT7462_PWM_RANGE_SHIFT ; 
 int /*<<< orphan*/  ADT7462_REG_PWM_TRANGE (size_t) ; 
 size_t EINVAL ; 
 int find_trange_value (long) ; 
 struct adt7462_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strict_strtol (char const*,int,long*) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_pwm_tmax(struct device *dev,
			    struct device_attribute *devattr,
			    const char *buf,
			    size_t count)
{
	int temp;
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct i2c_client *client = to_i2c_client(dev);
	struct adt7462_data *data = i2c_get_clientdata(client);
	int tmin, trange_value;
	long trange;

	if (strict_strtol(buf, 10, &trange))
		return -EINVAL;

	/* trange = tmax - tmin */
	tmin = (data->pwm_tmin[attr->index] - 64) * 1000;
	trange_value = find_trange_value(trange - tmin);

	if (trange_value < 0)
		return -EINVAL;

	temp = trange_value << ADT7462_PWM_RANGE_SHIFT;
	temp |= data->pwm_trange[attr->index] & ADT7462_PWM_HYST_MASK;

	mutex_lock(&data->lock);
	data->pwm_trange[attr->index] = temp;
	i2c_smbus_write_byte_data(client, ADT7462_REG_PWM_TRANGE(attr->index),
				  temp);
	mutex_unlock(&data->lock);

	return count;
}