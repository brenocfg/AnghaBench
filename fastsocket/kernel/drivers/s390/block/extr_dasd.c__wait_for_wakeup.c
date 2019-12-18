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
struct dasd_device {int /*<<< orphan*/  cdev; } ;
struct dasd_ccw_req {scalar_t__ callback_data; struct dasd_device* startdev; } ;

/* Variables and functions */
 scalar_t__ DASD_SLEEPON_END_TAG ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int _wait_for_wakeup(struct dasd_ccw_req *cqr)
{
	struct dasd_device *device;
	int rc;

	device = cqr->startdev;
	spin_lock_irq(get_ccwdev_lock(device->cdev));
	rc = (cqr->callback_data == DASD_SLEEPON_END_TAG);
	spin_unlock_irq(get_ccwdev_lock(device->cdev));
	return rc;
}