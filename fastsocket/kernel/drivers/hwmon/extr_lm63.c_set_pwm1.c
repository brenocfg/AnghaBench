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
struct lm63_data {int config_fan; int pwm1_value; int pwm1_freq; int /*<<< orphan*/  update_lock; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EPERM ; 
 int /*<<< orphan*/  LM63_REG_PWM_VALUE ; 
 struct lm63_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned long simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t set_pwm1(struct device *dev, struct device_attribute *dummy,
			const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct lm63_data *data = i2c_get_clientdata(client);
	unsigned long val;
	
	if (!(data->config_fan & 0x20)) /* register is read-only */
		return -EPERM;

	val = simple_strtoul(buf, NULL, 10);
	mutex_lock(&data->update_lock);
	data->pwm1_value = val <= 0 ? 0 :
			   val >= 255 ? 2 * data->pwm1_freq :
			   (val * data->pwm1_freq * 2 + 127) / 255;
	i2c_smbus_write_byte_data(client, LM63_REG_PWM_VALUE, data->pwm1_value);
	mutex_unlock(&data->update_lock);
	return count;
}