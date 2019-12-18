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
struct pci_dev {int /*<<< orphan*/  is_physfn; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ sriov_migration (struct pci_dev*) ; 

irqreturn_t pci_sriov_migration(struct pci_dev *dev)
{
	if (!dev->is_physfn)
		return IRQ_NONE;

	return sriov_migration(dev) ? IRQ_HANDLED : IRQ_NONE;
}