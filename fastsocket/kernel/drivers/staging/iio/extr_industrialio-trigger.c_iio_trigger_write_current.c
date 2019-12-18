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
struct iio_trigger {int dummy; } ;
struct iio_dev {scalar_t__ currentmode; struct iio_trigger* trig; int /*<<< orphan*/  mlock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EBUSY ; 
 size_t IIO_TRIGGER_NAME_LENGTH ; 
 scalar_t__ INDIO_RING_TRIGGERED ; 
 struct iio_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  iio_get_trigger (struct iio_trigger*) ; 
 int /*<<< orphan*/  iio_put_trigger (struct iio_trigger*) ; 
 struct iio_trigger* iio_trigger_find_by_name (char const*,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t iio_trigger_write_current(struct device *dev,
					 struct device_attribute *attr,
					 const char *buf,
					 size_t len)
{
	struct iio_dev *dev_info = dev_get_drvdata(dev);
	struct iio_trigger *oldtrig = dev_info->trig;
	mutex_lock(&dev_info->mlock);
	if (dev_info->currentmode == INDIO_RING_TRIGGERED) {
		mutex_unlock(&dev_info->mlock);
		return -EBUSY;
	}
	mutex_unlock(&dev_info->mlock);

	len = len < IIO_TRIGGER_NAME_LENGTH ? len : IIO_TRIGGER_NAME_LENGTH;

	dev_info->trig = iio_trigger_find_by_name(buf, len);
	if (oldtrig && dev_info->trig != oldtrig)
		iio_put_trigger(oldtrig);
	if (dev_info->trig)
		iio_get_trigger(dev_info->trig);

	return len;
}