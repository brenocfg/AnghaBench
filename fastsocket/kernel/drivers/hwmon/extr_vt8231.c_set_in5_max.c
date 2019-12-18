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
struct vt8231_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * in_max; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  SENSORS_LIMIT (unsigned long,int /*<<< orphan*/ ,int) ; 
 struct vt8231_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * regvoltmax ; 
 unsigned long simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vt8231_write_value (struct vt8231_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t set_in5_max(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t count)
{
	struct vt8231_data *data = dev_get_drvdata(dev);
	unsigned long val = simple_strtoul(buf, NULL, 10);

	mutex_lock(&data->update_lock);
	data->in_max[5] = SENSORS_LIMIT(((val * 958 * 34) / (10000 * 54)) + 3,
					0, 255);
	vt8231_write_value(data, regvoltmax[5], data->in_max[5]);
	mutex_unlock(&data->update_lock);
	return count;
}