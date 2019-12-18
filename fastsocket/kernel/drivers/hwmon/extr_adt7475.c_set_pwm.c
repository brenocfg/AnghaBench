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
struct sensor_device_attribute_2 {int nr; size_t index; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adt7475_data {int** pwm; int /*<<< orphan*/  lock; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t CONTROL ; 
 size_t EINVAL ; 
#define  INPUT 130 
#define  MAX 129 
#define  MIN 128 
 int /*<<< orphan*/  PWM_CONFIG_REG (size_t) ; 
 unsigned char PWM_MAX_REG (size_t) ; 
 unsigned char PWM_MIN_REG (size_t) ; 
 unsigned char PWM_REG (size_t) ; 
 int SENSORS_LIMIT (long,int /*<<< orphan*/ ,int) ; 
 int adt7475_read (int /*<<< orphan*/ ) ; 
 struct adt7475_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,unsigned char,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strict_strtol (char const*,int,long*) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_pwm(struct device *dev, struct device_attribute *attr,
		       const char *buf, size_t count)
{

	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	struct i2c_client *client = to_i2c_client(dev);
	struct adt7475_data *data = i2c_get_clientdata(client);
	unsigned char reg = 0;
	long val;

	if (strict_strtol(buf, 10, &val))
		return -EINVAL;

	mutex_lock(&data->lock);

	switch (sattr->nr) {
	case INPUT:
		/* Get a fresh value for CONTROL */
		data->pwm[CONTROL][sattr->index] =
			adt7475_read(PWM_CONFIG_REG(sattr->index));

		/* If we are not in manual mode, then we shouldn't allow
		 * the user to set the pwm speed */
		if (((data->pwm[CONTROL][sattr->index] >> 5) & 7) != 7) {
			mutex_unlock(&data->lock);
			return count;
		}

		reg = PWM_REG(sattr->index);
		break;

	case MIN:
		reg = PWM_MIN_REG(sattr->index);
		break;

	case MAX:
		reg = PWM_MAX_REG(sattr->index);
		break;
	}

	data->pwm[sattr->nr][sattr->index] = SENSORS_LIMIT(val, 0, 0xFF);
	i2c_smbus_write_byte_data(client, reg,
				  data->pwm[sattr->nr][sattr->index]);

	mutex_unlock(&data->lock);

	return count;
}