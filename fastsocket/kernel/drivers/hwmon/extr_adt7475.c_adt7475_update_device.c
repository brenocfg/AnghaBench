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
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;
struct adt7475_data {int valid; int alarms; int** voltage; int** temp; int** pwm; int config5; int* range; int /*<<< orphan*/  lock; void* limits_updated; void*** tach; void* measure_updated; } ;

/* Variables and functions */
 int ADT7475_PWM_COUNT ; 
 int ADT7475_TACH_COUNT ; 
 int ADT7475_TEMP_COUNT ; 
 int ADT7475_VOLTAGE_COUNT ; 
 size_t AUTOMIN ; 
 int HZ ; 
 size_t INPUT ; 
 size_t MAX ; 
 size_t MIN ; 
 size_t OFFSET ; 
 int /*<<< orphan*/  PWM_MAX_REG (int) ; 
 int /*<<< orphan*/  PWM_MIN_REG (int) ; 
 int /*<<< orphan*/  PWM_REG (int) ; 
 int /*<<< orphan*/  REG_CONFIG5 ; 
 int /*<<< orphan*/  REG_EXTEND1 ; 
 int /*<<< orphan*/  REG_EXTEND2 ; 
 int /*<<< orphan*/  REG_STATUS1 ; 
 int /*<<< orphan*/  REG_STATUS2 ; 
 int /*<<< orphan*/  TACH_MIN_REG (int) ; 
 int /*<<< orphan*/  TACH_REG (int) ; 
 int /*<<< orphan*/  TEMP_MAX_REG (int) ; 
 int /*<<< orphan*/  TEMP_MIN_REG (int) ; 
 int /*<<< orphan*/  TEMP_OFFSET_REG (int) ; 
 int /*<<< orphan*/  TEMP_REG (int) ; 
 int /*<<< orphan*/  TEMP_THERM_REG (int) ; 
 int /*<<< orphan*/  TEMP_TMIN_REG (int) ; 
 int /*<<< orphan*/  TEMP_TRANGE_REG (int) ; 
 size_t THERM ; 
 int /*<<< orphan*/  VOLTAGE_MAX_REG (int) ; 
 int /*<<< orphan*/  VOLTAGE_MIN_REG (int) ; 
 int /*<<< orphan*/  VOLTAGE_REG (int) ; 
 int adt7475_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adt7475_read_hystersis (struct i2c_client*) ; 
 int /*<<< orphan*/  adt7475_read_pwm (struct i2c_client*,int) ; 
 void* adt7475_read_word (struct i2c_client*,int /*<<< orphan*/ ) ; 
 struct adt7475_data* i2c_get_clientdata (struct i2c_client*) ; 
 void* jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (void*,void*) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static struct adt7475_data *adt7475_update_device(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct adt7475_data *data = i2c_get_clientdata(client);
	u8 ext;
	int i;

	mutex_lock(&data->lock);

	/* Measurement values update every 2 seconds */
	if (time_after(jiffies, data->measure_updated + HZ * 2) ||
	    !data->valid) {
		data->alarms = adt7475_read(REG_STATUS2) << 8;
		data->alarms |= adt7475_read(REG_STATUS1);

		ext = adt7475_read(REG_EXTEND1);
		for (i = 0; i < ADT7475_VOLTAGE_COUNT; i++)
			data->voltage[INPUT][i] =
				(adt7475_read(VOLTAGE_REG(i)) << 2) |
				((ext >> ((i + 1) * 2)) & 3);

		ext = adt7475_read(REG_EXTEND2);
		for (i = 0; i < ADT7475_TEMP_COUNT; i++)
			data->temp[INPUT][i] =
				(adt7475_read(TEMP_REG(i)) << 2) |
				((ext >> ((i + 1) * 2)) & 3);

		for (i = 0; i < ADT7475_TACH_COUNT; i++)
			data->tach[INPUT][i] =
				adt7475_read_word(client, TACH_REG(i));

		/* Updated by hw when in auto mode */
		for (i = 0; i < ADT7475_PWM_COUNT; i++)
			data->pwm[INPUT][i] = adt7475_read(PWM_REG(i));

		data->measure_updated = jiffies;
	}

	/* Limits and settings, should never change update every 60 seconds */
	if (time_after(jiffies, data->limits_updated + HZ * 60) ||
	    !data->valid) {
		data->config5 = adt7475_read(REG_CONFIG5);

		for (i = 0; i < ADT7475_VOLTAGE_COUNT; i++) {
			/* Adjust values so they match the input precision */
			data->voltage[MIN][i] =
				adt7475_read(VOLTAGE_MIN_REG(i)) << 2;
			data->voltage[MAX][i] =
				adt7475_read(VOLTAGE_MAX_REG(i)) << 2;
		}

		for (i = 0; i < ADT7475_TEMP_COUNT; i++) {
			/* Adjust values so they match the input precision */
			data->temp[MIN][i] =
				adt7475_read(TEMP_MIN_REG(i)) << 2;
			data->temp[MAX][i] =
				adt7475_read(TEMP_MAX_REG(i)) << 2;
			data->temp[AUTOMIN][i] =
				adt7475_read(TEMP_TMIN_REG(i)) << 2;
			data->temp[THERM][i] =
				adt7475_read(TEMP_THERM_REG(i)) << 2;
			data->temp[OFFSET][i] =
				adt7475_read(TEMP_OFFSET_REG(i));
		}
		adt7475_read_hystersis(client);

		for (i = 0; i < ADT7475_TACH_COUNT; i++)
			data->tach[MIN][i] =
				adt7475_read_word(client, TACH_MIN_REG(i));

		for (i = 0; i < ADT7475_PWM_COUNT; i++) {
			data->pwm[MAX][i] = adt7475_read(PWM_MAX_REG(i));
			data->pwm[MIN][i] = adt7475_read(PWM_MIN_REG(i));
			/* Set the channel and control information */
			adt7475_read_pwm(client, i);
		}

		data->range[0] = adt7475_read(TEMP_TRANGE_REG(0));
		data->range[1] = adt7475_read(TEMP_TRANGE_REG(1));
		data->range[2] = adt7475_read(TEMP_TRANGE_REG(2));

		data->limits_updated = jiffies;
		data->valid = 1;
	}

	mutex_unlock(&data->lock);

	return data;
}