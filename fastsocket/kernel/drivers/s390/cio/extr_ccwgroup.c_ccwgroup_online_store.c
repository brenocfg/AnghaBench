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
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  driver; } ;
struct ccwgroup_driver {int /*<<< orphan*/  owner; } ;
struct ccwgroup_device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t ENODEV ; 
 int ccwgroup_set_offline (struct ccwgroup_device*) ; 
 int ccwgroup_set_online (struct ccwgroup_device*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int strict_strtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 struct ccwgroup_device* to_ccwgroupdev (struct device*) ; 
 struct ccwgroup_driver* to_ccwgroupdrv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
ccwgroup_online_store (struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	struct ccwgroup_device *gdev;
	struct ccwgroup_driver *gdrv;
	unsigned long value;
	int ret;

	if (!dev->driver)
		return -ENODEV;

	gdev = to_ccwgroupdev(dev);
	gdrv = to_ccwgroupdrv(dev->driver);

	if (!try_module_get(gdrv->owner))
		return -EINVAL;

	ret = strict_strtoul(buf, 0, &value);
	if (ret)
		goto out;

	if (value == 1)
		ret = ccwgroup_set_online(gdev);
	else if (value == 0)
		ret = ccwgroup_set_offline(gdev);
	else
		ret = -EINVAL;
out:
	module_put(gdrv->owner);
	return (ret == 0) ? count : ret;
}