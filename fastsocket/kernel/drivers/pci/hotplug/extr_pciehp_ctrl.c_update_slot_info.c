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
struct slot {int /*<<< orphan*/  hotplug_slot; } ;
struct hotplug_slot_info {int /*<<< orphan*/  adapter_status; int /*<<< orphan*/  latch_status; int /*<<< orphan*/  attention_status; int /*<<< orphan*/  power_status; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct hotplug_slot_info*) ; 
 struct hotplug_slot_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int pci_hp_change_slot_info (int /*<<< orphan*/ ,struct hotplug_slot_info*) ; 
 int /*<<< orphan*/  pciehp_get_adapter_status (struct slot*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pciehp_get_attention_status (struct slot*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pciehp_get_latch_status (struct slot*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pciehp_get_power_status (struct slot*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int update_slot_info(struct slot *slot)
{
	struct hotplug_slot_info *info;
	int result;

	info = kmalloc(sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	pciehp_get_power_status(slot, &info->power_status);
	pciehp_get_attention_status(slot, &info->attention_status);
	pciehp_get_latch_status(slot, &info->latch_status);
	pciehp_get_adapter_status(slot, &info->adapter_status);

	result = pci_hp_change_slot_info(slot->hotplug_slot, info);
	kfree (info);
	return result;
}