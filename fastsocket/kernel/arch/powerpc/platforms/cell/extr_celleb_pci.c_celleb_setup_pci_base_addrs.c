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
struct pci_controller {int dummy; } ;
struct celleb_pci_resource {TYPE_1__* r; } ;
struct TYPE_2__ {int start; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_BASE_ADDRESS_0 ; 
 int /*<<< orphan*/  PCI_BASE_ADDRESS_1 ; 
 int /*<<< orphan*/  PCI_BASE_ADDRESS_2 ; 
 int /*<<< orphan*/  PCI_BASE_ADDRESS_3 ; 
 int /*<<< orphan*/  PCI_BASE_ADDRESS_4 ; 
 int /*<<< orphan*/  PCI_BASE_ADDRESS_5 ; 
 int PCI_BASE_ADDRESS_MEM_TYPE_64 ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int PCI_COMMAND_IO ; 
 int PCI_COMMAND_MASTER ; 
 int PCI_COMMAND_MEMORY ; 
 int /*<<< orphan*/  celleb_config_write_fake (unsigned char*,int /*<<< orphan*/ ,int,int) ; 
 unsigned char* get_fake_config_start (struct pci_controller*,unsigned int,unsigned int) ; 
 struct celleb_pci_resource* get_resource_start (struct pci_controller*,unsigned int,unsigned int) ; 

__attribute__((used)) static inline void celleb_setup_pci_base_addrs(struct pci_controller *hose,
					unsigned int devno, unsigned int fn,
					unsigned int num_base_addr)
{
	u32 val;
	unsigned char *config;
	struct celleb_pci_resource *res;

	config = get_fake_config_start(hose, devno, fn);
	res = get_resource_start(hose, devno, fn);

	if (!config || !res)
		return;

	switch (num_base_addr) {
	case 3:
		val = (res->r[2].start & 0xfffffff0)
		    | PCI_BASE_ADDRESS_MEM_TYPE_64;
		celleb_config_write_fake(config, PCI_BASE_ADDRESS_4, 4, val);
		val = res->r[2].start >> 32;
		celleb_config_write_fake(config, PCI_BASE_ADDRESS_5, 4, val);
		/* FALLTHROUGH */
	case 2:
		val = (res->r[1].start & 0xfffffff0)
		    | PCI_BASE_ADDRESS_MEM_TYPE_64;
		celleb_config_write_fake(config, PCI_BASE_ADDRESS_2, 4, val);
		val = res->r[1].start >> 32;
		celleb_config_write_fake(config, PCI_BASE_ADDRESS_3, 4, val);
		/* FALLTHROUGH */
	case 1:
		val = (res->r[0].start & 0xfffffff0)
		    | PCI_BASE_ADDRESS_MEM_TYPE_64;
		celleb_config_write_fake(config, PCI_BASE_ADDRESS_0, 4, val);
		val = res->r[0].start >> 32;
		celleb_config_write_fake(config, PCI_BASE_ADDRESS_1, 4, val);
		break;
	}

	val = PCI_COMMAND_IO | PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER;
	celleb_config_write_fake(config, PCI_COMMAND, 2, val);
}