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
struct iio_dev {int modes; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int INDIO_RING_TRIGGERED ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_device_unregister_eventset (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_unregister_id (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_unregister_sysfs (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_unregister_trigger_consumer (struct iio_dev*) ; 

void iio_device_unregister(struct iio_dev *dev_info)
{
	if (dev_info->modes & INDIO_RING_TRIGGERED)
		iio_device_unregister_trigger_consumer(dev_info);
	iio_device_unregister_eventset(dev_info);
	iio_device_unregister_sysfs(dev_info);
	iio_device_unregister_id(dev_info);
	device_unregister(&dev_info->dev);
}