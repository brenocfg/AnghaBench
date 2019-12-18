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
 int /*<<< orphan*/  ACPI_VIDEO_CLASS ; 
 int /*<<< orphan*/  acpi_bus_unregister_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_root_dir ; 
 int /*<<< orphan*/  acpi_video_bus ; 
 scalar_t__ register_count ; 
 int /*<<< orphan*/  remove_proc_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void acpi_video_unregister(void)
{
	if (!register_count) {
		/*
		 * If the acpi video bus is already unloaded, don't
		 * unload it again and return directly.
		 */
		return;
	}
	acpi_bus_unregister_driver(&acpi_video_bus);

	remove_proc_entry(ACPI_VIDEO_CLASS, acpi_root_dir);

	register_count = 0;

	return;
}