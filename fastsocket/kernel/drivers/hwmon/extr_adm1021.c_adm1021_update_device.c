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
struct device {int dummy; } ;
struct adm1021_data {int valid; int* temp; int* temp_max; int* temp_min; int alarms; scalar_t__ type; int remote_temp_offset; int remote_temp_offset_prec; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; } ;
typedef  int s8 ;

/* Variables and functions */
 int /*<<< orphan*/  ADM1021_REG_STATUS ; 
 int /*<<< orphan*/  ADM1021_REG_TEMP (int) ; 
 int /*<<< orphan*/  ADM1021_REG_THYST_R (int) ; 
 int /*<<< orphan*/  ADM1021_REG_TOS_R (int) ; 
 int /*<<< orphan*/  ADM1023_REG_REM_OFFSET ; 
 int /*<<< orphan*/  ADM1023_REG_REM_OFFSET_PREC ; 
 int /*<<< orphan*/  ADM1023_REG_REM_TEMP_PREC ; 
 int /*<<< orphan*/  ADM1023_REG_REM_THYST_PREC ; 
 int /*<<< orphan*/  ADM1023_REG_REM_TOS_PREC ; 
 int HZ ; 
 scalar_t__ adm1023 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct adm1021_data* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static struct adm1021_data *adm1021_update_device(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct adm1021_data *data = i2c_get_clientdata(client);

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + HZ + HZ / 2)
	    || !data->valid) {
		int i;

		dev_dbg(&client->dev, "Starting adm1021 update\n");

		for (i = 0; i < 2; i++) {
			data->temp[i] = 1000 *
				(s8) i2c_smbus_read_byte_data(
					client, ADM1021_REG_TEMP(i));
			data->temp_max[i] = 1000 *
				(s8) i2c_smbus_read_byte_data(
					client, ADM1021_REG_TOS_R(i));
			data->temp_min[i] = 1000 *
				(s8) i2c_smbus_read_byte_data(
					client, ADM1021_REG_THYST_R(i));
		}
		data->alarms = i2c_smbus_read_byte_data(client,
						ADM1021_REG_STATUS) & 0x7c;
		if (data->type == adm1023) {
			/* The ADM1023 provides 3 extra bits of precision for
			 * the remote sensor in extra registers. */
			data->temp[1] += 125 * (i2c_smbus_read_byte_data(
				client, ADM1023_REG_REM_TEMP_PREC) >> 5);
			data->temp_max[1] += 125 * (i2c_smbus_read_byte_data(
				client, ADM1023_REG_REM_TOS_PREC) >> 5);
			data->temp_min[1] += 125 * (i2c_smbus_read_byte_data(
				client, ADM1023_REG_REM_THYST_PREC) >> 5);
			data->remote_temp_offset =
				i2c_smbus_read_byte_data(client,
						ADM1023_REG_REM_OFFSET);
			data->remote_temp_offset_prec =
				i2c_smbus_read_byte_data(client,
						ADM1023_REG_REM_OFFSET_PREC);
		}
		data->last_updated = jiffies;
		data->valid = 1;
	}

	mutex_unlock(&data->update_lock);

	return data;
}