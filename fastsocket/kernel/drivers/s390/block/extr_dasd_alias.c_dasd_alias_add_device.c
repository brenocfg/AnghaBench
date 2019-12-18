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
struct dasd_eckd_private {struct alias_lcu* lcu; } ;
struct dasd_device {int /*<<< orphan*/  cdev; int /*<<< orphan*/  alias_list; scalar_t__ private; } ;
struct alias_lcu {int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  active_devices; } ;

/* Variables and functions */
 int UPDATE_PENDING ; 
 int _add_device_to_lcu (struct alias_lcu*,struct dasd_device*,struct dasd_device*) ; 
 int /*<<< orphan*/  _schedule_lcu_update (struct alias_lcu*,struct dasd_device*) ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

int dasd_alias_add_device(struct dasd_device *device)
{
	struct dasd_eckd_private *private;
	struct alias_lcu *lcu;
	unsigned long flags;
	int rc;

	private = (struct dasd_eckd_private *) device->private;
	lcu = private->lcu;
	rc = 0;

	/* need to take cdev lock before lcu lock */
	spin_lock_irqsave(get_ccwdev_lock(device->cdev), flags);
	spin_lock(&lcu->lock);
	if (!(lcu->flags & UPDATE_PENDING)) {
		rc = _add_device_to_lcu(lcu, device, device);
		if (rc)
			lcu->flags |= UPDATE_PENDING;
	}
	if (lcu->flags & UPDATE_PENDING) {
		list_move(&device->alias_list, &lcu->active_devices);
		_schedule_lcu_update(lcu, device);
	}
	spin_unlock(&lcu->lock);
	spin_unlock_irqrestore(get_ccwdev_lock(device->cdev), flags);
	return rc;
}