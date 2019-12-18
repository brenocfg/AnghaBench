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
struct TYPE_2__ {int /*<<< orphan*/ * wimax_rfkill; int /*<<< orphan*/ * wwan3g_rfkill; int /*<<< orphan*/ * bluetooth_rfkill; scalar_t__ hotplug_slot; int /*<<< orphan*/ * wlan_rfkill; } ;

/* Variables and functions */
 int /*<<< orphan*/  eeepc_rfkill_hotplug () ; 
 int /*<<< orphan*/  eeepc_unregister_rfkill_notifier (char*) ; 
 TYPE_1__* ehotk ; 
 int /*<<< orphan*/  pci_hp_deregister (scalar_t__) ; 
 int /*<<< orphan*/  rfkill_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfkill_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void eeepc_rfkill_exit(void)
{
	eeepc_unregister_rfkill_notifier("\\_SB.PCI0.P0P5");
	eeepc_unregister_rfkill_notifier("\\_SB.PCI0.P0P6");
	eeepc_unregister_rfkill_notifier("\\_SB.PCI0.P0P7");
	if (ehotk->wlan_rfkill) {
		rfkill_unregister(ehotk->wlan_rfkill);
		rfkill_destroy(ehotk->wlan_rfkill);
		ehotk->wlan_rfkill = NULL;
	}
	/*
	 * Refresh pci hotplug in case the rfkill state was changed after
	 * eeepc_unregister_rfkill_notifier()
	 */
	eeepc_rfkill_hotplug();
	if (ehotk->hotplug_slot)
		pci_hp_deregister(ehotk->hotplug_slot);

	if (ehotk->bluetooth_rfkill) {
		rfkill_unregister(ehotk->bluetooth_rfkill);
		rfkill_destroy(ehotk->bluetooth_rfkill);
		ehotk->bluetooth_rfkill = NULL;
	}
	if (ehotk->wwan3g_rfkill) {
		rfkill_unregister(ehotk->wwan3g_rfkill);
		rfkill_destroy(ehotk->wwan3g_rfkill);
		ehotk->wwan3g_rfkill = NULL;
	}
	if (ehotk->wimax_rfkill) {
		rfkill_unregister(ehotk->wimax_rfkill);
		rfkill_destroy(ehotk->wimax_rfkill);
		ehotk->wimax_rfkill = NULL;
	}
}