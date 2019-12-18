#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  intr_status; } ;
struct TYPE_4__ {TYPE_1__ bfa_regs; } ;
struct bfa_s {scalar_t__ queue_process; TYPE_2__ iocfc; } ;

/* Variables and functions */
 int BFI_IOC_MAX_CQS ; 
 int __HFN_INT_CPE_MASK ; 
 int __HFN_INT_RME_MASK ; 
 int /*<<< orphan*/  bfa_isr_reqq (struct bfa_s*,int) ; 
 int /*<<< orphan*/  bfa_isr_rspq (struct bfa_s*,int) ; 
 int /*<<< orphan*/  bfa_msix_lpu_err (struct bfa_s*,int) ; 
 int readl (int /*<<< orphan*/ ) ; 

void
bfa_msix_all(struct bfa_s *bfa, int vec)
{
	u32	intr, qintr;
	int	queue;

	intr = readl(bfa->iocfc.bfa_regs.intr_status);
	if (!intr)
		return;

	/*
	 * RME completion queue interrupt
	 */
	qintr = intr & __HFN_INT_RME_MASK;
	if (qintr && bfa->queue_process) {
		for (queue = 0; queue < BFI_IOC_MAX_CQS; queue++)
			bfa_isr_rspq(bfa, queue);
	}

	intr &= ~qintr;
	if (!intr)
		return;

	/*
	 * CPE completion queue interrupt
	 */
	qintr = intr & __HFN_INT_CPE_MASK;
	if (qintr && bfa->queue_process) {
		for (queue = 0; queue < BFI_IOC_MAX_CQS; queue++)
			bfa_isr_reqq(bfa, queue);
	}
	intr &= ~qintr;
	if (!intr)
		return;

	bfa_msix_lpu_err(bfa, intr);
}