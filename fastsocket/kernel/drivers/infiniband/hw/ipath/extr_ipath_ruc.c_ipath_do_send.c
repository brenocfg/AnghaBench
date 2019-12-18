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
struct TYPE_6__ {scalar_t__ qp_type; int /*<<< orphan*/  device; } ;
struct TYPE_4__ {scalar_t__ dlid; } ;
struct ipath_qp {int s_flags; size_t state; scalar_t__ s_hdrwords; int /*<<< orphan*/  s_cur_size; int /*<<< orphan*/  s_cur_sge; int /*<<< orphan*/  s_hdr; int /*<<< orphan*/  s_lock; TYPE_3__ ibqp; TYPE_1__ remote_ah_attr; } ;
struct ipath_ibdev {int /*<<< orphan*/  n_unicast_xmit; TYPE_2__* dd; } ;
struct TYPE_5__ {scalar_t__ ipath_lid; } ;

/* Variables and functions */
 scalar_t__ IB_QPT_RC ; 
 scalar_t__ IB_QPT_UC ; 
 int IPATH_PROCESS_OR_FLUSH_SEND ; 
 int IPATH_S_ANY_WAIT ; 
 int IPATH_S_BUSY ; 
 int* ib_ipath_state_ops ; 
 int ipath_make_rc_req (struct ipath_qp*) ; 
 int ipath_make_uc_req (struct ipath_qp*) ; 
 int ipath_make_ud_req (struct ipath_qp*) ; 
 scalar_t__ ipath_no_bufs_available (struct ipath_qp*,struct ipath_ibdev*) ; 
 int /*<<< orphan*/  ipath_ruc_loopback (struct ipath_qp*) ; 
 scalar_t__ ipath_verbs_send (struct ipath_qp*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct ipath_ibdev* to_idev (int /*<<< orphan*/ ) ; 

void ipath_do_send(unsigned long data)
{
	struct ipath_qp *qp = (struct ipath_qp *)data;
	struct ipath_ibdev *dev = to_idev(qp->ibqp.device);
	int (*make_req)(struct ipath_qp *qp);
	unsigned long flags;

	if ((qp->ibqp.qp_type == IB_QPT_RC ||
	     qp->ibqp.qp_type == IB_QPT_UC) &&
	    qp->remote_ah_attr.dlid == dev->dd->ipath_lid) {
		ipath_ruc_loopback(qp);
		goto bail;
	}

	if (qp->ibqp.qp_type == IB_QPT_RC)
	       make_req = ipath_make_rc_req;
	else if (qp->ibqp.qp_type == IB_QPT_UC)
	       make_req = ipath_make_uc_req;
	else
	       make_req = ipath_make_ud_req;

	spin_lock_irqsave(&qp->s_lock, flags);

	/* Return if we are already busy processing a work request. */
	if ((qp->s_flags & (IPATH_S_BUSY | IPATH_S_ANY_WAIT)) ||
	    !(ib_ipath_state_ops[qp->state] & IPATH_PROCESS_OR_FLUSH_SEND)) {
		spin_unlock_irqrestore(&qp->s_lock, flags);
		goto bail;
	}

	qp->s_flags |= IPATH_S_BUSY;

	spin_unlock_irqrestore(&qp->s_lock, flags);

again:
	/* Check for a constructed packet to be sent. */
	if (qp->s_hdrwords != 0) {
		/*
		 * If no PIO bufs are available, return.  An interrupt will
		 * call ipath_ib_piobufavail() when one is available.
		 */
		if (ipath_verbs_send(qp, &qp->s_hdr, qp->s_hdrwords,
				     qp->s_cur_sge, qp->s_cur_size)) {
			if (ipath_no_bufs_available(qp, dev))
				goto bail;
		}
		dev->n_unicast_xmit++;
		/* Record that we sent the packet and s_hdr is empty. */
		qp->s_hdrwords = 0;
	}

	if (make_req(qp))
		goto again;

bail:;
}