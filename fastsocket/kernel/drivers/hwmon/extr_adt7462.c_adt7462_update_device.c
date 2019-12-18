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
struct device {int dummy; } ;
struct adt7462_data {unsigned long sensors_last_updated; int sensors_valid; unsigned long limits_last_updated; int limits_valid; int /*<<< orphan*/  lock; void* cfg2; void* pwm_max; void** pwm_cfg; void** pwm_trange; void** pwm_tmin; void** pwm_min; void** volt_min; void** volt_max; void** fan_min; void** temp_max; void** temp_min; void** alarms; void** voltages; void** pin_cfg; void** pwm; void* fan_enabled; int /*<<< orphan*/ * fan; void** temp; void** temp_frac; } ;

/* Variables and functions */
 int ADT7462_FAN_COUNT ; 
 int ADT7462_PIN_CFG_REG_COUNT ; 
 int ADT7462_PWM_COUNT ; 
 int ADT7462_REG_ALARM1 ; 
 int ADT7462_REG_ALARM2 ; 
 int ADT7462_REG_ALARM3 ; 
 int ADT7462_REG_ALARM4 ; 
 int ADT7462_REG_CFG2 ; 
 int /*<<< orphan*/  ADT7462_REG_FAN (int) ; 
 int ADT7462_REG_FAN_ENABLE ; 
 int ADT7462_REG_FAN_MIN (int) ; 
 int ADT7462_REG_PIN_CFG (int) ; 
 int ADT7462_REG_PWM (int) ; 
 int ADT7462_REG_PWM_CFG (int) ; 
 int ADT7462_REG_PWM_MAX ; 
 int ADT7462_REG_PWM_MIN (int) ; 
 int ADT7462_REG_PWM_TMIN (int) ; 
 int ADT7462_REG_PWM_TRANGE (int) ; 
 int ADT7462_REG_VOLT (struct adt7462_data*,int) ; 
 int ADT7462_REG_VOLT_MAX (struct adt7462_data*,int) ; 
 int ADT7462_REG_VOLT_MIN (struct adt7462_data*,int) ; 
 int ADT7462_TEMP_COUNT ; 
 int ADT7462_TEMP_MAX_REG (int) ; 
 int ADT7462_TEMP_MIN_REG (int) ; 
 int ADT7462_TEMP_REG (int) ; 
 int ADT7462_VOLT_COUNT ; 
 scalar_t__ LIMIT_REFRESH_INTERVAL ; 
 scalar_t__ SENSOR_REFRESH_INTERVAL ; 
 int /*<<< orphan*/  adt7462_read_word_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 struct adt7462_data* i2c_get_clientdata (struct i2c_client*) ; 
 void* i2c_smbus_read_byte_data (struct i2c_client*,int) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_before (unsigned long,scalar_t__) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static struct adt7462_data *adt7462_update_device(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct adt7462_data *data = i2c_get_clientdata(client);
	unsigned long local_jiffies = jiffies;
	int i;

	mutex_lock(&data->lock);
	if (time_before(local_jiffies, data->sensors_last_updated +
		SENSOR_REFRESH_INTERVAL)
		&& data->sensors_valid)
		goto no_sensor_update;

	for (i = 0; i < ADT7462_TEMP_COUNT; i++) {
		/*
		 * Reading the fractional register locks the integral
		 * register until both have been read.
		 */
		data->temp_frac[i] = i2c_smbus_read_byte_data(client,
						ADT7462_TEMP_REG(i));
		data->temp[i] = i2c_smbus_read_byte_data(client,
						ADT7462_TEMP_REG(i) + 1);
	}

	for (i = 0; i < ADT7462_FAN_COUNT; i++)
		data->fan[i] = adt7462_read_word_data(client,
						ADT7462_REG_FAN(i));

	data->fan_enabled = i2c_smbus_read_byte_data(client,
					ADT7462_REG_FAN_ENABLE);

	for (i = 0; i < ADT7462_PWM_COUNT; i++)
		data->pwm[i] = i2c_smbus_read_byte_data(client,
						ADT7462_REG_PWM(i));

	for (i = 0; i < ADT7462_PIN_CFG_REG_COUNT; i++)
		data->pin_cfg[i] = i2c_smbus_read_byte_data(client,
				ADT7462_REG_PIN_CFG(i));

	for (i = 0; i < ADT7462_VOLT_COUNT; i++) {
		int reg = ADT7462_REG_VOLT(data, i);
		if (!reg)
			data->voltages[i] = 0;
		else
			data->voltages[i] = i2c_smbus_read_byte_data(client,
								     reg);
	}

	data->alarms[0] = i2c_smbus_read_byte_data(client, ADT7462_REG_ALARM1);
	data->alarms[1] = i2c_smbus_read_byte_data(client, ADT7462_REG_ALARM2);
	data->alarms[2] = i2c_smbus_read_byte_data(client, ADT7462_REG_ALARM3);
	data->alarms[3] = i2c_smbus_read_byte_data(client, ADT7462_REG_ALARM4);

	data->sensors_last_updated = local_jiffies;
	data->sensors_valid = 1;

no_sensor_update:
	if (time_before(local_jiffies, data->limits_last_updated +
		LIMIT_REFRESH_INTERVAL)
		&& data->limits_valid)
		goto out;

	for (i = 0; i < ADT7462_TEMP_COUNT; i++) {
		data->temp_min[i] = i2c_smbus_read_byte_data(client,
						ADT7462_TEMP_MIN_REG(i));
		data->temp_max[i] = i2c_smbus_read_byte_data(client,
						ADT7462_TEMP_MAX_REG(i));
	}

	for (i = 0; i < ADT7462_FAN_COUNT; i++)
		data->fan_min[i] = i2c_smbus_read_byte_data(client,
						ADT7462_REG_FAN_MIN(i));

	for (i = 0; i < ADT7462_VOLT_COUNT; i++) {
		int reg = ADT7462_REG_VOLT_MAX(data, i);
		data->volt_max[i] =
			(reg ? i2c_smbus_read_byte_data(client, reg) : 0);

		reg = ADT7462_REG_VOLT_MIN(data, i);
		data->volt_min[i] =
			(reg ? i2c_smbus_read_byte_data(client, reg) : 0);
	}

	for (i = 0; i < ADT7462_PWM_COUNT; i++) {
		data->pwm_min[i] = i2c_smbus_read_byte_data(client,
						ADT7462_REG_PWM_MIN(i));
		data->pwm_tmin[i] = i2c_smbus_read_byte_data(client,
						ADT7462_REG_PWM_TMIN(i));
		data->pwm_trange[i] = i2c_smbus_read_byte_data(client,
						ADT7462_REG_PWM_TRANGE(i));
		data->pwm_cfg[i] = i2c_smbus_read_byte_data(client,
						ADT7462_REG_PWM_CFG(i));
	}

	data->pwm_max = i2c_smbus_read_byte_data(client, ADT7462_REG_PWM_MAX);

	data->cfg2 = i2c_smbus_read_byte_data(client, ADT7462_REG_CFG2);

	data->limits_last_updated = local_jiffies;
	data->limits_valid = 1;

out:
	mutex_unlock(&data->lock);
	return data;
}