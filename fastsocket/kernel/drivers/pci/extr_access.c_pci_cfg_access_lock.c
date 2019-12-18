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
struct pci_dev {int block_ucfg_access; } ;

/* Variables and functions */
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  pci_lock ; 
 int /*<<< orphan*/  pci_wait_cfg (struct pci_dev*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void pci_cfg_access_lock(struct pci_dev *dev)
{
	might_sleep();

	spin_lock_irq(&pci_lock);
	if (dev->block_ucfg_access)
	    pci_wait_cfg(dev);
	dev->block_ucfg_access = 1;
	spin_unlock_irq(&pci_lock);
}