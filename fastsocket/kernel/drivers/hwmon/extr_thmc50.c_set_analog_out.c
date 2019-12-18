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
struct thmc50_data {int analog_out; int /*<<< orphan*/  update_lock; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int SENSORS_LIMIT (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  THMC50_REG_ANALOG_OUT ; 
 int /*<<< orphan*/  THMC50_REG_CONF ; 
 int THMC50_REG_CONF_nFANOFF ; 
 struct thmc50_data* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t set_analog_out(struct device *dev,
			      struct device_attribute *attr,
			      const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct thmc50_data *data = i2c_get_clientdata(client);
	int tmp = simple_strtoul(buf, NULL, 10);
	int config;

	mutex_lock(&data->update_lock);
	data->analog_out = SENSORS_LIMIT(tmp, 0, 255);
	i2c_smbus_write_byte_data(client, THMC50_REG_ANALOG_OUT,
				  data->analog_out);

	config = i2c_smbus_read_byte_data(client, THMC50_REG_CONF);
	if (data->analog_out == 0)
		config &= ~THMC50_REG_CONF_nFANOFF;
	else
		config |= THMC50_REG_CONF_nFANOFF;
	i2c_smbus_write_byte_data(client, THMC50_REG_CONF, config);

	mutex_unlock(&data->update_lock);
	return count;
}