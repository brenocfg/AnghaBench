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
struct lm78_data {int valid; int* in; int* in_min; int* in_max; int* fan; int* fan_min; int temp; int temp_over; int temp_hyst; int vid; scalar_t__ type; int* fan_div; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; int /*<<< orphan*/  alarms; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  LM78_REG_ALARM1 ; 
 int /*<<< orphan*/  LM78_REG_ALARM2 ; 
 int /*<<< orphan*/  LM78_REG_CHIPID ; 
 int /*<<< orphan*/  LM78_REG_FAN (int) ; 
 int /*<<< orphan*/  LM78_REG_FAN_MIN (int) ; 
 int /*<<< orphan*/  LM78_REG_IN (int) ; 
 int /*<<< orphan*/  LM78_REG_IN_MAX (int) ; 
 int /*<<< orphan*/  LM78_REG_IN_MIN (int) ; 
 int /*<<< orphan*/  LM78_REG_TEMP ; 
 int /*<<< orphan*/  LM78_REG_TEMP_HYST ; 
 int /*<<< orphan*/  LM78_REG_TEMP_OVER ; 
 int /*<<< orphan*/  LM78_REG_VID_FANDIV ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 struct lm78_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ jiffies ; 
 int lm78_read_value (struct lm78_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ lm79 ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct lm78_data *lm78_update_device(struct device *dev)
{
	struct lm78_data *data = dev_get_drvdata(dev);
	int i;

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + HZ + HZ / 2)
	    || !data->valid) {

		dev_dbg(dev, "Starting lm78 update\n");

		for (i = 0; i <= 6; i++) {
			data->in[i] =
			    lm78_read_value(data, LM78_REG_IN(i));
			data->in_min[i] =
			    lm78_read_value(data, LM78_REG_IN_MIN(i));
			data->in_max[i] =
			    lm78_read_value(data, LM78_REG_IN_MAX(i));
		}
		for (i = 0; i < 3; i++) {
			data->fan[i] =
			    lm78_read_value(data, LM78_REG_FAN(i));
			data->fan_min[i] =
			    lm78_read_value(data, LM78_REG_FAN_MIN(i));
		}
		data->temp = lm78_read_value(data, LM78_REG_TEMP);
		data->temp_over =
		    lm78_read_value(data, LM78_REG_TEMP_OVER);
		data->temp_hyst =
		    lm78_read_value(data, LM78_REG_TEMP_HYST);
		i = lm78_read_value(data, LM78_REG_VID_FANDIV);
		data->vid = i & 0x0f;
		if (data->type == lm79)
			data->vid |=
			    (lm78_read_value(data, LM78_REG_CHIPID) &
			     0x01) << 4;
		else
			data->vid |= 0x10;
		data->fan_div[0] = (i >> 4) & 0x03;
		data->fan_div[1] = i >> 6;
		data->alarms = lm78_read_value(data, LM78_REG_ALARM1) +
		    (lm78_read_value(data, LM78_REG_ALARM2) << 8);
		data->last_updated = jiffies;
		data->valid = 1;

		data->fan_div[2] = 1;
	}

	mutex_unlock(&data->update_lock);

	return data;
}