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
struct raw3270_request {int dummy; } ;
struct raw3270 {int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int raw3270_halt_io_nolock (struct raw3270*,struct raw3270_request*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int
raw3270_halt_io(struct raw3270 *rp, struct raw3270_request *rq)
{
	unsigned long flags;
	int rc;

	spin_lock_irqsave(get_ccwdev_lock(rp->cdev), flags);
	rc = raw3270_halt_io_nolock(rp, rq);
	spin_unlock_irqrestore(get_ccwdev_lock(rp->cdev), flags);
	return rc;
}