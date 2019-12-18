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
struct device {int dummy; } ;
struct dasd_device {int /*<<< orphan*/  flags; } ;
struct ccw_device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_FLAG_OFFLINE ; 
 int /*<<< orphan*/  DASD_FLAG_SAFE_OFFLINE ; 
 int /*<<< orphan*/  DASD_FLAG_SAFE_OFFLINE_RUNNING ; 
 int EBUSY ; 
 scalar_t__ IS_ERR (struct dasd_device*) ; 
 int PTR_ERR (struct dasd_device*) ; 
 int ccw_device_set_offline (struct ccw_device*) ; 
 struct dasd_device* dasd_device_from_cdev (struct ccw_device*) ; 
 int /*<<< orphan*/  dasd_put_device (struct dasd_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ccw_device* to_ccwdev (struct device*) ; 

__attribute__((used)) static ssize_t
dasd_safe_offline_store(struct device *dev, struct device_attribute *attr,
			const char *buf, size_t count)
{
	struct ccw_device *cdev = to_ccwdev(dev);
	struct dasd_device *device;
	int rc;

	device = dasd_device_from_cdev(cdev);
	if (IS_ERR(device)) {
		rc = PTR_ERR(device);
		goto out;
	}

	if (test_bit(DASD_FLAG_OFFLINE, &device->flags) ||
	    test_bit(DASD_FLAG_SAFE_OFFLINE_RUNNING, &device->flags)) {
		/* Already doing offline processing */
		dasd_put_device(device);
		rc = -EBUSY;
		goto out;
	}

	set_bit(DASD_FLAG_SAFE_OFFLINE, &device->flags);
	dasd_put_device(device);

	rc = ccw_device_set_offline(cdev);

out:
	return rc ? rc : count;
}