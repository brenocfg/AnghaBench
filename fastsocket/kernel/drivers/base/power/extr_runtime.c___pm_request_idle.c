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
struct TYPE_2__ {scalar_t__ disable_depth; scalar_t__ runtime_status; int request_pending; scalar_t__ request; int /*<<< orphan*/  work; int /*<<< orphan*/  usage_count; scalar_t__ runtime_error; } ;
struct device {TYPE_1__ power; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ RPM_REQ_IDLE ; 
 scalar_t__ RPM_REQ_NONE ; 
 scalar_t__ RPM_SUSPENDED ; 
 scalar_t__ RPM_SUSPENDING ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_children_suspended (struct device*) ; 
 int /*<<< orphan*/  pm_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __pm_request_idle(struct device *dev)
{
	int retval = 0;

	if (dev->power.runtime_error)
		retval = -EINVAL;
	else if (atomic_read(&dev->power.usage_count) > 0
	    || dev->power.disable_depth > 0
	    || dev->power.runtime_status == RPM_SUSPENDED
	    || dev->power.runtime_status == RPM_SUSPENDING)
		retval = -EAGAIN;
	else if (!pm_children_suspended(dev))
		retval = -EBUSY;
	if (retval)
		return retval;

	if (dev->power.request_pending) {
		/* Any requests other then RPM_REQ_IDLE take precedence. */
		if (dev->power.request == RPM_REQ_NONE)
			dev->power.request = RPM_REQ_IDLE;
		else if (dev->power.request != RPM_REQ_IDLE)
			retval = -EAGAIN;
		return retval;
	}

	dev->power.request = RPM_REQ_IDLE;
	dev->power.request_pending = true;
	queue_work(pm_wq, &dev->power.work);

	return retval;
}