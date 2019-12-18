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
typedef  int u32 ;
struct pci_device_id {int driver_data; int /*<<< orphan*/  member_0; } ;
struct pci_dev {TYPE_1__* bus; } ;
struct TYPE_2__ {struct pci_dev* self; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DEVICE (int,int) ; 
 int /*<<< orphan*/  PCI_VDEVICE (int /*<<< orphan*/  const,int) ; 
#define  PLX 128 
 struct pci_device_id* pci_match_id (struct pci_device_id const*,struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int,int) ; 

__attribute__((used)) static void configure_pcie_bridge(struct pci_dev *pci)
{
	enum { PEX811X, PI7C9X110 };
	static const struct pci_device_id bridge_ids[] = {
		{ PCI_VDEVICE(PLX, 0x8111), .driver_data = PEX811X },
		{ PCI_VDEVICE(PLX, 0x8112), .driver_data = PEX811X },
		{ PCI_DEVICE(0x12d8, 0xe110), .driver_data = PI7C9X110 },
		{ }
	};
	struct pci_dev *bridge;
	const struct pci_device_id *id;
	u32 tmp;

	if (!pci->bus || !pci->bus->self)
		return;
	bridge = pci->bus->self;

	id = pci_match_id(bridge_ids, bridge);
	if (!id)
		return;

	switch (id->driver_data) {
	case PEX811X:	/* PLX PEX8111/PEX8112 PCIe/PCI bridge */
		pci_read_config_dword(bridge, 0x48, &tmp);
		tmp |= 1;	/* enable blind prefetching */
		tmp |= 1 << 11;	/* enable beacon generation */
		pci_write_config_dword(bridge, 0x48, tmp);

		pci_write_config_dword(bridge, 0x84, 0x0c);
		pci_read_config_dword(bridge, 0x88, &tmp);
		tmp &= ~(7 << 27);
		tmp |= 2 << 27;	/* set prefetch size to 128 bytes */
		pci_write_config_dword(bridge, 0x88, tmp);
		break;

	case PI7C9X110:	/* Pericom PI7C9X110 PCIe/PCI bridge */
		pci_read_config_dword(bridge, 0x40, &tmp);
		tmp |= 1;	/* park the PCI arbiter to the sound chip */
		pci_write_config_dword(bridge, 0x40, tmp);
		break;
	}
}