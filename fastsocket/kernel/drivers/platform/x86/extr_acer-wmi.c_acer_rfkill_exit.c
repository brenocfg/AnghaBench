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
 int /*<<< orphan*/  ACER_CAP_BLUETOOTH ; 
 int /*<<< orphan*/  acer_rfkill_work ; 
 int /*<<< orphan*/  bluetooth_rfkill ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 scalar_t__ has_cap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfkill_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfkill_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wireless_rfkill ; 

__attribute__((used)) static void acer_rfkill_exit(void)
{
	cancel_delayed_work_sync(&acer_rfkill_work);

	rfkill_unregister(wireless_rfkill);
	rfkill_destroy(wireless_rfkill);

	if (has_cap(ACER_CAP_BLUETOOTH)) {
		rfkill_unregister(bluetooth_rfkill);
		rfkill_destroy(bluetooth_rfkill);
	}
	return;
}