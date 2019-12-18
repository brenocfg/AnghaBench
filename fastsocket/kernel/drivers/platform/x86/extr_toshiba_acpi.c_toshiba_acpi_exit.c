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
struct TYPE_2__ {int /*<<< orphan*/  p_dev; scalar_t__ bt_rfk; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_TOSHIBA ; 
 int /*<<< orphan*/  acpi_root_dir ; 
 int /*<<< orphan*/  backlight_device_unregister (scalar_t__) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_device () ; 
 int /*<<< orphan*/  remove_proc_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfkill_destroy (scalar_t__) ; 
 int /*<<< orphan*/  rfkill_unregister (scalar_t__) ; 
 TYPE_1__ toshiba_acpi ; 
 scalar_t__ toshiba_backlight_device ; 
 scalar_t__ toshiba_proc_dir ; 

__attribute__((used)) static void toshiba_acpi_exit(void)
{
	if (toshiba_acpi.bt_rfk) {
		rfkill_unregister(toshiba_acpi.bt_rfk);
		rfkill_destroy(toshiba_acpi.bt_rfk);
	}

	if (toshiba_backlight_device)
		backlight_device_unregister(toshiba_backlight_device);

	remove_device();

	if (toshiba_proc_dir)
		remove_proc_entry(PROC_TOSHIBA, acpi_root_dir);

	platform_device_unregister(toshiba_acpi.p_dev);

	return;
}