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
struct pci_slot {int /*<<< orphan*/  kobj; struct hotplug_slot* hotplug; } ;
struct pci_bus {int dummy; } ;
struct module {int dummy; } ;
struct hotplug_slot {int /*<<< orphan*/  slot_list; struct pci_slot* pci_slot; TYPE_1__* ops; int /*<<< orphan*/ * release; int /*<<< orphan*/ * info; } ;
struct TYPE_2__ {char const* mod_name; struct module* owner; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct pci_slot*) ; 
 int /*<<< orphan*/  KOBJ_ADD ; 
 int PTR_ERR (struct pci_slot*) ; 
 int /*<<< orphan*/  dbg (char*,...) ; 
 int fs_add_slot (struct pci_slot*) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct pci_slot* pci_create_slot (struct pci_bus*,int,char const*,struct hotplug_slot*) ; 
 int /*<<< orphan*/  pci_hotplug_slot_list ; 
 int /*<<< orphan*/  pci_hp_mutex ; 

int __pci_hp_register(struct hotplug_slot *slot, struct pci_bus *bus,
		      int devnr, const char *name,
		      struct module *owner, const char *mod_name)
{
	int result;
	struct pci_slot *pci_slot;

	if (slot == NULL)
		return -ENODEV;
	if ((slot->info == NULL) || (slot->ops == NULL))
		return -EINVAL;
	if (slot->release == NULL) {
		dbg("Why are you trying to register a hotplug slot "
		    "without a proper release function?\n");
		return -EINVAL;
	}

	slot->ops->owner = owner;
	slot->ops->mod_name = mod_name;

	mutex_lock(&pci_hp_mutex);
	/*
	 * No problems if we call this interface from both ACPI_PCI_SLOT
	 * driver and call it here again. If we've already created the
	 * pci_slot, the interface will simply bump the refcount.
	 */
	pci_slot = pci_create_slot(bus, devnr, name, slot);
	if (IS_ERR(pci_slot)) {
		result = PTR_ERR(pci_slot);
		goto out;
	}

	slot->pci_slot = pci_slot;
	pci_slot->hotplug = slot;

	list_add(&slot->slot_list, &pci_hotplug_slot_list);

	result = fs_add_slot(pci_slot);
	kobject_uevent(&pci_slot->kobj, KOBJ_ADD);
	dbg("Added slot %s to the list\n", name);
out:
	mutex_unlock(&pci_hp_mutex);
	return result;
}