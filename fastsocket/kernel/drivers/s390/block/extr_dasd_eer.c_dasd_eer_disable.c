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
struct dasd_device {int /*<<< orphan*/  cdev; int /*<<< orphan*/  flags; struct dasd_ccw_req* eer_cqr; } ;
struct dasd_ccw_req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_FLAG_EER_IN_USE ; 
 int /*<<< orphan*/  DASD_FLAG_EER_SNSS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dasd_kfree_request (struct dasd_ccw_req*,struct dasd_device*) ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void dasd_eer_disable(struct dasd_device *device)
{
	struct dasd_ccw_req *cqr;
	unsigned long flags;
	int in_use;

	if (!device->eer_cqr)
		return;
	spin_lock_irqsave(get_ccwdev_lock(device->cdev), flags);
	cqr = device->eer_cqr;
	device->eer_cqr = NULL;
	clear_bit(DASD_FLAG_EER_SNSS, &device->flags);
	in_use = test_and_clear_bit(DASD_FLAG_EER_IN_USE, &device->flags);
	spin_unlock_irqrestore(get_ccwdev_lock(device->cdev), flags);
	if (cqr && !in_use)
		dasd_kfree_request(cqr, device);
}