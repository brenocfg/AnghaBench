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
struct yealink_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t ENODEV ; 
 struct yealink_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_rwsema ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yealink_set_ringtone (struct yealink_dev*,char*,size_t) ; 

__attribute__((used)) static ssize_t store_ringtone(struct device *dev,
		struct device_attribute *attr,
		const char *buf, size_t count)
{
	struct yealink_dev *yld;

	down_write(&sysfs_rwsema);
	yld = dev_get_drvdata(dev);
	if (yld == NULL) {
		up_write(&sysfs_rwsema);
		return -ENODEV;
	}

	/* TODO locking with async usb control interface??? */
	yealink_set_ringtone(yld, (char *)buf, count);
	up_write(&sysfs_rwsema);
	return count;
}