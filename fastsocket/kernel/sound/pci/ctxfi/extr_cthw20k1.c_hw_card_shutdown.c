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
struct hw {int irq; long mem_base; int /*<<< orphan*/  pci; scalar_t__ io_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int,struct hw*) ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hw_card_shutdown(struct hw *hw)
{
	if (hw->irq >= 0)
		free_irq(hw->irq, hw);

	hw->irq	= -1;

	if (hw->mem_base)
		iounmap((void *)hw->mem_base);

	hw->mem_base = (unsigned long)NULL;

	if (hw->io_base)
		pci_release_regions(hw->pci);

	hw->io_base = 0;

	pci_disable_device(hw->pci);

	return 0;
}