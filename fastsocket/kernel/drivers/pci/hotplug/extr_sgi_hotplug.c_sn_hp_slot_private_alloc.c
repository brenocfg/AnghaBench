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
typedef  int u16 ;
struct slot {int device_num; int /*<<< orphan*/  hp_list; struct hotplug_slot* hotplug_slot; int /*<<< orphan*/  physical_path; struct pci_bus* pci_bus; } ;
struct TYPE_2__ {scalar_t__ bs_persist_busnum; } ;
struct pcibus_info {TYPE_1__ pbi_buscommon; } ;
struct pci_bus {int dummy; } ;
struct hotplug_slot {struct slot* private; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct pcibus_info* SN_PCIBUS_BUSSOFT_INFO (struct pci_bus*) ; 
 struct slot* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pci_domain_nr (struct pci_bus*) ; 
 int /*<<< orphan*/  sn_generate_path (struct pci_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sn_hp_list ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int) ; 

__attribute__((used)) static int sn_hp_slot_private_alloc(struct hotplug_slot *bss_hotplug_slot,
				    struct pci_bus *pci_bus, int device,
				    char *name)
{
	struct pcibus_info *pcibus_info;
	struct slot *slot;

	pcibus_info = SN_PCIBUS_BUSSOFT_INFO(pci_bus);

	slot = kzalloc(sizeof(*slot), GFP_KERNEL);
	if (!slot)
		return -ENOMEM;
	bss_hotplug_slot->private = slot;

	slot->device_num = device;
	slot->pci_bus = pci_bus;
	sprintf(name, "%04x:%02x:%02x",
		pci_domain_nr(pci_bus),
		((u16)pcibus_info->pbi_buscommon.bs_persist_busnum),
		device + 1);

	sn_generate_path(pci_bus, slot->physical_path);

	slot->hotplug_slot = bss_hotplug_slot;
	list_add(&slot->hp_list, &sn_hp_list);

	return 0;
}