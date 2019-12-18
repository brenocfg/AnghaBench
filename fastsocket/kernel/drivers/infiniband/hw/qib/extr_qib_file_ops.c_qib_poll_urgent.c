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
struct qib_devdata {int /*<<< orphan*/  uctxt_lock; } ;
struct qib_ctxtdata {scalar_t__ urgent; scalar_t__ urgent_poll; int /*<<< orphan*/  flag; int /*<<< orphan*/  wait; struct qib_devdata* dd; } ;
struct poll_table_struct {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 unsigned int POLLIN ; 
 unsigned int POLLRDNORM ; 
 int /*<<< orphan*/  QIB_CTXT_WAITING_URG ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int qib_poll_urgent(struct qib_ctxtdata *rcd,
				    struct file *fp,
				    struct poll_table_struct *pt)
{
	struct qib_devdata *dd = rcd->dd;
	unsigned pollflag;

	poll_wait(fp, &rcd->wait, pt);

	spin_lock_irq(&dd->uctxt_lock);
	if (rcd->urgent != rcd->urgent_poll) {
		pollflag = POLLIN | POLLRDNORM;
		rcd->urgent_poll = rcd->urgent;
	} else {
		pollflag = 0;
		set_bit(QIB_CTXT_WAITING_URG, &rcd->flag);
	}
	spin_unlock_irq(&dd->uctxt_lock);

	return pollflag;
}