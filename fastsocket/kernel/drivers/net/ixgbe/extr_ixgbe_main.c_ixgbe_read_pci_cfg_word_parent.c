#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int dummy; } ;
struct pci_bus {struct pci_dev* self; } ;
struct ixgbe_adapter {TYPE_2__* pdev; } ;
struct TYPE_4__ {TYPE_1__* bus; } ;
struct TYPE_3__ {struct pci_bus* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_CAP_ID_EXP ; 
 int pci_find_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ixgbe_read_pci_cfg_word_parent(struct ixgbe_adapter *adapter,
					  u32 reg, u16 *value)
{
	int pos = 0;
	struct pci_dev *parent_dev;
	struct pci_bus *parent_bus;

	parent_bus = adapter->pdev->bus->parent;
	if (!parent_bus)
		return -1;

	parent_dev = parent_bus->self;
	if (!parent_dev)
		return -1;

	pos = pci_find_capability(parent_dev, PCI_CAP_ID_EXP);
	if (!pos)
		return -1;

	pci_read_config_word(parent_dev, pos + reg, value);
	return 0;
}