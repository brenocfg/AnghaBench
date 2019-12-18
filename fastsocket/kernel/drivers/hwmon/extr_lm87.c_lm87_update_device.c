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
struct lm87_data {int valid; int channel; int* in; int* in_min; int* in_max; int* fan; int* fan_min; int* temp; int* temp_high; int* temp_low; int* fan_div; int vid; int alarms; int aout; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; void* temp_crit_ext; void* temp_crit_int; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int CHAN_NO_FAN (int) ; 
 int CHAN_TEMP3 ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  LM87_REG_AIN (int) ; 
 int /*<<< orphan*/  LM87_REG_AIN_MAX (int) ; 
 int /*<<< orphan*/  LM87_REG_AIN_MIN (int) ; 
 int /*<<< orphan*/  LM87_REG_ALARMS1 ; 
 int /*<<< orphan*/  LM87_REG_ALARMS2 ; 
 int /*<<< orphan*/  LM87_REG_AOUT ; 
 int /*<<< orphan*/  LM87_REG_FAN (int) ; 
 int /*<<< orphan*/  LM87_REG_FAN_MIN (int) ; 
 int /*<<< orphan*/  LM87_REG_IN (int) ; 
 int /*<<< orphan*/  LM87_REG_IN_MAX (int) ; 
 int /*<<< orphan*/  LM87_REG_IN_MIN (int) ; 
 int /*<<< orphan*/ * LM87_REG_TEMP ; 
 int /*<<< orphan*/ * LM87_REG_TEMP_HIGH ; 
 int /*<<< orphan*/  LM87_REG_TEMP_HW_EXT ; 
 int /*<<< orphan*/  LM87_REG_TEMP_HW_EXT_LOCK ; 
 int /*<<< orphan*/  LM87_REG_TEMP_HW_INT ; 
 int /*<<< orphan*/  LM87_REG_TEMP_HW_INT_LOCK ; 
 int /*<<< orphan*/ * LM87_REG_TEMP_LOW ; 
 int /*<<< orphan*/  LM87_REG_VID4 ; 
 int /*<<< orphan*/  LM87_REG_VID_FAN_DIV ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct lm87_data* i2c_get_clientdata (struct i2c_client*) ; 
 scalar_t__ jiffies ; 
 int lm87_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 void* min (int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static struct lm87_data *lm87_update_device(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct lm87_data *data = i2c_get_clientdata(client);

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + HZ) || !data->valid) {
		int i, j;

		dev_dbg(&client->dev, "Updating data.\n");

		i = (data->channel & CHAN_TEMP3) ? 1 : 0;
		j = (data->channel & CHAN_TEMP3) ? 5 : 6;
		for (; i < j; i++) {
			data->in[i] = lm87_read_value(client,
				      LM87_REG_IN(i));
			data->in_min[i] = lm87_read_value(client,
					  LM87_REG_IN_MIN(i));
			data->in_max[i] = lm87_read_value(client,
					  LM87_REG_IN_MAX(i));
		}

		for (i = 0; i < 2; i++) {
			if (data->channel & CHAN_NO_FAN(i)) {
				data->in[6+i] = lm87_read_value(client,
						LM87_REG_AIN(i));
				data->in_max[6+i] = lm87_read_value(client,
						    LM87_REG_AIN_MAX(i));
				data->in_min[6+i] = lm87_read_value(client,
						    LM87_REG_AIN_MIN(i));

			} else {
				data->fan[i] = lm87_read_value(client,
					       LM87_REG_FAN(i));
				data->fan_min[i] = lm87_read_value(client,
						   LM87_REG_FAN_MIN(i));
			}
		}

		j = (data->channel & CHAN_TEMP3) ? 3 : 2;
		for (i = 0 ; i < j; i++) {
			data->temp[i] = lm87_read_value(client,
					LM87_REG_TEMP[i]);
			data->temp_high[i] = lm87_read_value(client,
					     LM87_REG_TEMP_HIGH[i]);
			data->temp_low[i] = lm87_read_value(client,
					    LM87_REG_TEMP_LOW[i]);
		}

		i = lm87_read_value(client, LM87_REG_TEMP_HW_INT_LOCK);
		j = lm87_read_value(client, LM87_REG_TEMP_HW_INT);
		data->temp_crit_int = min(i, j);

		i = lm87_read_value(client, LM87_REG_TEMP_HW_EXT_LOCK);
		j = lm87_read_value(client, LM87_REG_TEMP_HW_EXT);
		data->temp_crit_ext = min(i, j);

		i = lm87_read_value(client, LM87_REG_VID_FAN_DIV);
		data->fan_div[0] = (i >> 4) & 0x03;
		data->fan_div[1] = (i >> 6) & 0x03;
		data->vid = (i & 0x0F)
			  | (lm87_read_value(client, LM87_REG_VID4) & 0x01)
			     << 4;

		data->alarms = lm87_read_value(client, LM87_REG_ALARMS1)
			     | (lm87_read_value(client, LM87_REG_ALARMS2)
				<< 8);
		data->aout = lm87_read_value(client, LM87_REG_AOUT);

		data->last_updated = jiffies;
		data->valid = 1;
	}

	mutex_unlock(&data->update_lock);

	return data;
}