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
typedef  size_t u32 ;
struct sk_buff {int dummy; } ;
struct TYPE_6__ {size_t rq_head; size_t rq_tail; int rq_size; size_t qp_id; struct sk_buff** rx_skb; } ;
struct TYPE_4__ {size_t cq_number; scalar_t__ cq_size; } ;
struct nes_vnic_mgt {TYPE_3__ mgt; TYPE_1__ mgt_cq; } ;
struct nes_vnic {int /*<<< orphan*/  mgt_pbase; int /*<<< orphan*/ * mgt_vbase; int /*<<< orphan*/  mgt_mem_size; struct nes_vnic_mgt** mgtvnic; int /*<<< orphan*/  mgt_thread; struct nes_device* nesdev; } ;
struct nes_hw_cqp_wqe {int /*<<< orphan*/  wqe_words; } ;
struct TYPE_5__ {size_t sq_head; size_t sq_size; int qp_id; size_t sq_tail; int /*<<< orphan*/  waitq; int /*<<< orphan*/  lock; struct nes_hw_cqp_wqe* sq_vbase; } ;
struct nes_device {int /*<<< orphan*/  pcidev; TYPE_2__ cqp; scalar_t__ regs; scalar_t__ ceq_index; } ;

/* Variables and functions */
 size_t NES_CQP_DESTROY_CQ ; 
 size_t NES_CQP_DESTROY_QP ; 
 size_t NES_CQP_QP_TYPE_NIC ; 
 int /*<<< orphan*/  NES_CQP_WQE_ID_IDX ; 
 int /*<<< orphan*/  NES_CQP_WQE_OPCODE_IDX ; 
 int /*<<< orphan*/  NES_DBG_SHUTDOWN ; 
 int /*<<< orphan*/  NES_EVENT_TIMEOUT ; 
 int NES_MGT_QP_COUNT ; 
 scalar_t__ NES_WQE_ALLOC ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  kfree (struct nes_vnic_mgt*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nes_debug (int /*<<< orphan*/ ,char*,size_t,...) ; 
 int /*<<< orphan*/  nes_fill_init_cqp_wqe (struct nes_hw_cqp_wqe*,struct nes_device*) ; 
 int /*<<< orphan*/  nes_mgt_free_skb (struct nes_device*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nes_write32 (scalar_t__,int) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_wqe_32bit_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void nes_destroy_mgt(struct nes_vnic *nesvnic)
{
	struct nes_device *nesdev = nesvnic->nesdev;
	struct nes_vnic_mgt *mgtvnic;
	struct nes_vnic_mgt *first_mgtvnic;
	unsigned long flags;
	struct nes_hw_cqp_wqe *cqp_wqe;
	u32 cqp_head;
	struct sk_buff *rx_skb;
	int i;
	int ret;

	kthread_stop(nesvnic->mgt_thread);

	/* Free remaining NIC receive buffers */
	first_mgtvnic = nesvnic->mgtvnic[0];
	for (i = 0; i < NES_MGT_QP_COUNT; i++) {
		mgtvnic = nesvnic->mgtvnic[i];
		if (mgtvnic == NULL)
			continue;

		while (mgtvnic->mgt.rq_head != mgtvnic->mgt.rq_tail) {
			rx_skb = mgtvnic->mgt.rx_skb[mgtvnic->mgt.rq_tail];
			nes_mgt_free_skb(nesdev, rx_skb, PCI_DMA_FROMDEVICE);
			mgtvnic->mgt.rq_tail++;
			mgtvnic->mgt.rq_tail &= (mgtvnic->mgt.rq_size - 1);
		}

		spin_lock_irqsave(&nesdev->cqp.lock, flags);

		/* Destroy NIC QP */
		cqp_head = nesdev->cqp.sq_head;
		cqp_wqe = &nesdev->cqp.sq_vbase[cqp_head];
		nes_fill_init_cqp_wqe(cqp_wqe, nesdev);

		set_wqe_32bit_value(cqp_wqe->wqe_words, NES_CQP_WQE_OPCODE_IDX,
				    (NES_CQP_DESTROY_QP | NES_CQP_QP_TYPE_NIC));
		set_wqe_32bit_value(cqp_wqe->wqe_words, NES_CQP_WQE_ID_IDX,
				    mgtvnic->mgt.qp_id);

		if (++cqp_head >= nesdev->cqp.sq_size)
			cqp_head = 0;

		cqp_wqe = &nesdev->cqp.sq_vbase[cqp_head];

		/* Destroy NIC CQ */
		nes_fill_init_cqp_wqe(cqp_wqe, nesdev);
		set_wqe_32bit_value(cqp_wqe->wqe_words, NES_CQP_WQE_OPCODE_IDX,
				    (NES_CQP_DESTROY_CQ | ((u32)mgtvnic->mgt_cq.cq_size << 16)));
		set_wqe_32bit_value(cqp_wqe->wqe_words, NES_CQP_WQE_ID_IDX,
				    (mgtvnic->mgt_cq.cq_number | ((u32)nesdev->ceq_index << 16)));

		if (++cqp_head >= nesdev->cqp.sq_size)
			cqp_head = 0;

		nesdev->cqp.sq_head = cqp_head;
		barrier();

		/* Ring doorbell (2 WQEs) */
		nes_write32(nesdev->regs + NES_WQE_ALLOC, 0x02800000 | nesdev->cqp.qp_id);

		spin_unlock_irqrestore(&nesdev->cqp.lock, flags);
		nes_debug(NES_DBG_SHUTDOWN, "Waiting for CQP, cqp_head=%u, cqp.sq_head=%u,"
			  " cqp.sq_tail=%u, cqp.sq_size=%u\n",
			  cqp_head, nesdev->cqp.sq_head,
			  nesdev->cqp.sq_tail, nesdev->cqp.sq_size);

		ret = wait_event_timeout(nesdev->cqp.waitq, (nesdev->cqp.sq_tail == cqp_head),
					 NES_EVENT_TIMEOUT);

		nes_debug(NES_DBG_SHUTDOWN, "Destroy MGT QP returned, wait_event_timeout ret = %u, cqp_head=%u,"
			  " cqp.sq_head=%u, cqp.sq_tail=%u\n",
			  ret, cqp_head, nesdev->cqp.sq_head, nesdev->cqp.sq_tail);
		if (!ret)
			nes_debug(NES_DBG_SHUTDOWN, "MGT QP%u destroy timeout expired\n",
				  mgtvnic->mgt.qp_id);

		nesvnic->mgtvnic[i] = NULL;
	}

	if (nesvnic->mgt_vbase) {
		pci_free_consistent(nesdev->pcidev, nesvnic->mgt_mem_size, nesvnic->mgt_vbase,
				    nesvnic->mgt_pbase);
		nesvnic->mgt_vbase = NULL;
		nesvnic->mgt_pbase = 0;
	}

	kfree(first_mgtvnic);
}