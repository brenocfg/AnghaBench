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
 int /*<<< orphan*/  PROC_ASUS ; 
 int /*<<< orphan*/  acpi_bus_unregister_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_root_dir ; 
 scalar_t__ asus_backlight_device ; 
 int /*<<< orphan*/  asus_hotk_driver ; 
 int /*<<< orphan*/  backlight_device_unregister (scalar_t__) ; 
 int /*<<< orphan*/  remove_proc_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asus_acpi_exit(void)
{
	if (asus_backlight_device)
		backlight_device_unregister(asus_backlight_device);

	acpi_bus_unregister_driver(&asus_hotk_driver);
	remove_proc_entry(PROC_ASUS, acpi_root_dir);

	return;
}