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
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct nes_hw_aeqe {scalar_t__* aeqe_words; } ;
struct nes_hw_aeq {size_t aeq_head; size_t aeq_size; struct nes_hw_aeqe* aeq_vbase; } ;
struct nes_device {scalar_t__ regs; } ;

/* Variables and functions */
 size_t NES_AEQE_COMP_QP_CQ_ID_IDX ; 
 size_t NES_AEQE_CQ ; 
 size_t NES_AEQE_MISC_IDX ; 
 size_t NES_AEQE_QP ; 
 size_t NES_AEQE_VALID ; 
 scalar_t__ NES_AEQ_ALLOC ; 
 int /*<<< orphan*/  NES_DBG_AEQ ; 
 size_t NES_FIRST_QPN ; 
 size_t le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  nes_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nes_process_iwarp_aeqe (struct nes_device*,struct nes_hw_aeqe*) ; 
 int /*<<< orphan*/  nes_write32 (scalar_t__,int) ; 

__attribute__((used)) static void nes_process_aeq(struct nes_device *nesdev, struct nes_hw_aeq *aeq)
{
	/* u64 u64temp; */
	u32 head;
	u32 aeq_size;
	u32 aeqe_misc;
	u32 aeqe_cq_id;
	struct nes_hw_aeqe volatile *aeqe;

	head = aeq->aeq_head;
	aeq_size = aeq->aeq_size;

	do {
		aeqe = &aeq->aeq_vbase[head];
		if ((le32_to_cpu(aeqe->aeqe_words[NES_AEQE_MISC_IDX]) & NES_AEQE_VALID) == 0)
			break;
		aeqe_misc  = le32_to_cpu(aeqe->aeqe_words[NES_AEQE_MISC_IDX]);
		aeqe_cq_id = le32_to_cpu(aeqe->aeqe_words[NES_AEQE_COMP_QP_CQ_ID_IDX]);
		if (aeqe_misc & (NES_AEQE_QP|NES_AEQE_CQ)) {
			if (aeqe_cq_id >= NES_FIRST_QPN) {
				/* dealing with an accelerated QP related AE */
				/*
				 * u64temp = (((u64)(le32_to_cpu(aeqe->aeqe_words[NES_AEQE_COMP_CTXT_HIGH_IDX]))) << 32) |
				 *	     ((u64)(le32_to_cpu(aeqe->aeqe_words[NES_AEQE_COMP_CTXT_LOW_IDX])));
				 */
				nes_process_iwarp_aeqe(nesdev, (struct nes_hw_aeqe *)aeqe);
			} else {
				/* TODO: dealing with a CQP related AE */
				nes_debug(NES_DBG_AEQ, "Processing CQP related AE, misc = 0x%04X\n",
						(u16)(aeqe_misc >> 16));
			}
		}

		aeqe->aeqe_words[NES_AEQE_MISC_IDX] = 0;

		if (++head >= aeq_size)
			head = 0;

		nes_write32(nesdev->regs + NES_AEQ_ALLOC, 1 << 16);
	}
	while (1);
	aeq->aeq_head = head;
}