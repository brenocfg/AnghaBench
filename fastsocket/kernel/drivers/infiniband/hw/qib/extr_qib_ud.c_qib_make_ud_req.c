#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_24__ {int remote_qpn; int remote_qkey; int /*<<< orphan*/  pkey_index; int /*<<< orphan*/  ah; } ;
struct TYPE_13__ {TYPE_9__ ud; } ;
struct TYPE_19__ {int /*<<< orphan*/  imm_data; } ;
struct TYPE_14__ {scalar_t__ opcode; int send_flags; TYPE_10__ wr; TYPE_4__ ex; int /*<<< orphan*/  num_sge; } ;
struct qib_swqe {int length; TYPE_11__ wr; int /*<<< orphan*/ * sg_list; } ;
struct TYPE_23__ {scalar_t__ qp_type; int qp_num; int /*<<< orphan*/  device; } ;
struct TYPE_16__ {int total_len; int /*<<< orphan*/  num_sge; int /*<<< orphan*/ * sg_list; int /*<<< orphan*/  sge; } ;
struct qib_qp {size_t state; scalar_t__ s_last; scalar_t__ s_head; int s_cur; int s_size; int s_hdrwords; int s_cur_size; int qkey; int /*<<< orphan*/  s_lock; int /*<<< orphan*/  s_flags; TYPE_8__ ibqp; int /*<<< orphan*/  s_next_psn; int /*<<< orphan*/  s_pkey_index; TYPE_5__* s_hdr; TYPE_1__ s_sge; struct qib_swqe* s_wqe; int /*<<< orphan*/  s_srate; TYPE_1__* s_cur_sge; int /*<<< orphan*/  s_dma_busy; int /*<<< orphan*/  port_num; } ;
struct qib_pportdata {int lmc; int lid; } ;
struct TYPE_21__ {void** deth; int /*<<< orphan*/  imm_data; } ;
struct TYPE_22__ {TYPE_6__ ud; } ;
struct qib_other_headers {TYPE_7__ u; void** bth; } ;
struct qib_ibport {int* sl_to_vl; int /*<<< orphan*/  n_unicast_xmit; int /*<<< orphan*/  n_multicast_xmit; } ;
struct ib_ah_attr {int dlid; int ah_flags; int sl; int src_path_bits; int /*<<< orphan*/  grh; int /*<<< orphan*/  static_rate; } ;
struct TYPE_17__ {struct qib_other_headers oth; int /*<<< orphan*/  grh; } ;
struct TYPE_18__ {struct qib_other_headers oth; TYPE_2__ l; } ;
struct TYPE_20__ {void** lrh; TYPE_3__ u; } ;
struct TYPE_15__ {struct ib_ah_attr attr; } ;

