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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ INDIO_RING_TRIGGERED ; 
 struct iio_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  lis3l02dq_read_16bit_signed (struct device*,struct device_attribute*,char*) ; 
 int /*<<< orphan*/  lis3l02dq_read_accel_from_ring (struct device*,struct device_attribute*,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t lis3l02dq_read_accel(struct device *dev,
				    struct device_attribute *attr,
				    char *buf)
{
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	ssize_t ret;

	/* Take the iio_dev status lock */
	mutex_lock(&indio_dev->mlock);
	if (indio_dev->currentmode == INDIO_RING_TRIGGERED)
		ret = lis3l02dq_read_accel_from_ring(dev, attr, buf);
	else
		ret =  lis3l02dq_read_16bit_signed(dev, attr, buf);
	mutex_unlock(&indio_dev->mlock);

	return ret;
}