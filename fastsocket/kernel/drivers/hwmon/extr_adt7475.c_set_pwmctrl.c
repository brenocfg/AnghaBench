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
struct sensor_device_attribute_2 {size_t index; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adt7475_data {int /*<<< orphan*/  lock; int /*<<< orphan*/ * pwmchan; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  adt7475_read_pwm (struct i2c_client*,size_t) ; 
 int hw_set_pwm (struct i2c_client*,size_t,long,int /*<<< orphan*/ ) ; 
 struct adt7475_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strict_strtol (char const*,int,long*) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_pwmctrl(struct device *dev, struct device_attribute *attr,
			   const char *buf, size_t count)
{
	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	struct i2c_client *client = to_i2c_client(dev);
	struct adt7475_data *data = i2c_get_clientdata(client);
	int r;
	long val;

	if (strict_strtol(buf, 10, &val))
		return -EINVAL;

	mutex_lock(&data->lock);
	/* Read Modify Write PWM values */
	adt7475_read_pwm(client, sattr->index);
	r = hw_set_pwm(client, sattr->index, val, data->pwmchan[sattr->index]);
	if (r)
		count = r;
	mutex_unlock(&data->lock);

	return count;
}