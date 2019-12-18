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
struct vt1211_data {int /*<<< orphan*/  update_lock; void** temp_hyst; void** temp_max; } ;
struct sensor_device_attribute_2 {int index; int nr; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
#define  SHOW_SET_TEMP_MAX 129 
#define  SHOW_SET_TEMP_MAX_HYST 128 
 void* TEMP_TO_REG (int,long) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 struct vt1211_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * regtemphyst ; 
 int /*<<< orphan*/ * regtempmax ; 
 long simple_strtol (char const*,int /*<<< orphan*/ *,int) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 
 int /*<<< orphan*/  vt1211_write8 (struct vt1211_data*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static ssize_t set_temp(struct device *dev, struct device_attribute *attr,
			const char *buf, size_t count)
{
	struct vt1211_data *data = dev_get_drvdata(dev);
	struct sensor_device_attribute_2 *sensor_attr_2 =
						to_sensor_dev_attr_2(attr);
	int ix = sensor_attr_2->index;
	int fn = sensor_attr_2->nr;
	long val = simple_strtol(buf, NULL, 10);

	mutex_lock(&data->update_lock);
	switch (fn) {
	case SHOW_SET_TEMP_MAX:
		data->temp_max[ix] = TEMP_TO_REG(ix, val);
		vt1211_write8(data, regtempmax[ix],
			      data->temp_max[ix]);
		break;
	case SHOW_SET_TEMP_MAX_HYST:
		data->temp_hyst[ix] = TEMP_TO_REG(ix, val);
		vt1211_write8(data, regtemphyst[ix],
			      data->temp_hyst[ix]);
		break;
	default:
		dev_dbg(dev, "Unknown attr fetch (%d)\n", fn);
	}
	mutex_unlock(&data->update_lock);

	return count;
}