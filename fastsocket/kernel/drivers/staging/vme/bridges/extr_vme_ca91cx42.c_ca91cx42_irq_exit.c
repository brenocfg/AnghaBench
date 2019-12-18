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
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ LINT_EN ; 
 scalar_t__ LINT_STAT ; 
 scalar_t__ VINT_EN ; 
 TYPE_1__* ca91cx42_bridge ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct pci_dev*) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 

__attribute__((used)) static void ca91cx42_irq_exit(struct pci_dev *pdev)
{
	/* Disable interrupts from PCI to VME */
	iowrite32(0, ca91cx42_bridge->base + VINT_EN);

	/* Disable PCI interrupts */
	iowrite32(0, ca91cx42_bridge->base + LINT_EN);
	/* Clear Any Pending PCI Interrupts */
	iowrite32(0x00FFFFFF, ca91cx42_bridge->base + LINT_STAT);

	free_irq(pdev->irq, pdev);
}