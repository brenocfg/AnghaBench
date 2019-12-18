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
typedef  int u16 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_EXP_DEVCTL2 ; 
 int PCI_EXP_IDO_CMP_EN ; 
 unsigned long PCI_EXP_IDO_COMPLETION ; 
 unsigned long PCI_EXP_IDO_REQUEST ; 
 int PCI_EXP_IDO_REQ_EN ; 
 int /*<<< orphan*/  pcie_capability_set_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 

void pci_enable_ido(struct pci_dev *dev, unsigned long type)
{
	u16 ctrl = 0;

	if (type & PCI_EXP_IDO_REQUEST)
		ctrl |= PCI_EXP_IDO_REQ_EN;
	if (type & PCI_EXP_IDO_COMPLETION)
		ctrl |= PCI_EXP_IDO_CMP_EN;
	if (ctrl)
		pcie_capability_set_word(dev, PCI_EXP_DEVCTL2, ctrl);
}