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
 int /*<<< orphan*/  pci_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

bool pci_cfg_access_trylock(struct pci_dev *dev)
 {
	unsigned long flags;
	bool locked = true;

	spin_lock_irqsave(&pci_lock, flags);
	if (dev->block_ucfg_access)
		locked = false;
	else
		dev->block_ucfg_access = 1;
	spin_unlock_irqrestore(&pci_lock, flags);

	return locked;
}