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
typedef  int u8 ;
struct i2c_client {int dummy; } ;
struct gl520_data {int* fan_min; int beep_mask; int alarm_mask; int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * fan_div; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int FAN_TO_REG (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL520_REG_BEEP_MASK ; 
 int /*<<< orphan*/  GL520_REG_FAN_MIN ; 
 int gl520_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl520_write_value (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct gl520_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned long simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_fan_min(struct device *dev, struct device_attribute *attr,
			   const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct gl520_data *data = i2c_get_clientdata(client);
	int n = to_sensor_dev_attr(attr)->index;
	unsigned long v = simple_strtoul(buf, NULL, 10);
	u8 r;

	mutex_lock(&data->update_lock);
	r = FAN_TO_REG(v, data->fan_div[n]);
	data->fan_min[n] = r;

	if (n == 0)
		gl520_write_value(client, GL520_REG_FAN_MIN,
				  (gl520_read_value(client, GL520_REG_FAN_MIN)
				   & ~0xff00) | (r << 8));
	else
		gl520_write_value(client, GL520_REG_FAN_MIN,
				  (gl520_read_value(client, GL520_REG_FAN_MIN)
				   & ~0xff) | r);

	data->beep_mask = gl520_read_value(client, GL520_REG_BEEP_MASK);
	if (data->fan_min[n] == 0)
		data->alarm_mask &= (n == 0) ? ~0x20 : ~0x40;
	else
		data->alarm_mask |= (n == 0) ? 0x20 : 0x40;
	data->beep_mask &= data->alarm_mask;
	gl520_write_value(client, GL520_REG_BEEP_MASK, data->beep_mask);

	mutex_unlock(&data->update_lock);
	return count;
}