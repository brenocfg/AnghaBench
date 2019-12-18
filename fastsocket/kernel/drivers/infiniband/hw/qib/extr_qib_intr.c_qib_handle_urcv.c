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
typedef  unsigned long long u64 ;
struct qib_devdata {int first_user_ctxt; int cfgctxts; int /*<<< orphan*/  uctxt_lock; int /*<<< orphan*/  (* f_rcvctrl ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;struct qib_ctxtdata** rcd; } ;
struct qib_ctxtdata {int /*<<< orphan*/  wait; int /*<<< orphan*/  urgent; int /*<<< orphan*/  flag; int /*<<< orphan*/  ctxt; int /*<<< orphan*/  ppd; int /*<<< orphan*/  cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  QIB_CTXT_WAITING_RCV ; 
 int /*<<< orphan*/  QIB_CTXT_WAITING_URG ; 
 int /*<<< orphan*/  QIB_RCVCTRL_INTRAVAIL_DIS ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void qib_handle_urcv(struct qib_devdata *dd, u64 ctxtr)
{
	struct qib_ctxtdata *rcd;
	unsigned long flags;
	int i;

	spin_lock_irqsave(&dd->uctxt_lock, flags);
	for (i = dd->first_user_ctxt; dd->rcd && i < dd->cfgctxts; i++) {
		if (!(ctxtr & (1ULL << i)))
			continue;
		rcd = dd->rcd[i];
		if (!rcd || !rcd->cnt)
			continue;

		if (test_and_clear_bit(QIB_CTXT_WAITING_RCV, &rcd->flag)) {
			wake_up_interruptible(&rcd->wait);
			dd->f_rcvctrl(rcd->ppd, QIB_RCVCTRL_INTRAVAIL_DIS,
				      rcd->ctxt);
		} else if (test_and_clear_bit(QIB_CTXT_WAITING_URG,
					      &rcd->flag)) {
			rcd->urgent++;
			wake_up_interruptible(&rcd->wait);
		}
	}
	spin_unlock_irqrestore(&dd->uctxt_lock, flags);
}