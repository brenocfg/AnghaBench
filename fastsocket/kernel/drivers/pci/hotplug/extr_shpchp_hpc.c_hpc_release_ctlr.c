#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct controller {int num_slots; int /*<<< orphan*/  mmio_size; int /*<<< orphan*/  mmio_base; int /*<<< orphan*/  creg; TYPE_1__* pci_dev; int /*<<< orphan*/  poll_timer; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int ARBITER_SERR_MASK ; 
 int BUTTON_PRESS_INTR_MASK ; 
 int COMMAND_INTR_MASK ; 
 int CON_PFAULT_INTR_MASK ; 
 int CON_PFAULT_SERR_MASK ; 
 int GLOBAL_INTR_MASK ; 
 int GLOBAL_SERR_MASK ; 
 int ISO_PFAULT_INTR_MASK ; 
 int MRL_CHANGE_INTR_MASK ; 
 int MRL_CHANGE_SERR_MASK ; 
 int PRSNT_CHANGE_INTR_MASK ; 
 int /*<<< orphan*/  SERR_INTR_ENABLE ; 
 int SERR_INTR_RSVDZ_MASK ; 
 int /*<<< orphan*/  SLOT_REG (int) ; 
 int SLOT_REG_RSVDZ_MASK ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cleanup_slots (struct controller*) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct controller*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_msi (TYPE_1__*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int shpc_readl (struct controller*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shpc_writel (struct controller*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  shpchp_num_controllers ; 
 scalar_t__ shpchp_poll_mode ; 
 int /*<<< orphan*/  shpchp_wq ; 

__attribute__((used)) static void hpc_release_ctlr(struct controller *ctrl)
{
	int i;
	u32 slot_reg, serr_int;

	/*
	 * Mask event interrupts and SERRs of all slots
	 */
	for (i = 0; i < ctrl->num_slots; i++) {
		slot_reg = shpc_readl(ctrl, SLOT_REG(i));
		slot_reg |= (PRSNT_CHANGE_INTR_MASK | ISO_PFAULT_INTR_MASK |
			     BUTTON_PRESS_INTR_MASK | MRL_CHANGE_INTR_MASK |
			     CON_PFAULT_INTR_MASK   | MRL_CHANGE_SERR_MASK |
			     CON_PFAULT_SERR_MASK);
		slot_reg &= ~SLOT_REG_RSVDZ_MASK;
		shpc_writel(ctrl, SLOT_REG(i), slot_reg);
	}

	cleanup_slots(ctrl);

	/*
	 * Mask SERR and System Interrupt generation
	 */
	serr_int = shpc_readl(ctrl, SERR_INTR_ENABLE);
	serr_int |= (GLOBAL_INTR_MASK  | GLOBAL_SERR_MASK |
		     COMMAND_INTR_MASK | ARBITER_SERR_MASK);
	serr_int &= ~SERR_INTR_RSVDZ_MASK;
	shpc_writel(ctrl, SERR_INTR_ENABLE, serr_int);

	if (shpchp_poll_mode)
		del_timer(&ctrl->poll_timer);
	else {
		free_irq(ctrl->pci_dev->irq, ctrl);
		pci_disable_msi(ctrl->pci_dev);
	}

	iounmap(ctrl->creg);
	release_mem_region(ctrl->mmio_base, ctrl->mmio_size);

	/*
	 * If this is the last controller to be released, destroy the
	 * shpchpd work queue
	 */
	if (atomic_dec_and_test(&shpchp_num_controllers))
		destroy_workqueue(shpchp_wq);
}