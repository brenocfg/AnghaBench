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
struct pci_devres {scalar_t__ enabled; } ;
struct pci_dev {scalar_t__ is_busmaster; int /*<<< orphan*/  enable_cnt; } ;

/* Variables and functions */
 scalar_t__ atomic_sub_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_pci_disable_device (struct pci_dev*) ; 
 struct pci_devres* find_pci_dr (struct pci_dev*) ; 

void
pci_disable_device(struct pci_dev *dev)
{
	struct pci_devres *dr;

	dr = find_pci_dr(dev);
	if (dr)
		dr->enabled = 0;

	if (atomic_sub_return(1, &dev->enable_cnt) != 0)
		return;

	do_pci_disable_device(dev);

	dev->is_busmaster = 0;
}