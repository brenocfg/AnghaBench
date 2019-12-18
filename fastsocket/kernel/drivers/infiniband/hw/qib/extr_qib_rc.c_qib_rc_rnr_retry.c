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
struct qib_qp {int s_flags; int /*<<< orphan*/  s_lock; int /*<<< orphan*/  s_timer; } ;

/* Variables and functions */
 int QIB_S_WAIT_RNR ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qib_schedule_send (struct qib_qp*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void qib_rc_rnr_retry(unsigned long arg)
{
	struct qib_qp *qp = (struct qib_qp *)arg;
	unsigned long flags;

	spin_lock_irqsave(&qp->s_lock, flags);
	if (qp->s_flags & QIB_S_WAIT_RNR) {
		qp->s_flags &= ~QIB_S_WAIT_RNR;
		del_timer(&qp->s_timer);
		qib_schedule_send(qp);
	}
	spin_unlock_irqrestore(&qp->s_lock, flags);
}