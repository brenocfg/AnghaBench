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
struct f71882fg_data {long** pwm_auto_point_temp; int /*<<< orphan*/  update_lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int index; int nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  F71882FG_REG_POINT_TEMP (int,int) ; 
 long SENSORS_LIMIT (long,int /*<<< orphan*/ ,int) ; 
 struct f71882fg_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  f71882fg_write8 (struct f71882fg_data*,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int simple_strtol (char const*,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t store_pwm_auto_point_temp(struct device *dev,
					 struct device_attribute *devattr,
					 const char *buf, size_t count)
{
	struct f71882fg_data *data = dev_get_drvdata(dev);
	int pwm = to_sensor_dev_attr_2(devattr)->index;
	int point = to_sensor_dev_attr_2(devattr)->nr;
	long val = simple_strtol(buf, NULL, 10) / 1000;
	val = SENSORS_LIMIT(val, 0, 255);

	mutex_lock(&data->update_lock);
	f71882fg_write8(data, F71882FG_REG_POINT_TEMP(pwm, point), val);
	data->pwm_auto_point_temp[pwm][point] = val;
	mutex_unlock(&data->update_lock);

	return count;
}