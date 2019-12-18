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
struct w83627hf_data {int beep_mask; int /*<<< orphan*/  update_lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int BEEP_MASK_TO_REG (unsigned long) ; 
 int /*<<< orphan*/  W83781D_REG_BEEP_INTS1 ; 
 int /*<<< orphan*/  W83781D_REG_BEEP_INTS2 ; 
 int /*<<< orphan*/  W83781D_REG_BEEP_INTS3 ; 
 struct w83627hf_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned long simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  w83627hf_write_value (struct w83627hf_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t
store_beep_mask(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t count)
{
	struct w83627hf_data *data = dev_get_drvdata(dev);
	unsigned long val;

	val = simple_strtoul(buf, NULL, 10);

	mutex_lock(&data->update_lock);

	/* preserve beep enable */
	data->beep_mask = (data->beep_mask & 0x8000)
			| BEEP_MASK_TO_REG(val);
	w83627hf_write_value(data, W83781D_REG_BEEP_INTS1,
			    data->beep_mask & 0xff);
	w83627hf_write_value(data, W83781D_REG_BEEP_INTS3,
			    ((data->beep_mask) >> 16) & 0xff);
	w83627hf_write_value(data, W83781D_REG_BEEP_INTS2,
			    (data->beep_mask >> 8) & 0xff);

	mutex_unlock(&data->update_lock);
	return count;
}