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
typedef  long u8 ;
struct sensor_device_attribute {size_t index; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adt7473_data {long* pwm_behavior; int /*<<< orphan*/  lock; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 long ADT7473_PWM_BHVR_MASK ; 
 long ADT7473_PWM_BHVR_SHIFT ; 
 int /*<<< orphan*/  ADT7473_REG_PWM_BHVR (size_t) ; 
 size_t EINVAL ; 
 struct adt7473_data* i2c_get_clientdata (struct i2c_client*) ; 
 long i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strict_strtol (char const*,int,long*) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_pwm_auto_temp(struct device *dev,
				 struct device_attribute *devattr,
				 const char *buf,
				 size_t count)
{
	u8 reg;
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct i2c_client *client = to_i2c_client(dev);
	struct adt7473_data *data = i2c_get_clientdata(client);
	long temp;

	if (strict_strtol(buf, 10, &temp))
		return -EINVAL;

	switch (temp) {
	case 1:
	case 2:
	case 6:
	case 7:
		temp--;
		break;
	case 0:
		temp = 4;
		break;
	default:
		return -EINVAL;
	}

	mutex_lock(&data->lock);
	reg = i2c_smbus_read_byte_data(client,
				       ADT7473_REG_PWM_BHVR(attr->index));
	reg = (temp << ADT7473_PWM_BHVR_SHIFT) |
	      (reg & ~ADT7473_PWM_BHVR_MASK);
	i2c_smbus_write_byte_data(client, ADT7473_REG_PWM_BHVR(attr->index),
				  reg);
	data->pwm_behavior[attr->index] = reg;
	mutex_unlock(&data->lock);

	return count;
}