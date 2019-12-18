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
struct gl518_data {int* fan_min; int beep_mask; int alarm_mask; int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * fan_div; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_FROM_REG (int /*<<< orphan*/ ) ; 
 int FAN_TO_REG (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL518_REG_ALARM ; 
 int /*<<< orphan*/  GL518_REG_FAN_LIMIT ; 
 void* gl518_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl518_write_value (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct gl518_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned long simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_fan_min(struct device *dev, struct device_attribute *attr,
			   const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct gl518_data *data = i2c_get_clientdata(client);
	int nr = to_sensor_dev_attr(attr)->index;
	int regvalue;
	unsigned long val = simple_strtoul(buf, NULL, 10);

	mutex_lock(&data->update_lock);
	regvalue = gl518_read_value(client, GL518_REG_FAN_LIMIT);
	data->fan_min[nr] = FAN_TO_REG(val, DIV_FROM_REG(data->fan_div[nr]));
	regvalue = (regvalue & (0xff << (8 * nr)))
		 | (data->fan_min[nr] << (8 * (1 - nr)));
	gl518_write_value(client, GL518_REG_FAN_LIMIT, regvalue);

	data->beep_mask = gl518_read_value(client, GL518_REG_ALARM);
	if (data->fan_min[nr] == 0)
		data->alarm_mask &= ~(0x20 << nr);
	else
		data->alarm_mask |= (0x20 << nr);
	data->beep_mask &= data->alarm_mask;
	gl518_write_value(client, GL518_REG_ALARM, data->beep_mask);

	mutex_unlock(&data->update_lock);
	return count;
}