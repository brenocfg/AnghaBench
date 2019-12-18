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
struct pci_slot {int /*<<< orphan*/  kobj; } ;
struct pci_bus {TYPE_1__* self; } ;
struct hotplug_slot_info {int dummy; } ;
struct hotplug_slot {struct pci_slot* pci_slot; int /*<<< orphan*/  (* release ) (struct hotplug_slot*) ;int /*<<< orphan*/ * ops; void* info; } ;
struct TYPE_4__ {int /*<<< orphan*/  attr; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SN_MAX_HP_SLOTS ; 
 int SN_SLOT_NAME_SIZE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_hp_deregister (struct hotplug_slot*) ; 
 int pci_hp_register (struct hotplug_slot*,struct pci_bus*,int,char*) ; 
 int /*<<< orphan*/  sn_hotplug_slot_ops ; 
 struct hotplug_slot* sn_hp_destroy () ; 
 scalar_t__ sn_hp_slot_private_alloc (struct hotplug_slot*,struct pci_bus*,int,char*) ; 
 int sn_pci_slot_valid (struct pci_bus*,int) ; 
 int /*<<< orphan*/  sn_release_slot (struct hotplug_slot*) ; 
 TYPE_2__ sn_slot_path_attr ; 
 int sysfs_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sn_hotplug_slot_register(struct pci_bus *pci_bus)
{
	int device;
	struct pci_slot *pci_slot;
	struct hotplug_slot *bss_hotplug_slot;
	char name[SN_SLOT_NAME_SIZE];
	int rc = 0;

	/*
	 * Currently only four devices are supported,
	 * in the future there maybe more -- up to 32.
	 */

	for (device = 0; device < SN_MAX_HP_SLOTS ; device++) {
		if (sn_pci_slot_valid(pci_bus, device) != 1)
			continue;

		bss_hotplug_slot = kzalloc(sizeof(*bss_hotplug_slot),
					   GFP_KERNEL);
		if (!bss_hotplug_slot) {
			rc = -ENOMEM;
			goto alloc_err;
		}

		bss_hotplug_slot->info =
			kzalloc(sizeof(struct hotplug_slot_info),
				GFP_KERNEL);
		if (!bss_hotplug_slot->info) {
			rc = -ENOMEM;
			goto alloc_err;
		}

		if (sn_hp_slot_private_alloc(bss_hotplug_slot,
					     pci_bus, device, name)) {
			rc = -ENOMEM;
			goto alloc_err;
		}
		bss_hotplug_slot->ops = &sn_hotplug_slot_ops;
		bss_hotplug_slot->release = &sn_release_slot;

		rc = pci_hp_register(bss_hotplug_slot, pci_bus, device, name);
		if (rc)
			goto register_err;

		pci_slot = bss_hotplug_slot->pci_slot;
		rc = sysfs_create_file(&pci_slot->kobj,
				       &sn_slot_path_attr.attr);
		if (rc)
			goto register_err;
	}
	dev_dbg(&pci_bus->self->dev, "Registered bus with hotplug\n");
	return rc;

register_err:
	dev_dbg(&pci_bus->self->dev, "bus failed to register with err = %d\n",
		rc);

alloc_err:
	if (rc == -ENOMEM)
		dev_dbg(&pci_bus->self->dev, "Memory allocation error\n");

	/* destroy THIS element */
	if (bss_hotplug_slot)
		sn_release_slot(bss_hotplug_slot);

	/* destroy anything else on the list */
	while ((bss_hotplug_slot = sn_hp_destroy()))
		pci_hp_deregister(bss_hotplug_slot);

	return rc;
}