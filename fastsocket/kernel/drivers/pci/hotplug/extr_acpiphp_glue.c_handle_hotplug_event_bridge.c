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
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  _handle_hotplug_event_bridge ; 
 int /*<<< orphan*/  alloc_acpiphp_hp_work (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_hotplug_event_bridge(acpi_handle handle, u32 type,
					void *context)
{
	/*
	 * Currently the code adds all hotplug events to the kacpid_wq
	 * queue when it should add hotplug events to the kacpi_hotplug_wq.
	 * The proper way to fix this is to reorganize the code so that
	 * drivers (dock, etc.) do not call acpi_os_execute(), etc.
	 * For now just re-add this work to the kacpi_hotplug_wq so we
	 * don't deadlock on hotplug actions.
	 */
	alloc_acpiphp_hp_work(handle, type, context,
			      _handle_hotplug_event_bridge);
}