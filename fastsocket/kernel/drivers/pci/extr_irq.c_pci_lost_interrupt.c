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
struct pci_dev {scalar_t__ msix_enabled; scalar_t__ msi_enabled; } ;
typedef  enum pci_lost_interrupt_reason { ____Placeholder_pci_lost_interrupt_reason } pci_lost_interrupt_reason ;

/* Variables and functions */
 int PCI_LOST_IRQ_DISABLE_ACPI ; 
 int PCI_LOST_IRQ_DISABLE_MSI ; 
 int PCI_LOST_IRQ_DISABLE_MSIX ; 
 int PCI_LOST_IRQ_NO_INFORMATION ; 
 scalar_t__ acpi_disabled ; 
 scalar_t__ acpi_noirq ; 
 int /*<<< orphan*/  pci_note_irq_problem (struct pci_dev*,char*) ; 

enum pci_lost_interrupt_reason pci_lost_interrupt(struct pci_dev *pdev)
{
	if (pdev->msi_enabled || pdev->msix_enabled) {
		enum pci_lost_interrupt_reason ret;

		if (pdev->msix_enabled) {
			pci_note_irq_problem(pdev, "MSIX routing failure");
			ret = PCI_LOST_IRQ_DISABLE_MSIX;
		} else {
			pci_note_irq_problem(pdev, "MSI routing failure");
			ret = PCI_LOST_IRQ_DISABLE_MSI;
		}
		return ret;
	}
#ifdef CONFIG_ACPI
	if (!(acpi_disabled || acpi_noirq)) {
		pci_note_irq_problem(pdev, "Potential ACPI misrouting please reboot with acpi=noirq");
		/* currently no way to fix acpi on the fly */
		return PCI_LOST_IRQ_DISABLE_ACPI;
	}
#endif
	pci_note_irq_problem(pdev, "unknown cause (not MSI or ACPI)");
	return PCI_LOST_IRQ_NO_INFORMATION;
}