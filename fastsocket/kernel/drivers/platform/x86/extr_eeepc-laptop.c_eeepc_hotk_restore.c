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
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ wimax_rfkill; scalar_t__ wwan3g_rfkill; scalar_t__ bluetooth_rfkill; scalar_t__ wlan_rfkill; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_ASL_3G ; 
 int /*<<< orphan*/  CM_ASL_BLUETOOTH ; 
 int /*<<< orphan*/  CM_ASL_WIMAX ; 
 int /*<<< orphan*/  eeepc_rfkill_hotplug () ; 
 TYPE_1__* ehotk ; 
 int get_acpi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfkill_set_sw_state (scalar_t__,int) ; 

__attribute__((used)) static int eeepc_hotk_restore(struct device *device)
{
	/* Refresh both wlan rfkill state and pci hotplug */
	if (ehotk->wlan_rfkill)
		eeepc_rfkill_hotplug();

	if (ehotk->bluetooth_rfkill)
		rfkill_set_sw_state(ehotk->bluetooth_rfkill,
				    get_acpi(CM_ASL_BLUETOOTH) != 1);
	if (ehotk->wwan3g_rfkill)
		rfkill_set_sw_state(ehotk->wwan3g_rfkill,
				    get_acpi(CM_ASL_3G) != 1);
	if (ehotk->wimax_rfkill)
		rfkill_set_sw_state(ehotk->wimax_rfkill,
				    get_acpi(CM_ASL_WIMAX) != 1);

	return 0;
}