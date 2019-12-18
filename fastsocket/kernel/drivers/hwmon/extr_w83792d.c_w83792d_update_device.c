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
struct w83792d_data {int valid; int* in; int* in_max; int* in_min; int low_bits; int* fan; int* fan_min; int* pwm; int* pwmenable; int* temp1; int** temp_add; int* fan_div; int alarms; int chassis; int chassis_clear; int* thermal_cruise; int* tolerance; int** sf2_points; int** sf2_levels; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  W83792D_REG_ALARM1 ; 
 int /*<<< orphan*/  W83792D_REG_ALARM2 ; 
 int /*<<< orphan*/  W83792D_REG_ALARM3 ; 
 int /*<<< orphan*/  W83792D_REG_CHASSIS ; 
 int /*<<< orphan*/  W83792D_REG_CHASSIS_CLR ; 
 int /*<<< orphan*/ * W83792D_REG_FAN ; 
 int /*<<< orphan*/  W83792D_REG_FAN_CFG ; 
 int /*<<< orphan*/ * W83792D_REG_FAN_DIV ; 
 int /*<<< orphan*/ * W83792D_REG_FAN_MIN ; 
 int /*<<< orphan*/ * W83792D_REG_IN ; 
 int /*<<< orphan*/ * W83792D_REG_IN_MAX ; 
 int /*<<< orphan*/ * W83792D_REG_IN_MIN ; 
 int /*<<< orphan*/ ** W83792D_REG_LEVELS ; 
 int /*<<< orphan*/  W83792D_REG_LOW_BITS1 ; 
 int /*<<< orphan*/  W83792D_REG_LOW_BITS2 ; 
 int /*<<< orphan*/ ** W83792D_REG_POINTS ; 
 int /*<<< orphan*/ * W83792D_REG_PWM ; 
 int /*<<< orphan*/ * W83792D_REG_TEMP1 ; 
 int /*<<< orphan*/ ** W83792D_REG_TEMP_ADD ; 
 int /*<<< orphan*/ * W83792D_REG_THERMAL ; 
 int /*<<< orphan*/ * W83792D_REG_TOLERANCE ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 struct w83792d_data* i2c_get_clientdata (struct i2c_client*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,unsigned long) ; 
 scalar_t__ time_before (scalar_t__,scalar_t__) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 int /*<<< orphan*/  w83792d_print_debug (struct w83792d_data*,struct device*) ; 
 int w83792d_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct w83792d_data *w83792d_update_device(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct w83792d_data *data = i2c_get_clientdata(client);
	int i, j;
	u8 reg_array_tmp[4], reg_tmp;

	mutex_lock(&data->update_lock);

	if (time_after
	    (jiffies - data->last_updated, (unsigned long) (HZ * 3))
	    || time_before(jiffies, data->last_updated) || !data->valid) {
		dev_dbg(dev, "Starting device update\n");

		/* Update the voltages measured value and limits */
		for (i = 0; i < 9; i++) {
			data->in[i] = w83792d_read_value(client,
						W83792D_REG_IN[i]);
			data->in_max[i] = w83792d_read_value(client,
						W83792D_REG_IN_MAX[i]);
			data->in_min[i] = w83792d_read_value(client,
						W83792D_REG_IN_MIN[i]);
		}
		data->low_bits = w83792d_read_value(client,
						W83792D_REG_LOW_BITS1) +
				 (w83792d_read_value(client,
						W83792D_REG_LOW_BITS2) << 8);
		for (i = 0; i < 7; i++) {
			/* Update the Fan measured value and limits */
			data->fan[i] = w83792d_read_value(client,
						W83792D_REG_FAN[i]);
			data->fan_min[i] = w83792d_read_value(client,
						W83792D_REG_FAN_MIN[i]);
			/* Update the PWM/DC Value and PWM/DC flag */
			data->pwm[i] = w83792d_read_value(client,
						W83792D_REG_PWM[i]);
		}

		reg_tmp = w83792d_read_value(client, W83792D_REG_FAN_CFG);
		data->pwmenable[0] = reg_tmp & 0x03;
		data->pwmenable[1] = (reg_tmp>>2) & 0x03;
		data->pwmenable[2] = (reg_tmp>>4) & 0x03;

		for (i = 0; i < 3; i++) {
			data->temp1[i] = w83792d_read_value(client,
							W83792D_REG_TEMP1[i]);
		}
		for (i = 0; i < 2; i++) {
			for (j = 0; j < 6; j++) {
				data->temp_add[i][j] = w83792d_read_value(
					client,W83792D_REG_TEMP_ADD[i][j]);
			}
		}

		/* Update the Fan Divisor */
		for (i = 0; i < 4; i++) {
			reg_array_tmp[i] = w83792d_read_value(client,
							W83792D_REG_FAN_DIV[i]);
		}
		data->fan_div[0] = reg_array_tmp[0] & 0x07;
		data->fan_div[1] = (reg_array_tmp[0] >> 4) & 0x07;
		data->fan_div[2] = reg_array_tmp[1] & 0x07;
		data->fan_div[3] = (reg_array_tmp[1] >> 4) & 0x07;
		data->fan_div[4] = reg_array_tmp[2] & 0x07;
		data->fan_div[5] = (reg_array_tmp[2] >> 4) & 0x07;
		data->fan_div[6] = reg_array_tmp[3] & 0x07;

		/* Update the realtime status */
		data->alarms = w83792d_read_value(client, W83792D_REG_ALARM1) +
			(w83792d_read_value(client, W83792D_REG_ALARM2) << 8) +
			(w83792d_read_value(client, W83792D_REG_ALARM3) << 16);

		/* Update CaseOpen status and it's CLR_CHS. */
		data->chassis = (w83792d_read_value(client,
			W83792D_REG_CHASSIS) >> 5) & 0x01;
		data->chassis_clear = (w83792d_read_value(client,
			W83792D_REG_CHASSIS_CLR) >> 7) & 0x01;

		/* Update Thermal Cruise/Smart Fan I target value */
		for (i = 0; i < 3; i++) {
			data->thermal_cruise[i] =
				w83792d_read_value(client,
				W83792D_REG_THERMAL[i]) & 0x7f;
		}

		/* Update Smart Fan I/II tolerance */
		reg_tmp = w83792d_read_value(client, W83792D_REG_TOLERANCE[0]);
		data->tolerance[0] = reg_tmp & 0x0f;
		data->tolerance[1] = (reg_tmp >> 4) & 0x0f;
		data->tolerance[2] = w83792d_read_value(client,
					W83792D_REG_TOLERANCE[2]) & 0x0f;

		/* Update Smart Fan II temperature points */
		for (i = 0; i < 3; i++) {
			for (j = 0; j < 4; j++) {
				data->sf2_points[i][j] = w83792d_read_value(
					client,W83792D_REG_POINTS[i][j]) & 0x7f;
			}
		}

		/* Update Smart Fan II duty cycle levels */
		for (i = 0; i < 3; i++) {
			reg_tmp = w83792d_read_value(client,
						W83792D_REG_LEVELS[i][0]);
			data->sf2_levels[i][0] = reg_tmp & 0x0f;
			data->sf2_levels[i][1] = (reg_tmp >> 4) & 0x0f;
			reg_tmp = w83792d_read_value(client,
						W83792D_REG_LEVELS[i][2]);
			data->sf2_levels[i][2] = (reg_tmp >> 4) & 0x0f;
			data->sf2_levels[i][3] = reg_tmp & 0x0f;
		}

		data->last_updated = jiffies;
		data->valid = 1;
	}

	mutex_unlock(&data->update_lock);

#ifdef DEBUG
	w83792d_print_debug(data, dev);
#endif

	return data;
}