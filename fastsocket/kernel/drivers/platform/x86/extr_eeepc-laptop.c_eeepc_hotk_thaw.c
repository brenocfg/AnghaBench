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
struct TYPE_2__ {scalar_t__ wlan_rfkill; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_ASL_WLAN ; 
 TYPE_1__* ehotk ; 
 int get_acpi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_acpi (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int eeepc_hotk_thaw(struct device *device)
{
	if (ehotk->wlan_rfkill) {
		bool wlan;

		/*
		 * Work around bios bug - acpi _PTS turns off the wireless led
		 * during suspend.  Normally it restores it on resume, but
		 * we should kick it ourselves in case hibernation is aborted.
		 */
		wlan = get_acpi(CM_ASL_WLAN);
		set_acpi(CM_ASL_WLAN, wlan);
	}

	return 0;
}