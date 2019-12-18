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
struct ipath_devdata {int ipath_flags; int /*<<< orphan*/  ipath_unit; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int IPATH_DISABLED ; 
 struct ipath_devdata* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int ipath_reset_device (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (char const*,char*,int) ; 

__attribute__((used)) static ssize_t store_reset(struct device *dev,
			 struct device_attribute *attr,
			  const char *buf,
			  size_t count)
{
	struct ipath_devdata *dd = dev_get_drvdata(dev);
	int ret;

	if (count < 5 || memcmp(buf, "reset", 5)) {
		ret = -EINVAL;
		goto bail;
	}

	if (dd->ipath_flags & IPATH_DISABLED) {
		/*
		 * post-reset init would re-enable interrupts, etc.
		 * so don't allow reset on disabled devices.  Not
		 * perfect error, but about the best choice.
		 */
		dev_info(dev,"Unit %d is disabled, can't reset\n",
			 dd->ipath_unit);
		ret = -EINVAL;
		goto bail;
	}
	ret = ipath_reset_device(dd->ipath_unit);
bail:
	return ret<0 ? ret : count;
}