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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct TYPE_2__ {scalar_t__ bs_asic_type; } ;
struct pcibus_info {TYPE_1__ pbi_buscommon; } ;
struct pci_bus {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int EPERM ; 
#define  L1_BOARDTYPE_PCIX3SLOT 132 
#define  L1_BRICKTYPE_IA 131 
#define  L1_BRICKTYPE_IX 130 
#define  L1_BRICKTYPE_PA 129 
#define  L1_BRICKTYPE_PX 128 
 scalar_t__ PCIIO_ASIC_TYPE_TIOCA ; 
 struct pcibus_info* SN_PCIBUS_BUSSOFT_INFO (struct pci_bus*) ; 
 int sn_ioboard_to_pci_bus (struct pci_bus*) ; 

__attribute__((used)) static int sn_pci_bus_valid(struct pci_bus *pci_bus)
{
	struct pcibus_info *pcibus_info;
	u32 asic_type;
	u16 ioboard_type;

	/* Don't register slots hanging off the TIOCA bus */
	pcibus_info = SN_PCIBUS_BUSSOFT_INFO(pci_bus);
	asic_type = pcibus_info->pbi_buscommon.bs_asic_type;
	if (asic_type == PCIIO_ASIC_TYPE_TIOCA)
		return -EPERM;

	/* Only register slots in I/O Bricks that support hotplug */
	ioboard_type = sn_ioboard_to_pci_bus(pci_bus);
	switch (ioboard_type) {
		case L1_BRICKTYPE_IX:
		case L1_BRICKTYPE_PX:
		case L1_BRICKTYPE_IA:
		case L1_BRICKTYPE_PA:
		case L1_BOARDTYPE_PCIX3SLOT:
			return 1;
			break;
		default:
			return -EPERM;
			break;
	}

	return -EIO;
}