/* Variables and functions */
 int IB_AH_GRH ; 
 int IB_BTH_SOLICITED ; 
 void* IB_LID_PERMISSIVE ; 
 int IB_OPCODE_UD_SEND_ONLY ; 
 int IB_OPCODE_UD_SEND_ONLY_WITH_IMMEDIATE ; 
 scalar_t__ IB_QPT_GSI ; 
 scalar_t__ IB_QPT_SMI ; 
 int IB_SEND_SOLICITED ; 
 int /*<<< orphan*/  IB_WC_SUCCESS ; 
 int /*<<< orphan*/  IB_WC_WR_FLUSH_ERR ; 
 scalar_t__ IB_WR_SEND_WITH_IMM ; 
 int QIB_DEFAULT_P_KEY ; 
 int QIB_FLUSH_SEND ; 
 int QIB_LRH_BTH ; 
 int QIB_LRH_GRH ; 
 int QIB_MULTICAST_LID_BASE ; 
 int QIB_MULTICAST_QPN ; 
 int QIB_PERMISSIVE_LID ; 
 int QIB_PROCESS_NEXT_SEND_OK ; 
 int QIB_PSN_MASK ; 
 int /*<<< orphan*/  QIB_S_BUSY ; 
 int /*<<< orphan*/  QIB_S_WAIT_DMA ; 
 int SIZE_OF_CRC ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 void* cpu_to_be16 (int) ; 
 void* cpu_to_be32 (int) ; 
 struct qib_swqe* get_swqe_ptr (struct qib_qp*,int) ; 
 int* ib_qib_state_ops ; 
 struct qib_pportdata* ppd_from_ibp (struct qib_ibport*) ; 
 int qib_get_pkey (struct qib_ibport*,int /*<<< orphan*/ ) ; 
 scalar_t__ qib_make_grh (struct qib_ibport*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  qib_send_complete (struct qib_qp*,struct qib_swqe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_ud_loopback (struct qib_qp*,struct qib_swqe*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_12__* to_iah (int /*<<< orphan*/ ) ; 
 struct qib_ibport* to_iport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int qib_make_ud_req(struct qib_qp *qp)
{
	struct qib_other_headers *ohdr;
	struct ib_ah_attr *ah_attr;
	struct qib_pportdata *ppd;
	struct qib_ibport *ibp;
	struct qib_swqe *wqe;
	unsigned long flags;
	u32 nwords;
	u32 extra_bytes;
	u32 bth0;
	u16 lrh0;
	u16 lid;
	int ret = 0;
	int next_cur;

	spin_lock_irqsave(&qp->s_lock, flags);

	if (!(ib_qib_state_ops[qp->state] & QIB_PROCESS_NEXT_SEND_OK)) {
		if (!(ib_qib_state_ops[qp->state] & QIB_FLUSH_SEND))
			goto bail;
		/* We are in the error state, flush the work request. */
		if (qp->s_last == qp->s_head)
			goto bail;
		/* If DMAs are in progress, we can't flush immediately. */
		if (atomic_read(&qp->s_dma_busy)) {
			qp->s_flags |= QIB_S_WAIT_DMA;
			goto bail;
		}
		wqe = get_swqe_ptr(qp, qp->s_last);
		qib_send_complete(qp, wqe, IB_WC_WR_FLUSH_ERR);
		goto done;
	}

	if (qp->s_cur == qp->s_head)
		goto bail;

	wqe = get_swqe_ptr(qp, qp->s_cur);
	next_cur = qp->s_cur + 1;
	if (next_cur >= qp->s_size)
		next_cur = 0;

	/* Construct the header. */
	ibp = to_iport(qp->ibqp.device, qp->port_num);
	ppd = ppd_from_ibp(ibp);
	ah_attr = &to_iah(wqe->wr.wr.ud.ah)->attr;
	if (ah_attr->dlid >= QIB_MULTICAST_LID_BASE) {
		if (ah_attr->dlid != QIB_PERMISSIVE_LID)
			ibp->n_multicast_xmit++;
		else
			ibp->n_unicast_xmit++;
	} else {
		ibp->n_unicast_xmit++;
		lid = ah_attr->dlid & ~((1 << ppd->lmc) - 1);
		if (unlikely(lid == ppd->lid)) {
			/*
			 * If DMAs are in progress, we can't generate
			 * a completion for the loopback packet since
			 * it would be out of order.
			 * XXX Instead of waiting, we could queue a
			 * zero length descriptor so we get a callback.
			 */
			if (atomic_read(&qp->s_dma_busy)) {
				qp->s_flags |= QIB_S_WAIT_DMA;
				goto bail;
			}
			qp->s_cur = next_cur;
			spin_unlock_irqrestore(&qp->s_lock, flags);
			qib_ud_loopback(qp, wqe);
			spin_lock_irqsave(&qp->s_lock, flags);
			qib_send_complete(qp, wqe, IB_WC_SUCCESS);
			goto done;
		}
	}

	qp->s_cur = next_cur;
	extra_bytes = -wqe->length & 3;
	nwords = (wqe->length + extra_bytes) >> 2;

	/* header size in 32-bit words LRH+BTH+DETH = (8+12+8)/4. */
	qp->s_hdrwords = 7;
	qp->s_cur_size = wqe->length;
	qp->s_cur_sge = &qp->s_sge;
	qp->s_srate = ah_attr->static_rate;
	qp->s_wqe = wqe;
	qp->s_sge.sge = wqe->sg_list[0];
	qp->s_sge.sg_list = wqe->sg_list + 1;
	qp->s_sge.num_sge = wqe->wr.num_sge;
	qp->s_sge.total_len = wqe->length;

	if (ah_attr->ah_flags & IB_AH_GRH) {
		/* Header size in 32-bit words. */
		qp->s_hdrwords += qib_make_grh(ibp, &qp->s_hdr->u.l.grh,
					       &ah_attr->grh,
					       qp->s_hdrwords, nwords);
		lrh0 = QIB_LRH_GRH;
		ohdr = &qp->s_hdr->u.l.oth;
		/*
		 * Don't worry about sending to locally attached multicast
		 * QPs.  It is unspecified by the spec. what happens.
		 */
	} else {
		/* Header size in 32-bit words. */
		lrh0 = QIB_LRH_BTH;
		ohdr = &qp->s_hdr->u.oth;
	}
	if (wqe->wr.opcode == IB_WR_SEND_WITH_IMM) {
		qp->s_hdrwords++;
		ohdr->u.ud.imm_data = wqe->wr.ex.imm_data;
		bth0 = IB_OPCODE_UD_SEND_ONLY_WITH_IMMEDIATE << 24;
	} else
		bth0 = IB_OPCODE_UD_SEND_ONLY << 24;
	lrh0 |= ah_attr->sl << 4;
	if (qp->ibqp.qp_type == IB_QPT_SMI)
		lrh0 |= 0xF000; /* Set VL (see ch. 13.5.3.1) */
	else
		lrh0 |= ibp->sl_to_vl[ah_attr->sl] << 12;
	qp->s_hdr->lrh[0] = cpu_to_be16(lrh0);
	qp->s_hdr->lrh[1] = cpu_to_be16(ah_attr->dlid);  /* DEST LID */
	qp->s_hdr->lrh[2] = cpu_to_be16(qp->s_hdrwords + nwords + SIZE_OF_CRC);
	lid = ppd->lid;
	if (lid) {
		lid |= ah_attr->src_path_bits & ((1 << ppd->lmc) - 1);
		qp->s_hdr->lrh[3] = cpu_to_be16(lid);
	} else
		qp->s_hdr->lrh[3] = IB_LID_PERMISSIVE;
	if (wqe->wr.send_flags & IB_SEND_SOLICITED)
		bth0 |= IB_BTH_SOLICITED;
	bth0 |= extra_bytes << 20;
	bth0 |= qp->ibqp.qp_type == IB_QPT_SMI ? QIB_DEFAULT_P_KEY :
		qib_get_pkey(ibp, qp->ibqp.qp_type == IB_QPT_GSI ?
			     wqe->wr.wr.ud.pkey_index : qp->s_pkey_index);
	ohdr->bth[0] = cpu_to_be32(bth0);
	/*
	 * Use the multicast QP if the destination LID is a multicast LID.
	 */
	ohdr->bth[1] = ah_attr->dlid >= QIB_MULTICAST_LID_BASE &&
		ah_attr->dlid != QIB_PERMISSIVE_LID ?
		cpu_to_be32(QIB_MULTICAST_QPN) :
		cpu_to_be32(wqe->wr.wr.ud.remote_qpn);
	ohdr->bth[2] = cpu_to_be32(qp->s_next_psn++ & QIB_PSN_MASK);
	/*
	 * Qkeys with the high order bit set mean use the
	 * qkey from the QP context instead of the WR (see 10.2.5).
	 */
	ohdr->u.ud.deth[0] = cpu_to_be32((int)wqe->wr.wr.ud.remote_qkey < 0 ?
					 qp->qkey : wqe->wr.wr.ud.remote_qkey);
	ohdr->u.ud.deth[1] = cpu_to_be32(qp->ibqp.qp_num);

done:
	ret = 1;
	goto unlock;

bail:
	qp->s_flags &= ~QIB_S_BUSY;
unlock:
	spin_unlock_irqrestore(&qp->s_lock, flags);
	return ret;
}