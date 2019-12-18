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
struct max6650_data {int config; int /*<<< orphan*/  update_lock; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int MAX6650_CFG_MODE_MASK ; 
 int /*<<< orphan*/  MAX6650_REG_CONFIG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct max6650_data* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t set_enable(struct device *dev, struct device_attribute *devattr,
			  const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct max6650_data *data = i2c_get_clientdata(client);
	int mode = simple_strtoul(buf, NULL, 10);
	int max6650_modes[3] = {0, 3, 2};

	if ((mode < 0)||(mode > 2)) {
		dev_err(&client->dev,
			"illegal value for pwm1_enable (%d)\n", mode);
		return -EINVAL;
	}

	mutex_lock(&data->update_lock);

	data->config = i2c_smbus_read_byte_data(client, MAX6650_REG_CONFIG);
	data->config = (data->config & ~MAX6650_CFG_MODE_MASK)
		       | (max6650_modes[mode] << 4);

	i2c_smbus_write_byte_data(client, MAX6650_REG_CONFIG, data->config);

	mutex_unlock(&data->update_lock);

	return count;
}