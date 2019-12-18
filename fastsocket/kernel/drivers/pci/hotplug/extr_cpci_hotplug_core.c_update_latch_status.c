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
typedef  int /*<<< orphan*/  u8 ;
struct hotplug_slot_info {int /*<<< orphan*/  latch_status; } ;
struct hotplug_slot {int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct hotplug_slot_info*,int /*<<< orphan*/ ,int) ; 
 int pci_hp_change_slot_info (struct hotplug_slot*,struct hotplug_slot_info*) ; 

__attribute__((used)) static int
update_latch_status(struct hotplug_slot *hotplug_slot, u8 value)
{
	struct hotplug_slot_info info;

	memcpy(&info, hotplug_slot->info, sizeof(struct hotplug_slot_info));
	info.latch_status = value;
	return pci_hp_change_slot_info(hotplug_slot, &info);
}