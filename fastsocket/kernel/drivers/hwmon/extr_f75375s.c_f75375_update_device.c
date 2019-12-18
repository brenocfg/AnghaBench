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
struct i2c_client {int dummy; } ;
struct f75375_data {int valid; int /*<<< orphan*/  update_lock; void* last_updated; void** in; void** fan; void** temp; void* last_limits; void* fan_timer; void** in_min; void** in_max; void** pwm; void** fan_exp; void** fan_min; void** fan_full; void** temp_max_hyst; void** temp_high; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  F75375_REG_FAN (int) ; 
 int /*<<< orphan*/  F75375_REG_FAN_EXP (int) ; 
 int /*<<< orphan*/  F75375_REG_FAN_FULL (int) ; 
 int /*<<< orphan*/  F75375_REG_FAN_MIN (int) ; 
 int /*<<< orphan*/  F75375_REG_FAN_PWM_DUTY (int) ; 
 int /*<<< orphan*/  F75375_REG_FAN_TIMER ; 
 int /*<<< orphan*/  F75375_REG_TEMP (int) ; 
 int /*<<< orphan*/  F75375_REG_TEMP_HIGH (int) ; 
 int /*<<< orphan*/  F75375_REG_TEMP_HYST (int) ; 
 int /*<<< orphan*/  F75375_REG_VOLT (int) ; 
 int /*<<< orphan*/  F75375_REG_VOLT_HIGH (int) ; 
 int /*<<< orphan*/  F75375_REG_VOLT_LOW (int) ; 
 int HZ ; 
 void* f75375_read16 (struct i2c_client*,int /*<<< orphan*/ ) ; 
 void* f75375_read8 (struct i2c_client*,int /*<<< orphan*/ ) ; 
 struct f75375_data* i2c_get_clientdata (struct i2c_client*) ; 
 void* jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (void*,void*) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static struct f75375_data *f75375_update_device(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct f75375_data *data = i2c_get_clientdata(client);
	int nr;

	mutex_lock(&data->update_lock);

	/* Limit registers cache is refreshed after 60 seconds */
	if (time_after(jiffies, data->last_limits + 60 * HZ)
		|| !data->valid) {
		for (nr = 0; nr < 2; nr++) {
			data->temp_high[nr] =
				f75375_read8(client, F75375_REG_TEMP_HIGH(nr));
			data->temp_max_hyst[nr] =
				f75375_read8(client, F75375_REG_TEMP_HYST(nr));
			data->fan_full[nr] =
				f75375_read16(client, F75375_REG_FAN_FULL(nr));
			data->fan_min[nr] =
				f75375_read16(client, F75375_REG_FAN_MIN(nr));
			data->fan_exp[nr] =
				f75375_read16(client, F75375_REG_FAN_EXP(nr));
			data->pwm[nr] =	f75375_read8(client,
				F75375_REG_FAN_PWM_DUTY(nr));

		}
		for (nr = 0; nr < 4; nr++) {
			data->in_max[nr] =
				f75375_read8(client, F75375_REG_VOLT_HIGH(nr));
			data->in_min[nr] =
				f75375_read8(client, F75375_REG_VOLT_LOW(nr));
		}
		data->fan_timer = f75375_read8(client, F75375_REG_FAN_TIMER);
		data->last_limits = jiffies;
	}

	/* Measurement registers cache is refreshed after 2 second */
	if (time_after(jiffies, data->last_updated + 2 * HZ)
		|| !data->valid) {
		for (nr = 0; nr < 2; nr++) {
			data->temp[nr] =
				f75375_read8(client, F75375_REG_TEMP(nr));
			data->fan[nr] =
				f75375_read16(client, F75375_REG_FAN(nr));
		}
		for (nr = 0; nr < 4; nr++)
			data->in[nr] =
				f75375_read8(client, F75375_REG_VOLT(nr));

		data->last_updated = jiffies;
		data->valid = 1;
	}

	mutex_unlock(&data->update_lock);
	return data;
}