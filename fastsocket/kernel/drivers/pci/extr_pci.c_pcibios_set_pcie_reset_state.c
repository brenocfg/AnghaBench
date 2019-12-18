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
typedef  enum pcie_reset_state { ____Placeholder_pcie_reset_state } pcie_reset_state ;

/* Variables and functions */
 int EINVAL ; 

int __attribute__ ((weak)) pcibios_set_pcie_reset_state(struct pci_dev *dev,
							enum pcie_reset_state state)
{
	return -EINVAL;
}