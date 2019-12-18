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
typedef  int u16 ;
struct pci_dev {int /*<<< orphan*/  devfn; struct pci_bus* bus; } ;
struct pci_bus {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* write ) (struct pci_bus*,int /*<<< orphan*/ ,int,int,int) ;int /*<<< orphan*/  (* read ) (struct pci_bus*,int /*<<< orphan*/ ,int,int,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int PCI_COMMAND ; 
 int PCI_COMMAND_INTX_DISABLE ; 
 int PCI_STATUS ; 
 int PCI_STATUS_INTERRUPT ; 
 int /*<<< orphan*/  pci_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct pci_bus*,int /*<<< orphan*/ ,int,int,int*) ; 
 int /*<<< orphan*/  stub2 (struct pci_bus*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static bool pci_check_and_set_intx_mask(struct pci_dev *dev, bool mask)
{
	struct pci_bus *bus = dev->bus;
	bool mask_updated = true;
	u32 cmd_status_dword;
	u16 origcmd, newcmd;
	unsigned long flags;
	bool irq_pending;

	/*
	 * We do a single dword read to retrieve both command and status.
	 * Document assumptions that make this possible.
	 */
	BUILD_BUG_ON(PCI_COMMAND % 4);
	BUILD_BUG_ON(PCI_COMMAND + 2 != PCI_STATUS);

	spin_lock_irqsave(&pci_lock, flags);

	bus->ops->read(bus, dev->devfn, PCI_COMMAND, 4, &cmd_status_dword);

	irq_pending = (cmd_status_dword >> 16) & PCI_STATUS_INTERRUPT;

	/*
	 * Check interrupt status register to see whether our device
	 * triggered the interrupt (when masking) or the next IRQ is
	 * already pending (when unmasking).
	 */
	if (mask != irq_pending) {
		mask_updated = false;
		goto done;
	}

	origcmd = cmd_status_dword;
	newcmd = origcmd & ~PCI_COMMAND_INTX_DISABLE;
	if (mask)
		newcmd |= PCI_COMMAND_INTX_DISABLE;
	if (newcmd != origcmd)
		bus->ops->write(bus, dev->devfn, PCI_COMMAND, 2, newcmd);

done:
	spin_unlock_irqrestore(&pci_lock, flags);

	return mask_updated;
}