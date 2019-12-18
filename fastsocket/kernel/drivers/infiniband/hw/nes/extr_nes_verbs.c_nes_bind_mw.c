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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct nes_vnic {struct nes_device* nesdev; } ;
struct TYPE_6__ {int sq_head; int sq_tail; int qp_id; struct nes_hw_qp_wqe* sq_vbase; } ;
struct nes_qp {scalar_t__ ibqp_state; int /*<<< orphan*/  lock; TYPE_3__ hwqp; } ;
struct nes_hw_qp_wqe {scalar_t__* wqe_words; } ;
struct nes_device {scalar_t__ regs; } ;
struct ib_qp {int /*<<< orphan*/  device; } ;
struct TYPE_5__ {int mw_access_flags; int length; scalar_t__ addr; TYPE_1__* mr; } ;
struct ib_mw_bind {int send_flags; TYPE_2__ bind_info; scalar_t__ wr_id; } ;
struct ib_mw {int rkey; } ;
struct TYPE_4__ {int lkey; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int IB_ACCESS_REMOTE_READ ; 
 int IB_ACCESS_REMOTE_WRITE ; 
 scalar_t__ IB_QPS_RTS ; 
 int IB_SEND_SIGNALED ; 
 int NES_CQP_STAG_RIGHTS_REMOTE_READ ; 
 int NES_CQP_STAG_RIGHTS_REMOTE_WRITE ; 
 size_t NES_IWARP_SQ_BIND_WQE_LENGTH_HIGH_IDX ; 
 int /*<<< orphan*/  NES_IWARP_SQ_BIND_WQE_LENGTH_LOW_IDX ; 
 int /*<<< orphan*/  NES_IWARP_SQ_BIND_WQE_MR_IDX ; 
 int /*<<< orphan*/  NES_IWARP_SQ_BIND_WQE_MW_IDX ; 
 int /*<<< orphan*/  NES_IWARP_SQ_BIND_WQE_VA_FBO_LOW_IDX ; 
 int NES_IWARP_SQ_OP_BIND ; 
 int /*<<< orphan*/  NES_IWARP_SQ_WQE_COMP_SCRATCH_LOW_IDX ; 
 int NES_IWARP_SQ_WQE_LOCAL_FENCE ; 
 int /*<<< orphan*/  NES_IWARP_SQ_WQE_MISC_IDX ; 
 int NES_IWARP_SQ_WQE_SIGNALED_COMPL ; 
 scalar_t__ NES_WQE_ALLOC ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  nes_fill_init_qp_wqe (struct nes_hw_qp_wqe*,struct nes_qp*,int) ; 
 int /*<<< orphan*/  nes_write32 (scalar_t__,int) ; 
 int /*<<< orphan*/  set_wqe_32bit_value (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_wqe_64bit_value (scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct nes_qp* to_nesqp (struct ib_qp*) ; 
 struct nes_vnic* to_nesvnic (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nes_bind_mw(struct ib_qp *ibqp, struct ib_mw *ibmw,
		struct ib_mw_bind *ibmw_bind)
{
	u64 u64temp;
	struct nes_vnic *nesvnic = to_nesvnic(ibqp->device);
	struct nes_device *nesdev = nesvnic->nesdev;
	/* struct nes_mr *nesmr = to_nesmw(ibmw); */
	struct nes_qp *nesqp = to_nesqp(ibqp);
	struct nes_hw_qp_wqe *wqe;
	unsigned long flags = 0;
	u32 head;
	u32 wqe_misc = 0;
	u32 qsize;

	if (nesqp->ibqp_state > IB_QPS_RTS)
		return -EINVAL;

	spin_lock_irqsave(&nesqp->lock, flags);

	head = nesqp->hwqp.sq_head;
	qsize = nesqp->hwqp.sq_tail;

	/* Check for SQ overflow */
	if (((head + (2 * qsize) - nesqp->hwqp.sq_tail) % qsize) == (qsize - 1)) {
		spin_unlock_irqrestore(&nesqp->lock, flags);
		return -ENOMEM;
	}

	wqe = &nesqp->hwqp.sq_vbase[head];
	/* nes_debug(NES_DBG_MR, "processing sq wqe at %p, head = %u.\n", wqe, head); */
	nes_fill_init_qp_wqe(wqe, nesqp, head);
	u64temp = ibmw_bind->wr_id;
	set_wqe_64bit_value(wqe->wqe_words, NES_IWARP_SQ_WQE_COMP_SCRATCH_LOW_IDX, u64temp);
	wqe_misc = NES_IWARP_SQ_OP_BIND;

	wqe_misc |= NES_IWARP_SQ_WQE_LOCAL_FENCE;

	if (ibmw_bind->send_flags & IB_SEND_SIGNALED)
		wqe_misc |= NES_IWARP_SQ_WQE_SIGNALED_COMPL;

	if (ibmw_bind->bind_info.mw_access_flags & IB_ACCESS_REMOTE_WRITE)
		wqe_misc |= NES_CQP_STAG_RIGHTS_REMOTE_WRITE;
	if (ibmw_bind->bind_info.mw_access_flags & IB_ACCESS_REMOTE_READ)
		wqe_misc |= NES_CQP_STAG_RIGHTS_REMOTE_READ;

	set_wqe_32bit_value(wqe->wqe_words, NES_IWARP_SQ_WQE_MISC_IDX, wqe_misc);
	set_wqe_32bit_value(wqe->wqe_words, NES_IWARP_SQ_BIND_WQE_MR_IDX,
			    ibmw_bind->bind_info.mr->lkey);
	set_wqe_32bit_value(wqe->wqe_words, NES_IWARP_SQ_BIND_WQE_MW_IDX, ibmw->rkey);
	set_wqe_32bit_value(wqe->wqe_words, NES_IWARP_SQ_BIND_WQE_LENGTH_LOW_IDX,
			ibmw_bind->bind_info.length);
	wqe->wqe_words[NES_IWARP_SQ_BIND_WQE_LENGTH_HIGH_IDX] = 0;
	u64temp = (u64)ibmw_bind->bind_info.addr;
	set_wqe_64bit_value(wqe->wqe_words, NES_IWARP_SQ_BIND_WQE_VA_FBO_LOW_IDX, u64temp);

	head++;
	if (head >= qsize)
		head = 0;

	nesqp->hwqp.sq_head = head;
	barrier();

	nes_write32(nesdev->regs+NES_WQE_ALLOC,
			(1 << 24) | 0x00800000 | nesqp->hwqp.qp_id);

	spin_unlock_irqrestore(&nesqp->lock, flags);

	return 0;
}