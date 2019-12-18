#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct f71882fg_data {int** pwm_auto_point_temp; int* pwm_auto_point_hyst; int /*<<< orphan*/  update_lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int index; int nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  F71882FG_REG_FAN_HYST (int) ; 
 int /*<<< orphan*/  F71882FG_REG_POINT_TEMP (int,int) ; 
 long SENSORS_LIMIT (long,int,int) ; 
 struct f71882fg_data* dev_get_drvdata (struct device*) ; 
 void* f71882fg_read8 (struct f71882fg_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f71882fg_write8 (struct f71882fg_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int simple_strtol (char const*,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t store_pwm_auto_point_temp_hyst(struct device *dev,
					      struct device_attribute *devattr,
					      const char *buf, size_t count)
{
	struct f71882fg_data *data = dev_get_drvdata(dev);
	int nr = to_sensor_dev_attr_2(devattr)->index;
	int point = to_sensor_dev_attr_2(devattr)->nr;
	long val = simple_strtol(buf, NULL, 10) / 1000;
	u8 reg;

	mutex_lock(&data->update_lock);
	data->pwm_auto_point_temp[nr][point] =
		f71882fg_read8(data, F71882FG_REG_POINT_TEMP(nr, point));
	val = SENSORS_LIMIT(val, data->pwm_auto_point_temp[nr][point] - 15,
				data->pwm_auto_point_temp[nr][point]);
	val = data->pwm_auto_point_temp[nr][point] - val;

	reg = f71882fg_read8(data, F71882FG_REG_FAN_HYST(nr / 2));
	if (nr & 1)
		reg = (reg & 0x0f) | (val << 4);
	else
		reg = (reg & 0xf0) | val;

	f71882fg_write8(data, F71882FG_REG_FAN_HYST(nr / 2), reg);
	data->pwm_auto_point_hyst[nr / 2] = reg;
	mutex_unlock(&data->update_lock);

	return count;
}