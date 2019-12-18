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
struct fschmd_data {int valid; size_t kind; scalar_t__* temp_act; int* temp_status; scalar_t__* temp_max; int* fan_status; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; void** volt; void** fan_act; void** fan_min; void** fan_ripple; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int FSCHMD_FAN_ALARM ; 
 int* FSCHMD_NO_FAN_SENSORS ; 
 int* FSCHMD_NO_TEMP_SENSORS ; 
 int* FSCHMD_NO_VOLT_SENSORS ; 
 scalar_t__** FSCHMD_REG_FAN_ACT ; 
 scalar_t__** FSCHMD_REG_FAN_MIN ; 
 scalar_t__** FSCHMD_REG_FAN_RIPPLE ; 
 scalar_t__** FSCHMD_REG_FAN_STATE ; 
 scalar_t__** FSCHMD_REG_TEMP_ACT ; 
 scalar_t__** FSCHMD_REG_TEMP_LIMIT ; 
 scalar_t__** FSCHMD_REG_TEMP_STATE ; 
 scalar_t__** FSCHMD_REG_VOLT ; 
 int FSCHMD_TEMP_ALARM_MASK ; 
 int HZ ; 
 struct fschmd_data* i2c_get_clientdata (struct i2c_client*) ; 
 void* i2c_smbus_read_byte_data (struct i2c_client*,scalar_t__) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,scalar_t__,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static struct fschmd_data *fschmd_update_device(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct fschmd_data *data = i2c_get_clientdata(client);
	int i;

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + 2 * HZ) || !data->valid) {

		for (i = 0; i < FSCHMD_NO_TEMP_SENSORS[data->kind]; i++) {
			data->temp_act[i] = i2c_smbus_read_byte_data(client,
					FSCHMD_REG_TEMP_ACT[data->kind][i]);
			data->temp_status[i] = i2c_smbus_read_byte_data(client,
					FSCHMD_REG_TEMP_STATE[data->kind][i]);

			/* The fscpos doesn't have TEMP_LIMIT registers */
			if (FSCHMD_REG_TEMP_LIMIT[data->kind][i])
				data->temp_max[i] = i2c_smbus_read_byte_data(
					client,
					FSCHMD_REG_TEMP_LIMIT[data->kind][i]);

			/* reset alarm if the alarm condition is gone,
			   the chip doesn't do this itself */
			if ((data->temp_status[i] & FSCHMD_TEMP_ALARM_MASK) ==
					FSCHMD_TEMP_ALARM_MASK &&
					data->temp_act[i] < data->temp_max[i])
				i2c_smbus_write_byte_data(client,
					FSCHMD_REG_TEMP_STATE[data->kind][i],
					data->temp_status[i]);
		}

		for (i = 0; i < FSCHMD_NO_FAN_SENSORS[data->kind]; i++) {
			data->fan_act[i] = i2c_smbus_read_byte_data(client,
					FSCHMD_REG_FAN_ACT[data->kind][i]);
			data->fan_status[i] = i2c_smbus_read_byte_data(client,
					FSCHMD_REG_FAN_STATE[data->kind][i]);
			data->fan_ripple[i] = i2c_smbus_read_byte_data(client,
					FSCHMD_REG_FAN_RIPPLE[data->kind][i]);

			/* The fscpos third fan doesn't have a fan_min */
			if (FSCHMD_REG_FAN_MIN[data->kind][i])
				data->fan_min[i] = i2c_smbus_read_byte_data(
					client,
					FSCHMD_REG_FAN_MIN[data->kind][i]);

			/* reset fan status if speed is back to > 0 */
			if ((data->fan_status[i] & FSCHMD_FAN_ALARM) &&
					data->fan_act[i])
				i2c_smbus_write_byte_data(client,
					FSCHMD_REG_FAN_STATE[data->kind][i],
					data->fan_status[i]);
		}

		for (i = 0; i < FSCHMD_NO_VOLT_SENSORS[data->kind]; i++)
			data->volt[i] = i2c_smbus_read_byte_data(client,
					       FSCHMD_REG_VOLT[data->kind][i]);

		data->last_updated = jiffies;
		data->valid = 1;
	}

	mutex_unlock(&data->update_lock);

	return data;
}