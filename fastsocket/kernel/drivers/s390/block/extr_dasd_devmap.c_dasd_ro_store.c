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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct dasd_devmap {int /*<<< orphan*/  features; struct dasd_device* device; } ;
struct dasd_device {TYPE_1__* block; int /*<<< orphan*/  flags; int /*<<< orphan*/  features; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {scalar_t__ gdp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_FEATURE_READONLY ; 
 int /*<<< orphan*/  DASD_FLAG_DEVICE_RO ; 
 size_t EINVAL ; 
 scalar_t__ IS_ERR (struct dasd_devmap*) ; 
 size_t PTR_ERR (struct dasd_devmap*) ; 
 struct dasd_devmap* dasd_devmap_from_cdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_devmap_lock ; 
 int /*<<< orphan*/  set_disk_ro (scalar_t__,int) ; 
 int simple_strtoul (char const*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_ccwdev (struct device*) ; 

__attribute__((used)) static ssize_t
dasd_ro_store(struct device *dev, struct device_attribute *attr,
	      const char *buf, size_t count)
{
	struct dasd_devmap *devmap;
	struct dasd_device *device;
	int val;
	char *endp;

	devmap = dasd_devmap_from_cdev(to_ccwdev(dev));
	if (IS_ERR(devmap))
		return PTR_ERR(devmap);

	val = simple_strtoul(buf, &endp, 0);
	if (((endp + 1) < (buf + count)) || (val > 1))
		return -EINVAL;

	spin_lock(&dasd_devmap_lock);
	if (val)
		devmap->features |= DASD_FEATURE_READONLY;
	else
		devmap->features &= ~DASD_FEATURE_READONLY;
	device = devmap->device;
	if (device) {
		device->features = devmap->features;
		val = val || test_bit(DASD_FLAG_DEVICE_RO, &device->flags);
	}
	spin_unlock(&dasd_devmap_lock);
	if (device && device->block && device->block->gdp)
		set_disk_ro(device->block->gdp, val);
	return count;
}