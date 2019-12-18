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
struct vt8231_data {int* fan_min; int* fan_div; int /*<<< orphan*/  update_lock; } ;
struct sensor_device_attribute {int index; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_FROM_REG (int) ; 
 size_t EINVAL ; 
 long FAN_FROM_REG (int,int /*<<< orphan*/ ) ; 
 int FAN_TO_REG (long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VT8231_REG_FANDIV ; 
 int /*<<< orphan*/  VT8231_REG_FAN_MIN (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned long) ; 
 struct vt8231_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned long simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 
 int vt8231_read_value (struct vt8231_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vt8231_write_value (struct vt8231_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t set_fan_div(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t count)
{
	struct vt8231_data *data = dev_get_drvdata(dev);
	struct sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	unsigned long val = simple_strtoul(buf, NULL, 10);
	int nr = sensor_attr->index;
	int old = vt8231_read_value(data, VT8231_REG_FANDIV);
	long min = FAN_FROM_REG(data->fan_min[nr],
				 DIV_FROM_REG(data->fan_div[nr]));

	mutex_lock(&data->update_lock);
	switch (val) {
	case 1: data->fan_div[nr] = 0; break;
	case 2: data->fan_div[nr] = 1; break;
	case 4: data->fan_div[nr] = 2; break;
	case 8: data->fan_div[nr] = 3; break;
	default:
		dev_err(dev, "fan_div value %ld not supported. "
		        "Choose one of 1, 2, 4 or 8!\n", val);
		mutex_unlock(&data->update_lock);
		return -EINVAL;
	}

	/* Correct the fan minimum speed */
	data->fan_min[nr] = FAN_TO_REG(min, DIV_FROM_REG(data->fan_div[nr]));
	vt8231_write_value(data, VT8231_REG_FAN_MIN(nr), data->fan_min[nr]);

	old = (old & 0x0f) | (data->fan_div[1] << 6) | (data->fan_div[0] << 4);
	vt8231_write_value(data, VT8231_REG_FANDIV, old);
	mutex_unlock(&data->update_lock);
	return count;
}