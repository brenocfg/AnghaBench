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
struct slot {int number; TYPE_1__* hotplug_slot; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLOT_NAME_SIZE ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void make_slot_name(struct slot *slot)
{
	/*
	 * Stupid way to make a filename out of the slot name.
	 * replace this if your hardware provides a better way to name slots.
	 */
	snprintf(slot->hotplug_slot->name, SLOT_NAME_SIZE, "%d", slot->number);
}