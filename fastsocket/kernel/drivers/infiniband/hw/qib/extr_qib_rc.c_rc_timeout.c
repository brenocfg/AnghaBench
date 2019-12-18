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
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct qib_qp {int s_flags; int /*<<< orphan*/  r_lock; int /*<<< orphan*/  s_lock; scalar_t__ s_last_psn; int /*<<< orphan*/  s_timer; int /*<<< orphan*/  port_num; TYPE_1__ ibqp; } ;
struct qib_ibport {int /*<<< orphan*/  n_rc_timeouts; } ;

/* Variables and functions */
 int QIB_S_TIMER ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qib_restart_rc (struct qib_qp*,scalar_t__,int) ; 
 int /*<<< orphan*/  qib_schedule_send (struct qib_qp*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct qib_ibport* to_iport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rc_timeout(unsigned long arg)
{
	struct qib_qp *qp = (struct qib_qp *)arg;
	struct qib_ibport *ibp;
	unsigned long flags;

	spin_lock_irqsave(&qp->r_lock, flags);
	spin_lock(&qp->s_lock);
	if (qp->s_flags & QIB_S_TIMER) {
		ibp = to_iport(qp->ibqp.device, qp->port_num);
		ibp->n_rc_timeouts++;
		qp->s_flags &= ~QIB_S_TIMER;
		del_timer(&qp->s_timer);
		qib_restart_rc(qp, qp->s_last_psn + 1, 1);
		qib_schedule_send(qp);
	}
	spin_unlock(&qp->s_lock);
	spin_unlock_irqrestore(&qp->r_lock, flags);
}