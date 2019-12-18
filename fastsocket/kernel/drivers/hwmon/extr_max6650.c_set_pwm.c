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
struct max6650_data {int config; int dac; int /*<<< orphan*/  update_lock; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int MAX6650_CFG_V12 ; 
 int /*<<< orphan*/  MAX6650_REG_DAC ; 
 int SENSORS_LIMIT (int,int /*<<< orphan*/ ,int) ; 
 struct max6650_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t set_pwm(struct device *dev, struct device_attribute *devattr,
			const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct max6650_data *data = i2c_get_clientdata(client);
	int pwm = simple_strtoul(buf, NULL, 10);

	pwm = SENSORS_LIMIT(pwm, 0, 255);

	mutex_lock(&data->update_lock);

	if (data->config & MAX6650_CFG_V12)
		data->dac = 180 - (180 * pwm)/255;
	else
		data->dac = 76 - (76 * pwm)/255;

	i2c_smbus_write_byte_data(client, MAX6650_REG_DAC, data->dac);

	mutex_unlock(&data->update_lock);

	return count;
}