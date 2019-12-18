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
struct iio_dev {scalar_t__ currentmode; int /*<<< orphan*/  mlock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ INDIO_RING_TRIGGERED ; 
 struct iio_dev* dev_get_drvdata (struct device*) ; 
 int max1363_scan_direct (struct device*,struct device_attribute*,char*) ; 
 int max1363_scan_from_ring (struct device*,struct device_attribute*,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t max1363_scan(struct device *dev,
			    struct device_attribute *attr,
			    char *buf)
{
	struct iio_dev *dev_info = dev_get_drvdata(dev);
	int ret;

	mutex_lock(&dev_info->mlock);
	if (dev_info->currentmode == INDIO_RING_TRIGGERED)
		ret = max1363_scan_from_ring(dev, attr, buf);
	else
		ret = max1363_scan_direct(dev, attr, buf);
	mutex_unlock(&dev_info->mlock);

	return ret;
}