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
typedef  int /*<<< orphan*/  u16 ;
struct sensor_device_attribute {size_t index; } ;
struct i2c_client {int dummy; } ;
struct ds1621_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * temp; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/ * DS1621_REG_TEMP ; 
 int /*<<< orphan*/  LM75_TEMP_TO_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds1621_write_temp (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ds1621_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_strtol (char const*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_temp(struct device *dev, struct device_attribute *da,
			const char *buf, size_t count)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
	struct i2c_client *client = to_i2c_client(dev);
	struct ds1621_data *data = i2c_get_clientdata(client);
	u16 val = LM75_TEMP_TO_REG(simple_strtol(buf, NULL, 10));

	mutex_lock(&data->update_lock);
	data->temp[attr->index] = val;
	ds1621_write_temp(client, DS1621_REG_TEMP[attr->index],
			  data->temp[attr->index]);
	mutex_unlock(&data->update_lock);
	return count;
}