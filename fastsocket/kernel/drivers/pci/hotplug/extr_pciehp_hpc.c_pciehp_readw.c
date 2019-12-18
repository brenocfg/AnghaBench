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
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int dummy; } ;
struct controller {TYPE_1__* pcie; } ;
struct TYPE_2__ {struct pci_dev* port; } ;

/* Variables and functions */
 int pcie_capability_read_word (struct pci_dev*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int pciehp_readw(struct controller *ctrl, int reg, u16 *value)
{
	struct pci_dev *dev = ctrl->pcie->port;
	return pcie_capability_read_word(dev, reg, value);
}