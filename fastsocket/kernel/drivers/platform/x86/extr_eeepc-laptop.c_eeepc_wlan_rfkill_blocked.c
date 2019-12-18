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

/* Variables and functions */
 int /*<<< orphan*/  CM_ASL_WLAN ; 
 int get_acpi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool eeepc_wlan_rfkill_blocked(void)
{
	if (get_acpi(CM_ASL_WLAN) == 1)
		return false;
	return true;
}