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
struct f75375_data {int* pwm_mode; int /*<<< orphan*/  update_lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  F75375_REG_CONFIG1 ; 
 int FAN_CTRL_LINEAR (int) ; 
 int f75375_read8 (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f75375_write8 (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct f75375_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_pwm_mode(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t count)
{
	int nr = to_sensor_dev_attr(attr)->index;
	struct i2c_client *client = to_i2c_client(dev);
	struct f75375_data *data = i2c_get_clientdata(client);
	int val = simple_strtoul(buf, NULL, 10);
	u8 conf = 0;

	if (!(val == 0 || val == 1))
		return -EINVAL;

	mutex_lock(&data->update_lock);
	conf = f75375_read8(client, F75375_REG_CONFIG1);
	conf = ~(1 << FAN_CTRL_LINEAR(nr));

	if (val == 0)
		conf |= (1 << FAN_CTRL_LINEAR(nr)) ;

	f75375_write8(client, F75375_REG_CONFIG1, conf);
	data->pwm_mode[nr] = val;
	mutex_unlock(&data->update_lock);
	return count;
}