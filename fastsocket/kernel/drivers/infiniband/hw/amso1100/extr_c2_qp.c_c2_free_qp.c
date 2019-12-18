#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  shared; int /*<<< orphan*/  peer; } ;
struct TYPE_5__ {int /*<<< orphan*/  shared; int /*<<< orphan*/  peer; } ;
struct TYPE_4__ {int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; } ;
struct c2_qp {int /*<<< orphan*/  refcount; int /*<<< orphan*/  wait; TYPE_3__ rq_mq; TYPE_2__ sq_mq; int /*<<< orphan*/  qpn; TYPE_1__ ibqp; } ;
struct c2_dev {int dummy; } ;
struct c2_cq {int /*<<< orphan*/  cqn; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c2_cq_clean (struct c2_dev*,struct c2_qp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c2_free_mqsp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c2_free_qpn (struct c2_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c2_lock_cqs (struct c2_cq*,struct c2_cq*) ; 
 int /*<<< orphan*/  c2_unlock_cqs (struct c2_cq*,struct c2_cq*) ; 
 int /*<<< orphan*/  destroy_qp (struct c2_dev*,struct c2_qp*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct c2_cq* to_c2cq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void c2_free_qp(struct c2_dev *c2dev, struct c2_qp *qp)
{
	struct c2_cq *send_cq;
	struct c2_cq *recv_cq;

	send_cq = to_c2cq(qp->ibqp.send_cq);
	recv_cq = to_c2cq(qp->ibqp.recv_cq);

	/*
	 * Lock CQs here, so that CQ polling code can do QP lookup
	 * without taking a lock.
	 */
	c2_lock_cqs(send_cq, recv_cq);
	c2_free_qpn(c2dev, qp->qpn);
	c2_unlock_cqs(send_cq, recv_cq);

	/*
	 * Destroy qp in the rnic...
	 */
	destroy_qp(c2dev, qp);

	/*
	 * Mark any unreaped CQEs as null and void.
	 */
	c2_cq_clean(c2dev, qp, send_cq->cqn);
	if (send_cq != recv_cq)
		c2_cq_clean(c2dev, qp, recv_cq->cqn);
	/*
	 * Unmap the MQs and return the shared pointers
	 * to the message pool.
	 */
	iounmap(qp->sq_mq.peer);
	iounmap(qp->rq_mq.peer);
	c2_free_mqsp(qp->sq_mq.shared);
	c2_free_mqsp(qp->rq_mq.shared);

	atomic_dec(&qp->refcount);
	wait_event(qp->wait, !atomic_read(&qp->refcount));
}