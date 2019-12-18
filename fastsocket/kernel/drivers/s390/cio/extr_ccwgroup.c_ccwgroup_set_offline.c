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
struct ccwgroup_driver {int (* set_offline ) (struct ccwgroup_device*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;
struct ccwgroup_device {scalar_t__ state; int /*<<< orphan*/  onoff; TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ CCWGROUP_OFFLINE ; 
 int EAGAIN ; 
 int EINVAL ; 
 scalar_t__ atomic_cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (struct ccwgroup_device*) ; 
 struct ccwgroup_driver* to_ccwgroupdrv (int /*<<< orphan*/ ) ; 

int ccwgroup_set_offline(struct ccwgroup_device *gdev)
{
	struct ccwgroup_driver *gdrv;
	int ret;

	if (atomic_cmpxchg(&gdev->onoff, 0, 1) != 0)
		return -EAGAIN;
	if (gdev->state == CCWGROUP_OFFLINE) {
		ret = 0;
		goto out;
	}
	if (!gdev->dev.driver) {
		ret = -EINVAL;
		goto out;
	}
	gdrv = to_ccwgroupdrv (gdev->dev.driver);
	if ((ret = gdrv->set_offline ? gdrv->set_offline(gdev) : 0))
		goto out;

	gdev->state = CCWGROUP_OFFLINE;
 out:
	atomic_set(&gdev->onoff, 0);
	return ret;
}