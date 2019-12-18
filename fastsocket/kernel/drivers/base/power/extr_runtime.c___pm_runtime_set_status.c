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
struct TYPE_2__ {unsigned int runtime_status; int /*<<< orphan*/  lock; scalar_t__ runtime_error; int /*<<< orphan*/  child_count; int /*<<< orphan*/  ignore_children; int /*<<< orphan*/  disable_depth; } ;
struct device {TYPE_1__ power; struct device* parent; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int EINVAL ; 
 unsigned int RPM_ACTIVE ; 
 unsigned int RPM_SUSPENDED ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int /*<<< orphan*/  atomic_add_unless (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_request_idle (struct device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int __pm_runtime_set_status(struct device *dev, unsigned int status)
{
	struct device *parent = dev->parent;
	unsigned long flags;
	bool notify_parent = false;
	int error = 0;

	if (status != RPM_ACTIVE && status != RPM_SUSPENDED)
		return -EINVAL;

	spin_lock_irqsave(&dev->power.lock, flags);

	if (!dev->power.runtime_error && !dev->power.disable_depth) {
		error = -EAGAIN;
		goto out;
	}

	if (dev->power.runtime_status == status)
		goto out_set;

	if (status == RPM_SUSPENDED) {
		/* It always is possible to set the status to 'suspended'. */
		if (parent) {
			atomic_add_unless(&parent->power.child_count, -1, 0);
			notify_parent = !parent->power.ignore_children;
		}
		goto out_set;
	}

	if (parent) {
		spin_lock_nested(&parent->power.lock, SINGLE_DEPTH_NESTING);

		/*
		 * It is invalid to put an active child under a parent that is
		 * not active, has run-time PM enabled and the
		 * 'power.ignore_children' flag unset.
		 */
		if (!parent->power.disable_depth
		    && !parent->power.ignore_children
		    && parent->power.runtime_status != RPM_ACTIVE) {
			error = -EBUSY;
		} else {
			if (dev->power.runtime_status == RPM_SUSPENDED)
				atomic_inc(&parent->power.child_count);
		}

		spin_unlock(&parent->power.lock);

		if (error)
			goto out;
	}

 out_set:
	dev->power.runtime_status = status;
	dev->power.runtime_error = 0;
 out:
	spin_unlock_irqrestore(&dev->power.lock, flags);

	if (notify_parent)
		pm_request_idle(parent);

	return error;
}