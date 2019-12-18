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
typedef  scalar_t__ u8 ;
struct sensor_device_attribute_2 {size_t index; size_t nr; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct abituguru_data {scalar_t__** bank2_settings; int /*<<< orphan*/  update_lock; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int ABIT_UGURU_FAN_MAX ; 
 scalar_t__ ABIT_UGURU_SENSOR_BANK2 ; 
 size_t EINVAL ; 
 size_t EIO ; 
 scalar_t__ abituguru_bank2_max_threshold ; 
 scalar_t__ abituguru_bank2_min_threshold ; 
 size_t abituguru_write (struct abituguru_data*,scalar_t__,size_t,scalar_t__*,int) ; 
 struct abituguru_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t store_bank2_setting(struct device *dev, struct device_attribute
	*devattr, const char *buf, size_t count)
{
	struct sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	struct abituguru_data *data = dev_get_drvdata(dev);
	u8 val = (simple_strtoul(buf, NULL, 10)*255 + ABIT_UGURU_FAN_MAX/2) /
		ABIT_UGURU_FAN_MAX;
	ssize_t ret = count;

	/* this check can be done before taking the lock */
	if ((val < abituguru_bank2_min_threshold) ||
			(val > abituguru_bank2_max_threshold))
		return -EINVAL;

	mutex_lock(&data->update_lock);
	if (data->bank2_settings[attr->index][attr->nr] != val) {
		u8 orig_val = data->bank2_settings[attr->index][attr->nr];
		data->bank2_settings[attr->index][attr->nr] = val;
		if (abituguru_write(data, ABIT_UGURU_SENSOR_BANK2 + 2,
				attr->index, data->bank2_settings[attr->index],
				2) <= attr->nr) {
			data->bank2_settings[attr->index][attr->nr] = orig_val;
			ret = -EIO;
		}
	}
	mutex_unlock(&data->update_lock);
	return ret;
}