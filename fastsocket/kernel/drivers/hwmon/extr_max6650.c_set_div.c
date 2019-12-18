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
struct max6650_data {int count; int /*<<< orphan*/  update_lock; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  MAX6650_REG_COUNT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct max6650_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t set_div(struct device *dev, struct device_attribute *devattr,
		       const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct max6650_data *data = i2c_get_clientdata(client);
	int div = simple_strtoul(buf, NULL, 10);

	mutex_lock(&data->update_lock);
	switch (div) {
	case 1:
		data->count = 0;
		break;
	case 2:
		data->count = 1;
		break;
	case 4:
		data->count = 2;
		break;
	case 8:
		data->count = 3;
		break;
	default:
		mutex_unlock(&data->update_lock);
		dev_err(&client->dev,
			"illegal value for fan divider (%d)\n", div);
		return -EINVAL;
	}

	i2c_smbus_write_byte_data(client, MAX6650_REG_COUNT, data->count);
	mutex_unlock(&data->update_lock);

	return count;
}