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
struct usblp {int flags; int /*<<< orphan*/  wwait; int /*<<< orphan*/  mut; int /*<<< orphan*/  statusbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINTR ; 
 int ENOSPC ; 
 int LP_ABORT ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ schedule_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int usblp_check_status (struct usblp*,int) ; 
 int /*<<< orphan*/  usblp_read_status (struct usblp*,int /*<<< orphan*/ ) ; 
 int usblp_wtest (struct usblp*,int) ; 
 int /*<<< orphan*/  waita ; 

__attribute__((used)) static int usblp_wwait(struct usblp *usblp, int nonblock)
{
	DECLARE_WAITQUEUE(waita, current);
	int rc;
	int err = 0;

	add_wait_queue(&usblp->wwait, &waita);
	for (;;) {
		set_current_state(TASK_INTERRUPTIBLE);
		if (mutex_lock_interruptible(&usblp->mut)) {
			rc = -EINTR;
			break;
		}
		rc = usblp_wtest(usblp, nonblock);
		mutex_unlock(&usblp->mut);
		if (rc <= 0)
			break;

		if (schedule_timeout(msecs_to_jiffies(1500)) == 0) {
			if (usblp->flags & LP_ABORT) {
				err = usblp_check_status(usblp, err);
				if (err == 1) {	/* Paper out */
					rc = -ENOSPC;
					break;
				}
			} else {
				/* Prod the printer, Gentoo#251237. */
				mutex_lock(&usblp->mut);
				usblp_read_status(usblp, usblp->statusbuf);
				mutex_unlock(&usblp->mut);
			}
		}
	}
	set_current_state(TASK_RUNNING);
	remove_wait_queue(&usblp->wwait, &waita);
	return rc;
}