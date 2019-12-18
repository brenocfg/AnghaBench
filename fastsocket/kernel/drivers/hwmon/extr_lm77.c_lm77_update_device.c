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
struct lm77_data {int valid; int alarms; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; void* temp_max; void* temp_min; void* temp_crit; void* temp_hyst; void* temp_input; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  LM77_REG_TEMP ; 
 int /*<<< orphan*/  LM77_REG_TEMP_CRIT ; 
 int /*<<< orphan*/  LM77_REG_TEMP_HYST ; 
 int /*<<< orphan*/  LM77_REG_TEMP_MAX ; 
 int /*<<< orphan*/  LM77_REG_TEMP_MIN ; 
 void* LM77_TEMP_FROM_REG (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct lm77_data* i2c_get_clientdata (struct i2c_client*) ; 
 scalar_t__ jiffies ; 
 int lm77_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static struct lm77_data *lm77_update_device(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct lm77_data *data = i2c_get_clientdata(client);

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + HZ + HZ / 2)
	    || !data->valid) {
		dev_dbg(&client->dev, "Starting lm77 update\n");
		data->temp_input =
			LM77_TEMP_FROM_REG(lm77_read_value(client,
							   LM77_REG_TEMP));
		data->temp_hyst =
			LM77_TEMP_FROM_REG(lm77_read_value(client,
							   LM77_REG_TEMP_HYST));
		data->temp_crit =
			LM77_TEMP_FROM_REG(lm77_read_value(client,
							   LM77_REG_TEMP_CRIT));
		data->temp_min =
			LM77_TEMP_FROM_REG(lm77_read_value(client,
							   LM77_REG_TEMP_MIN));
		data->temp_max =
			LM77_TEMP_FROM_REG(lm77_read_value(client,
							   LM77_REG_TEMP_MAX));
		data->alarms =
			lm77_read_value(client, LM77_REG_TEMP) & 0x0007;
		data->last_updated = jiffies;
		data->valid = 1;
	}

	mutex_unlock(&data->update_lock);

	return data;
}