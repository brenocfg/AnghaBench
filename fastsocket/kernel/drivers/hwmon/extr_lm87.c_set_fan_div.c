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
typedef  int u8 ;
struct lm87_data {int* fan_min; int* fan_div; int /*<<< orphan*/  update_lock; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  FAN_DIV_FROM_REG (int) ; 
 unsigned long FAN_FROM_REG (int,int /*<<< orphan*/ ) ; 
 int FAN_TO_REG (unsigned long,long) ; 
 int /*<<< orphan*/  LM87_REG_FAN_MIN (int) ; 
 int /*<<< orphan*/  LM87_REG_VID_FAN_DIV ; 
 struct lm87_data* i2c_get_clientdata (struct i2c_client*) ; 
 int lm87_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lm87_write_value (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 long simple_strtol (char const*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t set_fan_div(struct device *dev, const char *buf,
		size_t count, int nr)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct lm87_data *data = i2c_get_clientdata(client);
	long val = simple_strtol(buf, NULL, 10);
	unsigned long min;
	u8 reg;

	mutex_lock(&data->update_lock);
	min = FAN_FROM_REG(data->fan_min[nr],
			   FAN_DIV_FROM_REG(data->fan_div[nr]));

	switch (val) {
	case 1: data->fan_div[nr] = 0; break;
	case 2: data->fan_div[nr] = 1; break;
	case 4: data->fan_div[nr] = 2; break;
	case 8: data->fan_div[nr] = 3; break;
	default:
		mutex_unlock(&data->update_lock);
		return -EINVAL;
	}

	reg = lm87_read_value(client, LM87_REG_VID_FAN_DIV);
	switch (nr) {
	case 0:
	    reg = (reg & 0xCF) | (data->fan_div[0] << 4);
	    break;
	case 1:
	    reg = (reg & 0x3F) | (data->fan_div[1] << 6);
	    break;
	}
	lm87_write_value(client, LM87_REG_VID_FAN_DIV, reg);

	data->fan_min[nr] = FAN_TO_REG(min, val);
	lm87_write_value(client, LM87_REG_FAN_MIN(nr),
			 data->fan_min[nr]);
	mutex_unlock(&data->update_lock);

	return count;
}