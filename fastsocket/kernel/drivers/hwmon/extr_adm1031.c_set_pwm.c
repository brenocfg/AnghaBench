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
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adm1031_data {int conf1; int* pwm; int /*<<< orphan*/  update_lock; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int ADM1031_CONF1_AUTO_MODE ; 
 int /*<<< orphan*/  ADM1031_REG_PWM ; 
 size_t EINVAL ; 
 int PWM_TO_REG (int) ; 
 int adm1031_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adm1031_write_value (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct adm1031_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int simple_strtol (char const*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_pwm(struct device *dev, struct device_attribute *attr,
		       const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct adm1031_data *data = i2c_get_clientdata(client);
	int nr = to_sensor_dev_attr(attr)->index;
	int val = simple_strtol(buf, NULL, 10);
	int reg;

	mutex_lock(&data->update_lock);
	if ((data->conf1 & ADM1031_CONF1_AUTO_MODE) &&
	    (((val>>4) & 0xf) != 5)) {
		/* In automatic mode, the only PWM accepted is 33% */
		mutex_unlock(&data->update_lock);
		return -EINVAL;
	}
	data->pwm[nr] = PWM_TO_REG(val);
	reg = adm1031_read_value(client, ADM1031_REG_PWM);
	adm1031_write_value(client, ADM1031_REG_PWM,
			    nr ? ((data->pwm[nr] << 4) & 0xf0) | (reg & 0xf)
			    : (data->pwm[nr] & 0xf) | (reg & 0xf0));
	mutex_unlock(&data->update_lock);
	return count;
}