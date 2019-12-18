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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SYSTEM_NOTIFY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_install_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ acpi_is_root_bridge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_hotplug_event_bridge ; 

__attribute__((used)) static acpi_status
find_root_bridges(acpi_handle handle, u32 lvl, void *context, void **rv)
{
	int *count = (int *)context;

	if (acpi_is_root_bridge(handle)) {
		acpi_install_notify_handler(handle, ACPI_SYSTEM_NOTIFY,
				handle_hotplug_event_bridge, NULL);
			(*count)++;
	}
	return AE_OK ;
}