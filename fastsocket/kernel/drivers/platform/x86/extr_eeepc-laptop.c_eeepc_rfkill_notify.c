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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_NOTIFY_BUS_CHECK ; 
 int /*<<< orphan*/  eeepc_rfkill_hotplug () ; 

__attribute__((used)) static void eeepc_rfkill_notify(acpi_handle handle, u32 event, void *data)
{
	if (event != ACPI_NOTIFY_BUS_CHECK)
		return;

	eeepc_rfkill_hotplug();
}