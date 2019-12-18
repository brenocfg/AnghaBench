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
struct pci_slot {int /*<<< orphan*/ * hotplug; } ;
struct hotplug_slot {int /*<<< orphan*/  (* release ) (struct hotplug_slot*) ;struct pci_slot* pci_slot; int /*<<< orphan*/  slot_list; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_remove_slot (struct pci_slot*) ; 
 struct hotplug_slot* get_slot_from_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hotplug_slot_name (struct hotplug_slot*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_destroy_slot (struct pci_slot*) ; 
 int /*<<< orphan*/  pci_hp_mutex ; 
 int /*<<< orphan*/  stub1 (struct hotplug_slot*) ; 

int pci_hp_deregister(struct hotplug_slot *hotplug)
{
	struct hotplug_slot *temp;
	struct pci_slot *slot;

	if (!hotplug)
		return -ENODEV;

	mutex_lock(&pci_hp_mutex);
	temp = get_slot_from_name(hotplug_slot_name(hotplug));
	if (temp != hotplug) {
		mutex_unlock(&pci_hp_mutex);
		return -ENODEV;
	}

	list_del(&hotplug->slot_list);

	slot = hotplug->pci_slot;
	fs_remove_slot(slot);
	dbg("Removed slot %s from the list\n", hotplug_slot_name(hotplug));

	hotplug->release(hotplug);
	slot->hotplug = NULL;
	pci_destroy_slot(slot);
	mutex_unlock(&pci_hp_mutex);

	return 0;
}