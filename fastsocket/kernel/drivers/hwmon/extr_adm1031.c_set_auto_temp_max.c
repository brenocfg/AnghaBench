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
struct adm1031_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * temp_max; int /*<<< orphan*/ * pwm; int /*<<< orphan*/ * auto_temp; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADM1031_REG_AUTO_TEMP (int) ; 
 int /*<<< orphan*/  AUTO_TEMP_MAX_TO_REG (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adm1031_write_value (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct adm1031_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int simple_strtol (char const*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t
set_auto_temp_max(struct device *dev, struct device_attribute *attr,
		  const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct adm1031_data *data = i2c_get_clientdata(client);
	int nr = to_sensor_dev_attr(attr)->index;
	int val = simple_strtol(buf, NULL, 10);

	mutex_lock(&data->update_lock);
	data->temp_max[nr] = AUTO_TEMP_MAX_TO_REG(val, data->auto_temp[nr], data->pwm[nr]);
	adm1031_write_value(client, ADM1031_REG_AUTO_TEMP(nr),
			    data->temp_max[nr]);
	mutex_unlock(&data->update_lock);
	return count;
}