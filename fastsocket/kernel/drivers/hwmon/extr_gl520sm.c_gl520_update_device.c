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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct gl520_data {int valid; int alarms; int beep_mask; int vid; int* in_input; int* in_min; int* in_max; int* fan_input; int* fan_min; int* temp_input; int* temp_max; int* temp_max_hyst; int* fan_div; int fan_off; int alarm_mask; int beep_enable; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; scalar_t__ two_temps; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL520_REG_ALARMS ; 
 int /*<<< orphan*/  GL520_REG_BEEP_MASK ; 
 int /*<<< orphan*/  GL520_REG_CONF ; 
 int /*<<< orphan*/  GL520_REG_FAN_DIV ; 
 int /*<<< orphan*/  GL520_REG_FAN_INPUT ; 
 int /*<<< orphan*/  GL520_REG_FAN_MIN ; 
 int /*<<< orphan*/ * GL520_REG_IN_INPUT ; 
 int /*<<< orphan*/ * GL520_REG_IN_LIMIT ; 
 int /*<<< orphan*/ * GL520_REG_IN_MAX ; 
 int /*<<< orphan*/ * GL520_REG_IN_MIN ; 
 int /*<<< orphan*/ * GL520_REG_TEMP_INPUT ; 
 int /*<<< orphan*/ * GL520_REG_TEMP_MAX ; 
 int /*<<< orphan*/ * GL520_REG_TEMP_MAX_HYST ; 
 int /*<<< orphan*/  GL520_REG_VID_INPUT ; 
 int HZ ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int gl520_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 struct gl520_data* i2c_get_clientdata (struct i2c_client*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static struct gl520_data *gl520_update_device(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct gl520_data *data = i2c_get_clientdata(client);
	int val, i;

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + 2 * HZ) || !data->valid) {

		dev_dbg(&client->dev, "Starting gl520sm update\n");

		data->alarms = gl520_read_value(client, GL520_REG_ALARMS);
		data->beep_mask = gl520_read_value(client, GL520_REG_BEEP_MASK);
		data->vid = gl520_read_value(client, GL520_REG_VID_INPUT) & 0x1f;

		for (i = 0; i < 4; i++) {
			data->in_input[i] = gl520_read_value(client,
							GL520_REG_IN_INPUT[i]);
			val = gl520_read_value(client, GL520_REG_IN_LIMIT[i]);
			data->in_min[i] = val & 0xff;
			data->in_max[i] = (val >> 8) & 0xff;
		}

		val = gl520_read_value(client, GL520_REG_FAN_INPUT);
		data->fan_input[0] = (val >> 8) & 0xff;
		data->fan_input[1] = val & 0xff;

		val = gl520_read_value(client, GL520_REG_FAN_MIN);
		data->fan_min[0] = (val >> 8) & 0xff;
		data->fan_min[1] = val & 0xff;

		data->temp_input[0] = gl520_read_value(client,
						GL520_REG_TEMP_INPUT[0]);
		data->temp_max[0] = gl520_read_value(client,
						GL520_REG_TEMP_MAX[0]);
		data->temp_max_hyst[0] = gl520_read_value(client,
						GL520_REG_TEMP_MAX_HYST[0]);

		val = gl520_read_value(client, GL520_REG_FAN_DIV);
		data->fan_div[0] = (val >> 6) & 0x03;
		data->fan_div[1] = (val >> 4) & 0x03;
		data->fan_off = (val >> 2) & 0x01;

		data->alarms &= data->alarm_mask;

		val = gl520_read_value(client, GL520_REG_CONF);
		data->beep_enable = !((val >> 2) & 1);

		/* Temp1 and Vin4 are the same input */
		if (data->two_temps) {
			data->temp_input[1] = gl520_read_value(client,
						GL520_REG_TEMP_INPUT[1]);
			data->temp_max[1] = gl520_read_value(client,
						GL520_REG_TEMP_MAX[1]);
			data->temp_max_hyst[1] = gl520_read_value(client,
						GL520_REG_TEMP_MAX_HYST[1]);
		} else {
			data->in_input[4] = gl520_read_value(client,
						GL520_REG_IN_INPUT[4]);
			data->in_min[4] = gl520_read_value(client,
						GL520_REG_IN_MIN[4]);
			data->in_max[4] = gl520_read_value(client,
						GL520_REG_IN_MAX[4]);
		}

		data->last_updated = jiffies;
		data->valid = 1;
	}

	mutex_unlock(&data->update_lock);

	return data;
}