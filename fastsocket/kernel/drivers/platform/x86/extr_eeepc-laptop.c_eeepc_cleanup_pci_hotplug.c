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
struct hotplug_slot {struct hotplug_slot* info; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct hotplug_slot*) ; 

__attribute__((used)) static void eeepc_cleanup_pci_hotplug(struct hotplug_slot *hotplug_slot)
{
	kfree(hotplug_slot->info);
	kfree(hotplug_slot);
}