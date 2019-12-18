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
struct lm90_data {scalar_t__ kind; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  temp_hyst; int /*<<< orphan*/ * temp8; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  LM90_REG_W_TCRIT_HYST ; 
 scalar_t__ adt7461 ; 
 int /*<<< orphan*/  hyst_to_reg (int) ; 
 struct lm90_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ max6646 ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 long simple_strtol (char const*,int /*<<< orphan*/ *,int) ; 
 int temp_from_s8 (int /*<<< orphan*/ ) ; 
 int temp_from_u8 (int /*<<< orphan*/ ) ; 
 int temp_from_u8_adt7461 (struct lm90_data*,int /*<<< orphan*/ ) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t set_temphyst(struct device *dev, struct device_attribute *dummy,
			    const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct lm90_data *data = i2c_get_clientdata(client);
	long val = simple_strtol(buf, NULL, 10);
	int temp;

	mutex_lock(&data->update_lock);
	if (data->kind == adt7461)
		temp = temp_from_u8_adt7461(data, data->temp8[2]);
	else if (data->kind == max6646)
		temp = temp_from_u8(data->temp8[2]);
	else
		temp = temp_from_s8(data->temp8[2]);

	data->temp_hyst = hyst_to_reg(temp - val);
	i2c_smbus_write_byte_data(client, LM90_REG_W_TCRIT_HYST,
				  data->temp_hyst);
	mutex_unlock(&data->update_lock);
	return count;
}