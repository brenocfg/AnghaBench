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
struct slot {struct slot* hotplug_slot; struct slot* name; struct slot* info; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct slot*) ; 

void dealloc_slot_struct(struct slot *slot)
{
	kfree(slot->hotplug_slot->info);
	kfree(slot->name);
	kfree(slot->hotplug_slot);
	kfree(slot);
}