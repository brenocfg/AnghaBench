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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct iio_dev {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  iio_trigger_consumer_attr_group ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int iio_device_register_trigger_consumer(struct iio_dev *dev_info)
{
	int ret;
	ret = sysfs_create_group(&dev_info->dev.kobj,
				 &iio_trigger_consumer_attr_group);
	return ret;
}