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
struct vt1211_data {long** pwm_auto_pwm; int /*<<< orphan*/  update_lock; } ;
struct sensor_device_attribute_2 {int index; int nr; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  VT1211_REG_PWM_AUTO_PWM (int,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,long) ; 
 struct vt1211_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 long simple_strtol (char const*,int /*<<< orphan*/ *,int) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 
 int /*<<< orphan*/  vt1211_write8 (struct vt1211_data*,int /*<<< orphan*/ ,long) ; 

__attribute__((used)) static ssize_t set_pwm_auto_point_pwm(struct device *dev,
				      struct device_attribute *attr,
				      const char *buf, size_t count)
{
	struct vt1211_data *data = dev_get_drvdata(dev);
	struct sensor_device_attribute_2 *sensor_attr_2 =
						to_sensor_dev_attr_2(attr);
	int ix = sensor_attr_2->index;
	int ap = sensor_attr_2->nr;
	long val = simple_strtol(buf, NULL, 10);

	if ((val < 0) || (val > 255)) {
		dev_err(dev, "pwm value %ld is out of range. "
			"Choose a value between 0 and 255.\n" , val);
		return -EINVAL;
	}

	mutex_lock(&data->update_lock);
	data->pwm_auto_pwm[ix][ap] = val;
	vt1211_write8(data, VT1211_REG_PWM_AUTO_PWM(ix, ap),
		      data->pwm_auto_pwm[ix][ap]);
	mutex_unlock(&data->update_lock);

	return count;
}