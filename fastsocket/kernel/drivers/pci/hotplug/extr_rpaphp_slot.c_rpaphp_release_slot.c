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
struct slot {int dummy; } ;
struct hotplug_slot {scalar_t__ private; } ;

/* Variables and functions */
 int /*<<< orphan*/  dealloc_slot_struct (struct slot*) ; 

__attribute__((used)) static void rpaphp_release_slot(struct hotplug_slot *hotplug_slot)
{
	struct slot *slot = (struct slot *) hotplug_slot->private;
	dealloc_slot_struct(slot);
}