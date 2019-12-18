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
struct max1363_state {struct max1363_mode const* current_mode; int /*<<< orphan*/  chip_info; } ;
struct max1363_mode {int dummy; } ;
struct iio_dev {int /*<<< orphan*/  mlock; struct max1363_state* dev_data; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 struct max1363_mode* __max1363_find_mode_in_ci (int /*<<< orphan*/ ,char const*) ; 
 struct iio_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  iio_ring_enabled (struct iio_dev*) ; 
 int max1363_set_scan_mode (struct max1363_state*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t max1363_store_scan_mode(struct device *dev,
				       struct device_attribute *attr,
				       const char *buf,
				       size_t len)
{
	struct iio_dev *dev_info = dev_get_drvdata(dev);
	struct max1363_state *st = dev_info->dev_data;
	const struct max1363_mode *new_mode;
	int ret;

	mutex_lock(&dev_info->mlock);
	new_mode = NULL;
	/* Avoid state changes if a ring buffer is enabled */
	if (!iio_ring_enabled(dev_info)) {
		new_mode
			= __max1363_find_mode_in_ci(st->chip_info, buf);
		if (!new_mode) {
			ret = -EINVAL;
			goto error_ret;
		}
		st->current_mode = new_mode;
		ret =  max1363_set_scan_mode(st);
		if (ret)
			goto error_ret;
	} else {
		ret = -EBUSY;
		goto error_ret;
	}
	mutex_unlock(&dev_info->mlock);

	return len;

error_ret:
	mutex_unlock(&dev_info->mlock);

	return ret;
}