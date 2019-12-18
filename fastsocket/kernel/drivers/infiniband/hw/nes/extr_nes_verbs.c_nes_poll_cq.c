#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct nes_vnic {struct nes_device* nesdev; } ;
struct TYPE_8__ {int sq_tail; int sq_size; int sq_head; int rq_tail; int rq_size; int rq_head; TYPE_2__* rq_vbase; TYPE_1__* sq_vbase; int /*<<< orphan*/  qp_id; } ;
struct nes_qp {TYPE_3__ hwqp; scalar_t__ skip_lsmm; int /*<<< orphan*/  ibqp; } ;
struct nes_hw_cqe {scalar_t__* cqe_words; } ;
struct nes_device {scalar_t__ regs; TYPE_4__* nesadapter; } ;
struct TYPE_10__ {int cq_head; int cq_size; int cq_number; struct nes_hw_cqe* cq_vbase; } ;
struct nes_cq {int polled_completions; int /*<<< orphan*/  lock; TYPE_5__ hw_cq; } ;
struct ib_wc {int status; int byte_len; int wr_id; int /*<<< orphan*/  opcode; int /*<<< orphan*/  src_qp; int /*<<< orphan*/ * qp; } ;
struct ib_cq {int /*<<< orphan*/  device; } ;
struct TYPE_9__ {int max_qp_wr; } ;
struct TYPE_7__ {scalar_t__* wqe_words; } ;
struct TYPE_6__ {scalar_t__* wqe_words; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_WC_FAST_REG_MR ; 
 int /*<<< orphan*/  IB_WC_LOCAL_INV ; 
 int /*<<< orphan*/  IB_WC_RDMA_READ ; 
 int /*<<< orphan*/  IB_WC_RDMA_WRITE ; 
 int /*<<< orphan*/  IB_WC_RECV ; 
 int /*<<< orphan*/  IB_WC_SEND ; 
 int IB_WC_SUCCESS ; 
 int IB_WC_WR_FLUSH_ERR ; 
 scalar_t__ NES_CQE_ALLOC ; 
 size_t NES_CQE_COMP_COMP_CTX_HIGH_IDX ; 
 size_t NES_CQE_COMP_COMP_CTX_LOW_IDX ; 
 size_t NES_CQE_ERROR_CODE_IDX ; 
 size_t NES_CQE_OPCODE_IDX ; 
 size_t NES_CQE_PAYLOAD_LENGTH_IDX ; 
 int NES_CQE_SQ ; 
 int NES_CQE_VALID ; 
 int /*<<< orphan*/  NES_DBG_CQ ; 
 int NES_IWARP_CQE_MAJOR_DRV ; 
 int NES_IWARP_CQE_MAJOR_FLUSH ; 
 int NES_IWARP_CQE_MINOR_FLUSH ; 
 size_t NES_IWARP_RQ_WQE_COMP_SCRATCH_HIGH_IDX ; 
 size_t NES_IWARP_RQ_WQE_COMP_SCRATCH_LOW_IDX ; 
#define  NES_IWARP_SQ_OP_FAST_REG 135 
#define  NES_IWARP_SQ_OP_LOCINV 134 
#define  NES_IWARP_SQ_OP_RDMAR 133 
#define  NES_IWARP_SQ_OP_RDMAW 132 
#define  NES_IWARP_SQ_OP_SEND 131 
#define  NES_IWARP_SQ_OP_SENDINV 130 
#define  NES_IWARP_SQ_OP_SENDSE 129 
#define  NES_IWARP_SQ_OP_SENDSEINV 128 
 size_t NES_IWARP_SQ_WQE_COMP_SCRATCH_HIGH_IDX ; 
 size_t NES_IWARP_SQ_WQE_COMP_SCRATCH_LOW_IDX ; 
 size_t NES_IWARP_SQ_WQE_MISC_IDX ; 
 size_t NES_IWARP_SQ_WQE_RDMA_LENGTH_IDX ; 
 size_t NES_IWARP_SQ_WQE_TOTAL_PAYLOAD_IDX ; 
 int NES_SW_CONTEXT_ALIGN ; 
 void* cpu_to_le32 (int) ; 
 int le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct ib_wc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nes_debug (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  nes_write32 (scalar_t__,int) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct nes_cq* to_nescq (struct ib_cq*) ; 
 struct nes_vnic* to_nesvnic (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nes_poll_cq(struct ib_cq *ibcq, int num_entries, struct ib_wc *entry)
{
	u64 u64temp;
	u64 wrid;
	unsigned long flags = 0;
	struct nes_vnic *nesvnic = to_nesvnic(ibcq->device);
	struct nes_device *nesdev = nesvnic->nesdev;
	struct nes_cq *nescq = to_nescq(ibcq);
	struct nes_qp *nesqp;
	struct nes_hw_cqe cqe;
	u32 head;
	u32 wq_tail = 0;
	u32 cq_size;
	u32 cqe_count = 0;
	u32 wqe_index;
	u32 u32temp;
	u32 move_cq_head = 1;
	u32 err_code;

	nes_debug(NES_DBG_CQ, "\n");

	spin_lock_irqsave(&nescq->lock, flags);

	head = nescq->hw_cq.cq_head;
	cq_size = nescq->hw_cq.cq_size;

	while (cqe_count < num_entries) {
		if ((le32_to_cpu(nescq->hw_cq.cq_vbase[head].cqe_words[NES_CQE_OPCODE_IDX]) &
				NES_CQE_VALID) == 0)
			break;

		/*
		 * Make sure we read CQ entry contents *after*
		 * we've checked the valid bit.
		 */
		rmb();

		cqe = nescq->hw_cq.cq_vbase[head];
		u32temp = le32_to_cpu(cqe.cqe_words[NES_CQE_COMP_COMP_CTX_LOW_IDX]);
		wqe_index = u32temp & (nesdev->nesadapter->max_qp_wr - 1);
		u32temp &= ~(NES_SW_CONTEXT_ALIGN-1);
		/* parse CQE, get completion context from WQE (either rq or sq) */
		u64temp = (((u64)(le32_to_cpu(cqe.cqe_words[NES_CQE_COMP_COMP_CTX_HIGH_IDX])))<<32) |
				((u64)u32temp);

		if (u64temp) {
			nesqp = (struct nes_qp *)(unsigned long)u64temp;
			memset(entry, 0, sizeof *entry);
			if (cqe.cqe_words[NES_CQE_ERROR_CODE_IDX] == 0) {
				entry->status = IB_WC_SUCCESS;
			} else {
				err_code = le32_to_cpu(cqe.cqe_words[NES_CQE_ERROR_CODE_IDX]);
				if (NES_IWARP_CQE_MAJOR_DRV == (err_code >> 16)) {
					entry->status = err_code & 0x0000ffff;

					/* The rest of the cqe's will be marked as flushed */
					nescq->hw_cq.cq_vbase[head].cqe_words[NES_CQE_ERROR_CODE_IDX] =
						cpu_to_le32((NES_IWARP_CQE_MAJOR_FLUSH << 16) |
							    NES_IWARP_CQE_MINOR_FLUSH);
				} else
					entry->status = IB_WC_WR_FLUSH_ERR;
			}

			entry->qp = &nesqp->ibqp;
			entry->src_qp = nesqp->hwqp.qp_id;

			if (le32_to_cpu(cqe.cqe_words[NES_CQE_OPCODE_IDX]) & NES_CQE_SQ) {
				if (nesqp->skip_lsmm) {
					nesqp->skip_lsmm = 0;
					nesqp->hwqp.sq_tail++;
				}

				/* Working on a SQ Completion*/
				wrid = (((u64)(cpu_to_le32((u32)nesqp->hwqp.sq_vbase[wqe_index].
						wqe_words[NES_IWARP_SQ_WQE_COMP_SCRATCH_HIGH_IDX]))) << 32) |
						((u64)(cpu_to_le32((u32)nesqp->hwqp.sq_vbase[wqe_index].
						wqe_words[NES_IWARP_SQ_WQE_COMP_SCRATCH_LOW_IDX])));
				entry->byte_len = le32_to_cpu(nesqp->hwqp.sq_vbase[wqe_index].
						wqe_words[NES_IWARP_SQ_WQE_TOTAL_PAYLOAD_IDX]);

				switch (le32_to_cpu(nesqp->hwqp.sq_vbase[wqe_index].
						wqe_words[NES_IWARP_SQ_WQE_MISC_IDX]) & 0x3f) {
					case NES_IWARP_SQ_OP_RDMAW:
						nes_debug(NES_DBG_CQ, "Operation = RDMA WRITE.\n");
						entry->opcode = IB_WC_RDMA_WRITE;
						break;
					case NES_IWARP_SQ_OP_RDMAR:
						nes_debug(NES_DBG_CQ, "Operation = RDMA READ.\n");
						entry->opcode = IB_WC_RDMA_READ;
						entry->byte_len = le32_to_cpu(nesqp->hwqp.sq_vbase[wqe_index].
								wqe_words[NES_IWARP_SQ_WQE_RDMA_LENGTH_IDX]);
						break;
					case NES_IWARP_SQ_OP_SENDINV:
					case NES_IWARP_SQ_OP_SENDSEINV:
					case NES_IWARP_SQ_OP_SEND:
					case NES_IWARP_SQ_OP_SENDSE:
						nes_debug(NES_DBG_CQ, "Operation = Send.\n");
						entry->opcode = IB_WC_SEND;
						break;
					case NES_IWARP_SQ_OP_LOCINV:
						entry->opcode = IB_WC_LOCAL_INV;
						break;
					case NES_IWARP_SQ_OP_FAST_REG:
						entry->opcode = IB_WC_FAST_REG_MR;
						break;
				}

				nesqp->hwqp.sq_tail = (wqe_index+1)&(nesqp->hwqp.sq_size - 1);
				if ((entry->status != IB_WC_SUCCESS) && (nesqp->hwqp.sq_tail != nesqp->hwqp.sq_head)) {
					move_cq_head = 0;
					wq_tail = nesqp->hwqp.sq_tail;
				}
			} else {
				/* Working on a RQ Completion*/
				entry->byte_len = le32_to_cpu(cqe.cqe_words[NES_CQE_PAYLOAD_LENGTH_IDX]);
				wrid = ((u64)(le32_to_cpu(nesqp->hwqp.rq_vbase[wqe_index].wqe_words[NES_IWARP_RQ_WQE_COMP_SCRATCH_LOW_IDX]))) |
					((u64)(le32_to_cpu(nesqp->hwqp.rq_vbase[wqe_index].wqe_words[NES_IWARP_RQ_WQE_COMP_SCRATCH_HIGH_IDX]))<<32);
					entry->opcode = IB_WC_RECV;

				nesqp->hwqp.rq_tail = (wqe_index+1)&(nesqp->hwqp.rq_size - 1);
				if ((entry->status != IB_WC_SUCCESS) && (nesqp->hwqp.rq_tail != nesqp->hwqp.rq_head)) {
					move_cq_head = 0;
					wq_tail = nesqp->hwqp.rq_tail;
				}
			}

			entry->wr_id = wrid;
			entry++;
			cqe_count++;
		}

		if (move_cq_head) {
			nescq->hw_cq.cq_vbase[head].cqe_words[NES_CQE_OPCODE_IDX] = 0;
			if (++head >= cq_size)
				head = 0;
			nescq->polled_completions++;

			if ((nescq->polled_completions > (cq_size / 2)) ||
					(nescq->polled_completions == 255)) {
				nes_debug(NES_DBG_CQ, "CQ%u Issuing CQE Allocate since more than half of cqes"
					" are pending %u of %u.\n",
					nescq->hw_cq.cq_number, nescq->polled_completions, cq_size);
				nes_write32(nesdev->regs+NES_CQE_ALLOC,
					nescq->hw_cq.cq_number | (nescq->polled_completions << 16));
				nescq->polled_completions = 0;
			}
		} else {
			/* Update the wqe index and set status to flush */
			wqe_index = le32_to_cpu(cqe.cqe_words[NES_CQE_COMP_COMP_CTX_LOW_IDX]);
			wqe_index = (wqe_index & (~(nesdev->nesadapter->max_qp_wr - 1))) | wq_tail;
			nescq->hw_cq.cq_vbase[head].cqe_words[NES_CQE_COMP_COMP_CTX_LOW_IDX] =
				cpu_to_le32(wqe_index);
			move_cq_head = 1; /* ready for next pass */
		}
	}

	if (nescq->polled_completions) {
		nes_write32(nesdev->regs+NES_CQE_ALLOC,
				nescq->hw_cq.cq_number | (nescq->polled_completions << 16));
		nescq->polled_completions = 0;
	}

	nescq->hw_cq.cq_head = head;
	nes_debug(NES_DBG_CQ, "Reporting %u completions for CQ%u.\n",
			cqe_count, nescq->hw_cq.cq_number);

	spin_unlock_irqrestore(&nescq->lock, flags);

	return cqe_count;
}