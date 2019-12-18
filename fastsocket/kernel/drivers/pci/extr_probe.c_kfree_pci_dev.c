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
struct pci_dev {struct pci_dev* rh_reserved1; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct pci_dev*) ; 

void kfree_pci_dev(struct pci_dev *dev)
{
	kfree(dev->rh_reserved1);
	kfree(dev);
}