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
struct TYPE_2__ {int idle_notification; int disable_depth; int request_pending; int deferred_resume; int /*<<< orphan*/  wait_queue; int /*<<< orphan*/  suspend_timer; scalar_t__ timer_expires; int /*<<< orphan*/  work; int /*<<< orphan*/  request; int /*<<< orphan*/  child_count; scalar_t__ runtime_error; int /*<<< orphan*/  usage_count; int /*<<< orphan*/  runtime_status; int /*<<< orphan*/  lock; } ;
struct device {TYPE_1__ power; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPM_REQ_NONE ; 
 int /*<<< orphan*/  RPM_SUSPENDED ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_work ; 
 int /*<<< orphan*/  pm_suspend_ignore_children (struct device*,int) ; 
 int /*<<< orphan*/  pm_suspend_timer_fn ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void pm_runtime_init(struct device *dev)
{
	spin_lock_init(&dev->power.lock);

	dev->power.runtime_status = RPM_SUSPENDED;
	dev->power.idle_notification = false;

	dev->power.disable_depth = 1;
	atomic_set(&dev->power.usage_count, 0);

	dev->power.runtime_error = 0;

	atomic_set(&dev->power.child_count, 0);
	pm_suspend_ignore_children(dev, false);

	dev->power.request_pending = false;
	dev->power.request = RPM_REQ_NONE;
	dev->power.deferred_resume = false;
	INIT_WORK(&dev->power.work, pm_runtime_work);

	dev->power.timer_expires = 0;
	setup_timer(&dev->power.suspend_timer, pm_suspend_timer_fn,
			(unsigned long)dev);

	init_waitqueue_head(&dev->power.wait_queue);
}