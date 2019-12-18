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
struct adm1021_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * temp_max; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADM1021_REG_TOS_W (int) ; 
 int /*<<< orphan*/  SENSORS_LIMIT (long,int,int) ; 
 struct adm1021_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_only ; 
 int simple_strtol (char const*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_temp_max(struct device *dev,
			    struct device_attribute *devattr,
			    const char *buf, size_t count)
{
	int index = to_sensor_dev_attr(devattr)->index;
	struct i2c_client *client = to_i2c_client(dev);
	struct adm1021_data *data = i2c_get_clientdata(client);
	long temp = simple_strtol(buf, NULL, 10) / 1000;

	mutex_lock(&data->update_lock);
	data->temp_max[index] = SENSORS_LIMIT(temp, -128, 127);
	if (!read_only)
		i2c_smbus_write_byte_data(client, ADM1021_REG_TOS_W(index),
					  data->temp_max[index]);
	mutex_unlock(&data->update_lock);

	return count;
}