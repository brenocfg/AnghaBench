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
typedef  int /*<<< orphan*/  u8 ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adt7473_data {int max_duty_at_overheat; int /*<<< orphan*/  lock; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADT7473_CFG4_MAX_DUTY_AT_OVT ; 
 int /*<<< orphan*/  ADT7473_REG_CFG4 ; 
 size_t EINVAL ; 
 struct adt7473_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strict_strtol (char const*,int,long*) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t set_max_duty_at_crit(struct device *dev,
				    struct device_attribute *devattr,
				    const char *buf,
				    size_t count)
{
	u8 reg;
	struct i2c_client *client = to_i2c_client(dev);
	struct adt7473_data *data = i2c_get_clientdata(client);
	long temp;

	if (strict_strtol(buf, 10, &temp))
		return -EINVAL;

	mutex_lock(&data->lock);
	data->max_duty_at_overheat = !!temp;
	reg = i2c_smbus_read_byte_data(client, ADT7473_REG_CFG4);
	if (temp)
		reg |= ADT7473_CFG4_MAX_DUTY_AT_OVT;
	else
		reg &= ~ADT7473_CFG4_MAX_DUTY_AT_OVT;
	i2c_smbus_write_byte_data(client, ADT7473_REG_CFG4, reg);
	mutex_unlock(&data->lock);

	return count;
}