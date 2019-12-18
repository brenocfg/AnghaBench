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
struct enic {int /*<<< orphan*/ * intr; int /*<<< orphan*/ * cq; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned int enic_cq_wq (struct enic*,int /*<<< orphan*/ ) ; 
 unsigned int enic_msix_wq_intr (struct enic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enic_wq_service ; 
 unsigned int vnic_cq_service (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_intr_return_credits (int /*<<< orphan*/ *,unsigned int,int,int) ; 

__attribute__((used)) static irqreturn_t enic_isr_msix_wq(int irq, void *data)
{
	struct enic *enic = data;
	unsigned int cq = enic_cq_wq(enic, 0);
	unsigned int intr = enic_msix_wq_intr(enic, 0);
	unsigned int wq_work_to_do = -1; /* no limit */
	unsigned int wq_work_done;

	wq_work_done = vnic_cq_service(&enic->cq[cq],
		wq_work_to_do, enic_wq_service, NULL);

	vnic_intr_return_credits(&enic->intr[intr],
		wq_work_done,
		1 /* unmask intr */,
		1 /* reset intr timer */);

	return IRQ_HANDLED;
}