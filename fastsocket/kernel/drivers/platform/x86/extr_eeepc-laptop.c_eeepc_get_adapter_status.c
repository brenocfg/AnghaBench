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
struct hotplug_slot {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_ASL_WLAN ; 
 int EINVAL ; 
 int get_acpi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int eeepc_get_adapter_status(struct hotplug_slot *hotplug_slot,
				    u8 *value)
{
	int val = get_acpi(CM_ASL_WLAN);

	if (val == 1 || val == 0)
		*value = val;
	else
		return -EINVAL;

	return 0;
}