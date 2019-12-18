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
struct w83627hf_data {int beep_mask; int /*<<< orphan*/  update_lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  W83781D_REG_BEEP_INTS1 ; 
 int /*<<< orphan*/  W83781D_REG_BEEP_INTS2 ; 
 int /*<<< orphan*/  W83781D_REG_BEEP_INTS3 ; 
 struct w83627hf_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned long simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 
 int w83627hf_read_value (struct w83627hf_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w83627hf_write_value (struct w83627hf_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t
store_beep(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t count)
{
	struct w83627hf_data *data = dev_get_drvdata(dev);
	int bitnr = to_sensor_dev_attr(attr)->index;
	unsigned long bit;
	u8 reg;

	bit = simple_strtoul(buf, NULL, 10);
	if (bit & ~1)
		return -EINVAL;

	mutex_lock(&data->update_lock);
	if (bit)
		data->beep_mask |= (1 << bitnr);
	else
		data->beep_mask &= ~(1 << bitnr);

	if (bitnr < 8) {
		reg = w83627hf_read_value(data, W83781D_REG_BEEP_INTS1);
		if (bit)
			reg |= (1 << bitnr);
		else
			reg &= ~(1 << bitnr);
		w83627hf_write_value(data, W83781D_REG_BEEP_INTS1, reg);
	} else if (bitnr < 16) {
		reg = w83627hf_read_value(data, W83781D_REG_BEEP_INTS2);
		if (bit)
			reg |= (1 << (bitnr - 8));
		else
			reg &= ~(1 << (bitnr - 8));
		w83627hf_write_value(data, W83781D_REG_BEEP_INTS2, reg);
	} else {
		reg = w83627hf_read_value(data, W83781D_REG_BEEP_INTS3);
		if (bit)
			reg |= (1 << (bitnr - 16));
		else
			reg &= ~(1 << (bitnr - 16));
		w83627hf_write_value(data, W83781D_REG_BEEP_INTS3, reg);
	}
	mutex_unlock(&data->update_lock);

	return count;
}