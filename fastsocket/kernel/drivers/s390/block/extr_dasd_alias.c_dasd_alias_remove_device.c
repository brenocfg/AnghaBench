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
struct dasd_device {scalar_t__ private; } ;
struct alias_lcu {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  _remove_device_from_lcu (struct alias_lcu*,struct dasd_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int dasd_alias_remove_device(struct dasd_device *device)
{
	struct dasd_eckd_private *private;
	struct alias_lcu *lcu;
	unsigned long flags;

	private = (struct dasd_eckd_private *) device->private;
	lcu = private->lcu;
	/* nothing to do if already removed */
	if (!lcu)
		return 0;
	spin_lock_irqsave(&lcu->lock, flags);
	_remove_device_from_lcu(lcu, device);
	spin_unlock_irqrestore(&lcu->lock, flags);
	return 0;
}