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
typedef  int u8 ;
struct slot {int /*<<< orphan*/  power_domain; } ;
struct hotplug_slot {scalar_t__ private; } ;

/* Variables and functions */
 int rtas_get_power_level (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int get_power_status(struct hotplug_slot *hotplug_slot, u8 * value)
{
	int retval, level;
	struct slot *slot = (struct slot *)hotplug_slot->private;

	retval = rtas_get_power_level (slot->power_domain, &level);
	if (!retval)
		*value = level;
	return retval;
}