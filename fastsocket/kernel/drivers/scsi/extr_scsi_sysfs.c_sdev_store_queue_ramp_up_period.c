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
struct scsi_device {int /*<<< orphan*/  queue_ramp_up_period; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  unsigned long ssize_t ;

/* Variables and functions */
 unsigned long EINVAL ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned long) ; 
 scalar_t__ strict_strtoul (char const*,int,unsigned long*) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static ssize_t
sdev_store_queue_ramp_up_period(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t count)
{
	struct scsi_device *sdev = to_scsi_device(dev);
	unsigned long period;

	if (strict_strtoul(buf, 10, &period))
		return -EINVAL;

	sdev->queue_ramp_up_period = msecs_to_jiffies(period);
	return period;
}