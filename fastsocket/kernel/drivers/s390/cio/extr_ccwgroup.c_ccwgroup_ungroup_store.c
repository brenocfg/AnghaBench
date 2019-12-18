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
struct ccwgroup_device {scalar_t__ state; int /*<<< orphan*/  onoff; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ CCWGROUP_OFFLINE ; 
 int EAGAIN ; 
 int EINVAL ; 
 scalar_t__ atomic_cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccwgroup_ungroup_callback ; 
 int device_schedule_callback (struct device*,int /*<<< orphan*/ ) ; 
 struct ccwgroup_device* to_ccwgroupdev (struct device*) ; 

__attribute__((used)) static ssize_t
ccwgroup_ungroup_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	struct ccwgroup_device *gdev;
	int rc;

	gdev = to_ccwgroupdev(dev);

	/* Prevent concurrent online/offline processing and ungrouping. */
	if (atomic_cmpxchg(&gdev->onoff, 0, 1) != 0)
		return -EAGAIN;
	if (gdev->state != CCWGROUP_OFFLINE) {
		rc = -EINVAL;
		goto out;
	}
	/* Note that we cannot unregister the device from one of its
	 * attribute methods, so we have to use this roundabout approach.
	 */
	rc = device_schedule_callback(dev, ccwgroup_ungroup_callback);
out:
	if (rc) {
		if (rc != -EAGAIN)
			/* Release onoff "lock" when ungrouping failed. */
			atomic_set(&gdev->onoff, 0);
		return rc;
	}
	return count;
}