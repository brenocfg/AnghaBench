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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int ixgbe_pci_sriov_disable (struct pci_dev*) ; 
 int ixgbe_pci_sriov_enable (struct pci_dev*,int) ; 

int ixgbe_pci_sriov_configure(struct pci_dev *dev, int num_vfs)
{
	if (num_vfs == 0)
		return ixgbe_pci_sriov_disable(dev);
	else
		return ixgbe_pci_sriov_enable(dev, num_vfs);
}