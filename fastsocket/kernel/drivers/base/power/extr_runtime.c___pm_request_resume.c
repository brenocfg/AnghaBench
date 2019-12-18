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
struct TYPE_2__ {scalar_t__ runtime_status; scalar_t__ disable_depth; int request_pending; int /*<<< orphan*/  work; void* request; scalar_t__ runtime_error; } ;
struct device {TYPE_1__ power; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 scalar_t__ RPM_ACTIVE ; 
 void* RPM_REQ_NONE ; 
 void* RPM_REQ_RESUME ; 
 scalar_t__ RPM_RESUMING ; 
 int /*<<< orphan*/  pm_runtime_deactivate_timer (struct device*) ; 
 int /*<<< orphan*/  pm_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __pm_request_resume(struct device *dev)
{
	int retval = 0;

	if (dev->power.runtime_error)
		return -EINVAL;

	if (dev->power.runtime_status == RPM_ACTIVE)
		retval = 1;
	else if (dev->power.runtime_status == RPM_RESUMING)
		retval = -EINPROGRESS;
	else if (dev->power.disable_depth > 0)
		retval = -EAGAIN;
	if (retval < 0)
		return retval;

	pm_runtime_deactivate_timer(dev);

	if (dev->power.request_pending) {
		/* If non-resume request is pending, we can overtake it. */
		dev->power.request = retval ? RPM_REQ_NONE : RPM_REQ_RESUME;
		return retval;
	} else if (retval) {
		return retval;
	}

	dev->power.request = RPM_REQ_RESUME;
	dev->power.request_pending = true;
	queue_work(pm_wq, &dev->power.work);

	return retval;
}