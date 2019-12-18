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
struct pci_controller {int /*<<< orphan*/ * cfg_addr; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  pciex_check_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

__attribute__((used)) static irqreturn_t pciex_handle_internal_irq(int irq, void *dev_id)
{
	struct pci_controller *phb = dev_id;

	pr_debug("PCIEX:pciex_handle_internal_irq(irq=%d)\n", irq);

	BUG_ON(phb->cfg_addr == NULL);

	pciex_check_status(phb->cfg_addr);

	return IRQ_HANDLED;
}