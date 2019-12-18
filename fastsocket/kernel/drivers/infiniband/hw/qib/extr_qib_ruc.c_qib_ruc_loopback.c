#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_16__ ;
typedef  struct TYPE_21__   TYPE_14__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_26__ {int /*<<< orphan*/  swap; scalar_t__ compare_add; int /*<<< orphan*/  rkey; int /*<<< orphan*/  remote_addr; } ;
struct TYPE_25__ {int /*<<< orphan*/  rkey; int /*<<< orphan*/  remote_addr; } ;
struct TYPE_27__ {TYPE_4__ atomic; TYPE_3__ rdma; } ;
struct TYPE_24__ {int /*<<< orphan*/  imm_data; } ;
struct TYPE_17__ {int num_sge; int opcode; int send_flags; TYPE_5__ wr; TYPE_2__ ex; } ;
struct qib_swqe {int length; TYPE_10__ wr; struct qib_sge* sg_list; } ;
struct qib_sge {scalar_t__ length; scalar_t__ sge_length; scalar_t__ n; scalar_t__ m; TYPE_14__* mr; scalar_t__ vaddr; } ;
struct TYPE_19__ {scalar_t__ qp_type; int /*<<< orphan*/  qp_context; int /*<<< orphan*/  (* event_handler ) (struct ib_event*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  device; int /*<<< orphan*/  recv_cq; } ;
struct TYPE_22__ {scalar_t__ expires; int /*<<< orphan*/  function; } ;
struct TYPE_31__ {int /*<<< orphan*/  sl; int /*<<< orphan*/  dlid; } ;
struct TYPE_20__ {int num_sge; int total_len; struct qib_sge sge; struct qib_sge* sg_list; } ;
struct TYPE_28__ {int num_sge; struct qib_sge* sg_list; struct qib_sge sge; } ;
struct qib_qp {int s_flags; size_t state; scalar_t__ s_last; scalar_t__ s_head; scalar_t__ s_cur; scalar_t__ s_size; int s_len; int qp_access_flags; scalar_t__ s_rnr_retry; scalar_t__ s_rnr_retry_cnt; size_t r_min_rnr_timer; int /*<<< orphan*/  wait; int /*<<< orphan*/  refcount; int /*<<< orphan*/  s_lock; TYPE_12__ ibqp; TYPE_16__ s_timer; TYPE_9__ remote_ah_attr; int /*<<< orphan*/  remote_qpn; int /*<<< orphan*/  r_wr_id; int /*<<< orphan*/  r_aflags; TYPE_13__ r_sge; TYPE_6__ s_sge; int /*<<< orphan*/  port_num; } ;
struct qib_ibport {int /*<<< orphan*/  n_rnr_naks; int /*<<< orphan*/  n_loop_pkts; int /*<<< orphan*/  n_pkt_drops; } ;
struct TYPE_23__ {int /*<<< orphan*/  imm_data; } ;
struct ib_wc {int byte_len; int port_num; void* status; int /*<<< orphan*/  sl; int /*<<< orphan*/  slid; int /*<<< orphan*/  src_qp; TYPE_12__* qp; int /*<<< orphan*/  wr_id; int /*<<< orphan*/  opcode; TYPE_1__ ex; void* wc_flags; } ;
struct TYPE_18__ {TYPE_12__* qp; } ;
struct ib_event {int /*<<< orphan*/  event; TYPE_11__ element; int /*<<< orphan*/  device; } ;
typedef  enum ib_wc_status { ____Placeholder_ib_wc_status } ib_wc_status ;
typedef  int /*<<< orphan*/  atomic64_t ;
struct TYPE_30__ {TYPE_7__* segs; } ;
struct TYPE_29__ {scalar_t__ length; scalar_t__ vaddr; } ;
struct TYPE_21__ {scalar_t__ mapsz; TYPE_8__** map; scalar_t__ lkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int IB_ACCESS_REMOTE_ATOMIC ; 
 int IB_ACCESS_REMOTE_READ ; 
 int IB_ACCESS_REMOTE_WRITE ; 
 int /*<<< orphan*/  IB_EVENT_QP_LAST_WQE_REACHED ; 
 scalar_t__ IB_QPT_RC ; 
 scalar_t__ IB_QPT_UC ; 
 int IB_SEND_SOLICITED ; 
 void* IB_WC_LOC_PROT_ERR ; 
 void* IB_WC_LOC_QP_OP_ERR ; 
 int /*<<< orphan*/  IB_WC_RECV ; 
 int /*<<< orphan*/  IB_WC_RECV_RDMA_WITH_IMM ; 
 int IB_WC_REM_ACCESS_ERR ; 
 int IB_WC_REM_INV_REQ_ERR ; 
 int IB_WC_REM_OP_ERR ; 
 int IB_WC_RETRY_EXC_ERR ; 
 int IB_WC_RNR_RETRY_EXC_ERR ; 
 void* IB_WC_SUCCESS ; 
 void* IB_WC_WITH_IMM ; 
 int IB_WC_WR_FLUSH_ERR ; 
#define  IB_WR_ATOMIC_CMP_AND_SWP 134 
#define  IB_WR_ATOMIC_FETCH_AND_ADD 133 
#define  IB_WR_RDMA_READ 132 
#define  IB_WR_RDMA_WRITE 131 
#define  IB_WR_RDMA_WRITE_WITH_IMM 130 
#define  IB_WR_SEND 129 
#define  IB_WR_SEND_WITH_IMM 128 
 int QIB_FLUSH_SEND ; 
 int QIB_PROCESS_NEXT_SEND_OK ; 
 int QIB_PROCESS_OR_FLUSH_SEND ; 
 int QIB_PROCESS_RECV_OK ; 
 int /*<<< orphan*/  QIB_R_WRID_VALID ; 
 scalar_t__ QIB_SEGSZ ; 
 int QIB_S_ANY_WAIT ; 
 int QIB_S_BUSY ; 
 int QIB_S_WAIT_RNR ; 
 int /*<<< orphan*/  add_timer (TYPE_16__*) ; 
 int /*<<< orphan*/  atomic64_add_return (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmpxchg (scalar_t__*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct qib_swqe* get_swqe_ptr (struct qib_qp*,scalar_t__) ; 
 int /*<<< orphan*/ * ib_qib_rnr_table ; 
 int* ib_qib_state_ops ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  memset (struct ib_wc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qib_copy_sge (TYPE_13__*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  qib_cq_enter (int /*<<< orphan*/ ,struct ib_wc*,int) ; 
 int qib_error_qp (struct qib_qp*,int) ; 
 int qib_get_rwqe (struct qib_qp*,int) ; 
 struct qib_qp* qib_lookup_qpn (struct qib_ibport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_put_mr (TYPE_14__*) ; 
 int /*<<< orphan*/  qib_put_ss (TYPE_13__*) ; 
 int /*<<< orphan*/  qib_rc_error (struct qib_qp*,void*) ; 
 int /*<<< orphan*/  qib_rc_rnr_retry ; 
 int /*<<< orphan*/  qib_rkey_ok (struct qib_qp*,struct qib_sge*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qib_send_complete (struct qib_qp*,struct qib_swqe*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct ib_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_icq (int /*<<< orphan*/ ) ; 
 struct qib_ibport* to_iport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlikely (int) ; 
 scalar_t__ usecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qib_ruc_loopback(struct qib_qp *sqp)
{
	struct qib_ibport *ibp = to_iport(sqp->ibqp.device, sqp->port_num);
	struct qib_qp *qp;
	struct qib_swqe *wqe;
	struct qib_sge *sge;
	unsigned long flags;
	struct ib_wc wc;
	u64 sdata;
	atomic64_t *maddr;
	enum ib_wc_status send_status;
	int release;
	int ret;

	/*
	 * Note that we check the responder QP state after
	 * checking the requester's state.
	 */
	qp = qib_lookup_qpn(ibp, sqp->remote_qpn);

	spin_lock_irqsave(&sqp->s_lock, flags);

	/* Return if we are already busy processing a work request. */
	if ((sqp->s_flags & (QIB_S_BUSY | QIB_S_ANY_WAIT)) ||
	    !(ib_qib_state_ops[sqp->state] & QIB_PROCESS_OR_FLUSH_SEND))
		goto unlock;

	sqp->s_flags |= QIB_S_BUSY;

again:
	if (sqp->s_last == sqp->s_head)
		goto clr_busy;
	wqe = get_swqe_ptr(sqp, sqp->s_last);

	/* Return if it is not OK to start a new work reqeust. */
	if (!(ib_qib_state_ops[sqp->state] & QIB_PROCESS_NEXT_SEND_OK)) {
		if (!(ib_qib_state_ops[sqp->state] & QIB_FLUSH_SEND))
			goto clr_busy;
		/* We are in the error state, flush the work request. */
		send_status = IB_WC_WR_FLUSH_ERR;
		goto flush_send;
	}

	/*
	 * We can rely on the entry not changing without the s_lock
	 * being held until we update s_last.
	 * We increment s_cur to indicate s_last is in progress.
	 */
	if (sqp->s_last == sqp->s_cur) {
		if (++sqp->s_cur >= sqp->s_size)
			sqp->s_cur = 0;
	}
	spin_unlock_irqrestore(&sqp->s_lock, flags);

	if (!qp || !(ib_qib_state_ops[qp->state] & QIB_PROCESS_RECV_OK) ||
	    qp->ibqp.qp_type != sqp->ibqp.qp_type) {
		ibp->n_pkt_drops++;
		/*
		 * For RC, the requester would timeout and retry so
		 * shortcut the timeouts and just signal too many retries.
		 */
		if (sqp->ibqp.qp_type == IB_QPT_RC)
			send_status = IB_WC_RETRY_EXC_ERR;
		else
			send_status = IB_WC_SUCCESS;
		goto serr;
	}

	memset(&wc, 0, sizeof wc);
	send_status = IB_WC_SUCCESS;

	release = 1;
	sqp->s_sge.sge = wqe->sg_list[0];
	sqp->s_sge.sg_list = wqe->sg_list + 1;
	sqp->s_sge.num_sge = wqe->wr.num_sge;
	sqp->s_len = wqe->length;
	switch (wqe->wr.opcode) {
	case IB_WR_SEND_WITH_IMM:
		wc.wc_flags = IB_WC_WITH_IMM;
		wc.ex.imm_data = wqe->wr.ex.imm_data;
		/* FALLTHROUGH */
	case IB_WR_SEND:
		ret = qib_get_rwqe(qp, 0);
		if (ret < 0)
			goto op_err;
		if (!ret)
			goto rnr_nak;
		break;

	case IB_WR_RDMA_WRITE_WITH_IMM:
		if (unlikely(!(qp->qp_access_flags & IB_ACCESS_REMOTE_WRITE)))
			goto inv_err;
		wc.wc_flags = IB_WC_WITH_IMM;
		wc.ex.imm_data = wqe->wr.ex.imm_data;
		ret = qib_get_rwqe(qp, 1);
		if (ret < 0)
			goto op_err;
		if (!ret)
			goto rnr_nak;
		/* FALLTHROUGH */
	case IB_WR_RDMA_WRITE:
		if (unlikely(!(qp->qp_access_flags & IB_ACCESS_REMOTE_WRITE)))
			goto inv_err;
		if (wqe->length == 0)
			break;
		if (unlikely(!qib_rkey_ok(qp, &qp->r_sge.sge, wqe->length,
					  wqe->wr.wr.rdma.remote_addr,
					  wqe->wr.wr.rdma.rkey,
					  IB_ACCESS_REMOTE_WRITE)))
			goto acc_err;
		qp->r_sge.sg_list = NULL;
		qp->r_sge.num_sge = 1;
		qp->r_sge.total_len = wqe->length;
		break;

	case IB_WR_RDMA_READ:
		if (unlikely(!(qp->qp_access_flags & IB_ACCESS_REMOTE_READ)))
			goto inv_err;
		if (unlikely(!qib_rkey_ok(qp, &sqp->s_sge.sge, wqe->length,
					  wqe->wr.wr.rdma.remote_addr,
					  wqe->wr.wr.rdma.rkey,
					  IB_ACCESS_REMOTE_READ)))
			goto acc_err;
		release = 0;
		sqp->s_sge.sg_list = NULL;
		sqp->s_sge.num_sge = 1;
		qp->r_sge.sge = wqe->sg_list[0];
		qp->r_sge.sg_list = wqe->sg_list + 1;
		qp->r_sge.num_sge = wqe->wr.num_sge;
		qp->r_sge.total_len = wqe->length;
		break;

	case IB_WR_ATOMIC_CMP_AND_SWP:
	case IB_WR_ATOMIC_FETCH_AND_ADD:
		if (unlikely(!(qp->qp_access_flags & IB_ACCESS_REMOTE_ATOMIC)))
			goto inv_err;
		if (unlikely(!qib_rkey_ok(qp, &qp->r_sge.sge, sizeof(u64),
					  wqe->wr.wr.atomic.remote_addr,
					  wqe->wr.wr.atomic.rkey,
					  IB_ACCESS_REMOTE_ATOMIC)))
			goto acc_err;
		/* Perform atomic OP and save result. */
		maddr = (atomic64_t *) qp->r_sge.sge.vaddr;
		sdata = wqe->wr.wr.atomic.compare_add;
		*(u64 *) sqp->s_sge.sge.vaddr =
			(wqe->wr.opcode == IB_WR_ATOMIC_FETCH_AND_ADD) ?
			(u64) atomic64_add_return(sdata, maddr) - sdata :
			(u64) cmpxchg((u64 *) qp->r_sge.sge.vaddr,
				      sdata, wqe->wr.wr.atomic.swap);
		qib_put_mr(qp->r_sge.sge.mr);
		qp->r_sge.num_sge = 0;
		goto send_comp;

	default:
		send_status = IB_WC_LOC_QP_OP_ERR;
		goto serr;
	}

	sge = &sqp->s_sge.sge;
	while (sqp->s_len) {
		u32 len = sqp->s_len;

		if (len > sge->length)
			len = sge->length;
		if (len > sge->sge_length)
			len = sge->sge_length;
		BUG_ON(len == 0);
		qib_copy_sge(&qp->r_sge, sge->vaddr, len, release);
		sge->vaddr += len;
		sge->length -= len;
		sge->sge_length -= len;
		if (sge->sge_length == 0) {
			if (!release)
				qib_put_mr(sge->mr);
			if (--sqp->s_sge.num_sge)
				*sge = *sqp->s_sge.sg_list++;
		} else if (sge->length == 0 && sge->mr->lkey) {
			if (++sge->n >= QIB_SEGSZ) {
				if (++sge->m >= sge->mr->mapsz)
					break;
				sge->n = 0;
			}
			sge->vaddr =
				sge->mr->map[sge->m]->segs[sge->n].vaddr;
			sge->length =
				sge->mr->map[sge->m]->segs[sge->n].length;
		}
		sqp->s_len -= len;
	}
	if (release)
		qib_put_ss(&qp->r_sge);

	if (!test_and_clear_bit(QIB_R_WRID_VALID, &qp->r_aflags))
		goto send_comp;

	if (wqe->wr.opcode == IB_WR_RDMA_WRITE_WITH_IMM)
		wc.opcode = IB_WC_RECV_RDMA_WITH_IMM;
	else
		wc.opcode = IB_WC_RECV;
	wc.wr_id = qp->r_wr_id;
	wc.status = IB_WC_SUCCESS;
	wc.byte_len = wqe->length;
	wc.qp = &qp->ibqp;
	wc.src_qp = qp->remote_qpn;
	wc.slid = qp->remote_ah_attr.dlid;
	wc.sl = qp->remote_ah_attr.sl;
	wc.port_num = 1;
	/* Signal completion event if the solicited bit is set. */
	qib_cq_enter(to_icq(qp->ibqp.recv_cq), &wc,
		       wqe->wr.send_flags & IB_SEND_SOLICITED);

send_comp:
	spin_lock_irqsave(&sqp->s_lock, flags);
	ibp->n_loop_pkts++;
flush_send:
	sqp->s_rnr_retry = sqp->s_rnr_retry_cnt;
	qib_send_complete(sqp, wqe, send_status);
	goto again;

rnr_nak:
	/* Handle RNR NAK */
	if (qp->ibqp.qp_type == IB_QPT_UC)
		goto send_comp;
	ibp->n_rnr_naks++;
	/*
	 * Note: we don't need the s_lock held since the BUSY flag
	 * makes this single threaded.
	 */
	if (sqp->s_rnr_retry == 0) {
		send_status = IB_WC_RNR_RETRY_EXC_ERR;
		goto serr;
	}
	if (sqp->s_rnr_retry_cnt < 7)
		sqp->s_rnr_retry--;
	spin_lock_irqsave(&sqp->s_lock, flags);
	if (!(ib_qib_state_ops[sqp->state] & QIB_PROCESS_RECV_OK))
		goto clr_busy;
	sqp->s_flags |= QIB_S_WAIT_RNR;
	sqp->s_timer.function = qib_rc_rnr_retry;
	sqp->s_timer.expires = jiffies +
		usecs_to_jiffies(ib_qib_rnr_table[qp->r_min_rnr_timer]);
	add_timer(&sqp->s_timer);
	goto clr_busy;

op_err:
	send_status = IB_WC_REM_OP_ERR;
	wc.status = IB_WC_LOC_QP_OP_ERR;
	goto err;

inv_err:
	send_status = IB_WC_REM_INV_REQ_ERR;
	wc.status = IB_WC_LOC_QP_OP_ERR;
	goto err;

acc_err:
	send_status = IB_WC_REM_ACCESS_ERR;
	wc.status = IB_WC_LOC_PROT_ERR;
err:
	/* responder goes to error state */
	qib_rc_error(qp, wc.status);

serr:
	spin_lock_irqsave(&sqp->s_lock, flags);
	qib_send_complete(sqp, wqe, send_status);
	if (sqp->ibqp.qp_type == IB_QPT_RC) {
		int lastwqe = qib_error_qp(sqp, IB_WC_WR_FLUSH_ERR);

		sqp->s_flags &= ~QIB_S_BUSY;
		spin_unlock_irqrestore(&sqp->s_lock, flags);
		if (lastwqe) {
			struct ib_event ev;

			ev.device = sqp->ibqp.device;
			ev.element.qp = &sqp->ibqp;
			ev.event = IB_EVENT_QP_LAST_WQE_REACHED;
			sqp->ibqp.event_handler(&ev, sqp->ibqp.qp_context);
		}
		goto done;
	}
clr_busy:
	sqp->s_flags &= ~QIB_S_BUSY;
unlock:
	spin_unlock_irqrestore(&sqp->s_lock, flags);
done:
	if (qp && atomic_dec_and_test(&qp->refcount))
		wake_up(&qp->wait);
}