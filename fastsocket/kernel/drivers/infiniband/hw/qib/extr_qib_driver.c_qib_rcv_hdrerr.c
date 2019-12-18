#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_8__ {int qp_type; } ;
struct qib_qp {size_t state; int /*<<< orphan*/  wait; int /*<<< orphan*/  refcount; int /*<<< orphan*/  r_lock; int /*<<< orphan*/  rspwait; int /*<<< orphan*/  r_flags; int /*<<< orphan*/  r_psn; int /*<<< orphan*/  r_ack_psn; int /*<<< orphan*/  r_nak_state; TYPE_4__ ibqp; } ;
struct qib_ibport {int /*<<< orphan*/  n_rc_seqnak; int /*<<< orphan*/  n_pkt_drops; } ;
struct qib_pportdata {int lmc; int lid; struct qib_ibport ibport_data; } ;
struct qib_other_headers {int /*<<< orphan*/ * bth; } ;
struct qib_message_header {int dummy; } ;
struct TYPE_5__ {scalar_t__ next_hdr; int /*<<< orphan*/  version_tclass_flow; } ;
struct TYPE_6__ {TYPE_1__ grh; struct qib_other_headers oth; } ;
struct TYPE_7__ {TYPE_2__ l; struct qib_other_headers oth; } ;
struct qib_ib_header {TYPE_3__ u; int /*<<< orphan*/ * lrh; } ;
struct qib_ctxtdata {int /*<<< orphan*/  qp_wait_list; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 scalar_t__ IB_GRH_NEXT_HDR ; 
 int IB_GRH_VERSION ; 
 int IB_GRH_VERSION_SHIFT ; 
 int /*<<< orphan*/  IB_NAK_PSN_ERROR ; 
 int IB_OPCODE_RC_RDMA_READ_RESPONSE_FIRST ; 
#define  IB_QPT_GSI 132 
#define  IB_QPT_RC 131 
#define  IB_QPT_SMI 130 
#define  IB_QPT_UC 129 
#define  IB_QPT_UD 128 
 int QIB_LRH_BTH ; 
 int QIB_LRH_GRH ; 
 int QIB_MULTICAST_LID_BASE ; 
 int QIB_MULTICAST_QPN ; 
 int QIB_PROCESS_RECV_OK ; 
 int QIB_QPN_MASK ; 
 int /*<<< orphan*/  QIB_R_RSP_NAK ; 
 int QLOGIC_IB_RHF_H_ICRCERR ; 
 int QLOGIC_IB_RHF_H_TIDERR ; 
 int QLOGIC_IB_RHF_H_VCRCERR ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int* ib_qib_state_ops ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int qib_cmp24 (int,int /*<<< orphan*/ ) ; 
 int qib_hdrget_length_in_bytes (int /*<<< orphan*/ *) ; 
 struct qib_qp* qib_lookup_qpn (struct qib_ibport*,int) ; 
 int qib_ruc_check_hdr (struct qib_ibport*,struct qib_ib_header*,int,struct qib_qp*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 qib_rcv_hdrerr(struct qib_ctxtdata *rcd, struct qib_pportdata *ppd,
			  u32 ctxt, u32 eflags, u32 l, u32 etail,
			  __le32 *rhf_addr, struct qib_message_header *rhdr)
{
	u32 ret = 0;

	if (eflags & (QLOGIC_IB_RHF_H_ICRCERR | QLOGIC_IB_RHF_H_VCRCERR))
		ret = 1;
	else if (eflags == QLOGIC_IB_RHF_H_TIDERR) {
		/* For TIDERR and RC QPs premptively schedule a NAK */
		struct qib_ib_header *hdr = (struct qib_ib_header *) rhdr;
		struct qib_other_headers *ohdr = NULL;
		struct qib_ibport *ibp = &ppd->ibport_data;
		struct qib_qp *qp = NULL;
		u32 tlen = qib_hdrget_length_in_bytes(rhf_addr);
		u16 lid  = be16_to_cpu(hdr->lrh[1]);
		int lnh = be16_to_cpu(hdr->lrh[0]) & 3;
		u32 qp_num;
		u32 opcode;
		u32 psn;
		int diff;

		/* Sanity check packet */
		if (tlen < 24)
			goto drop;

		if (lid < QIB_MULTICAST_LID_BASE) {
			lid &= ~((1 << ppd->lmc) - 1);
			if (unlikely(lid != ppd->lid))
				goto drop;
		}

		/* Check for GRH */
		if (lnh == QIB_LRH_BTH)
			ohdr = &hdr->u.oth;
		else if (lnh == QIB_LRH_GRH) {
			u32 vtf;

			ohdr = &hdr->u.l.oth;
			if (hdr->u.l.grh.next_hdr != IB_GRH_NEXT_HDR)
				goto drop;
			vtf = be32_to_cpu(hdr->u.l.grh.version_tclass_flow);
			if ((vtf >> IB_GRH_VERSION_SHIFT) != IB_GRH_VERSION)
				goto drop;
		} else
			goto drop;

		/* Get opcode and PSN from packet */
		opcode = be32_to_cpu(ohdr->bth[0]);
		opcode >>= 24;
		psn = be32_to_cpu(ohdr->bth[2]);

		/* Get the destination QP number. */
		qp_num = be32_to_cpu(ohdr->bth[1]) & QIB_QPN_MASK;
		if (qp_num != QIB_MULTICAST_QPN) {
			int ruc_res;
			qp = qib_lookup_qpn(ibp, qp_num);
			if (!qp)
				goto drop;

			/*
			 * Handle only RC QPs - for other QP types drop error
			 * packet.
			 */
			spin_lock(&qp->r_lock);

			/* Check for valid receive state. */
			if (!(ib_qib_state_ops[qp->state] &
			      QIB_PROCESS_RECV_OK)) {
				ibp->n_pkt_drops++;
				goto unlock;
			}

			switch (qp->ibqp.qp_type) {
			case IB_QPT_RC:
				ruc_res =
					qib_ruc_check_hdr(
						ibp, hdr,
						lnh == QIB_LRH_GRH,
						qp,
						be32_to_cpu(ohdr->bth[0]));
				if (ruc_res)
					goto unlock;

				/* Only deal with RDMA Writes for now */
				if (opcode <
				    IB_OPCODE_RC_RDMA_READ_RESPONSE_FIRST) {
					diff = qib_cmp24(psn, qp->r_psn);
					if (!qp->r_nak_state && diff >= 0) {
						ibp->n_rc_seqnak++;
						qp->r_nak_state =
							IB_NAK_PSN_ERROR;
						/* Use the expected PSN. */
						qp->r_ack_psn = qp->r_psn;
						/*
						 * Wait to send the sequence
						 * NAK until all packets
						 * in the receive queue have
						 * been processed.
						 * Otherwise, we end up
						 * propagating congestion.
						 */
						if (list_empty(&qp->rspwait)) {
							qp->r_flags |=
								QIB_R_RSP_NAK;
							atomic_inc(
								&qp->refcount);
							list_add_tail(
							 &qp->rspwait,
							 &rcd->qp_wait_list);
						}
					} /* Out of sequence NAK */
				} /* QP Request NAKs */
				break;
			case IB_QPT_SMI:
			case IB_QPT_GSI:
			case IB_QPT_UD:
			case IB_QPT_UC:
			default:
				/* For now don't handle any other QP types */
				break;
			}

unlock:
			spin_unlock(&qp->r_lock);
			/*
			 * Notify qib_destroy_qp() if it is waiting
			 * for us to finish.
			 */
			if (atomic_dec_and_test(&qp->refcount))
				wake_up(&qp->wait);
		} /* Unicast QP */
	} /* Valid packet with TIDErr */

drop:
	return ret;
}