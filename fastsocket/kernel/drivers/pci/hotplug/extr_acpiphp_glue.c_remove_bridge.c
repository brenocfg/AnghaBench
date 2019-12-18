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
struct acpiphp_bridge {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SYSTEM_NOTIFY ; 
 int /*<<< orphan*/  ACPI_TYPE_DEVICE ; 
 int /*<<< orphan*/  acpi_remove_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_walk_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct acpiphp_bridge* acpiphp_handle_to_bridge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_bridge (struct acpiphp_bridge*) ; 
 int /*<<< orphan*/  cleanup_p2p_bridge ; 
 int /*<<< orphan*/  handle_hotplug_event_bridge ; 

__attribute__((used)) static void remove_bridge(acpi_handle handle)
{
	struct acpiphp_bridge *bridge;

	/* cleanup p2p bridges under this host bridge
	   in a depth-first manner */
	acpi_walk_namespace(ACPI_TYPE_DEVICE, handle,
				(u32)1, cleanup_p2p_bridge, NULL, NULL);

	/*
	 * On root bridges with hotplug slots directly underneath (ie,
	 * no p2p bridge inbetween), we call cleanup_bridge(). 
	 *
	 * The else clause cleans up root bridges that either had no
	 * hotplug slots at all, or had a p2p bridge underneath.
	 */
	bridge = acpiphp_handle_to_bridge(handle);
	if (bridge)
		cleanup_bridge(bridge);
	else
		acpi_remove_notify_handler(handle, ACPI_SYSTEM_NOTIFY,
					   handle_hotplug_event_bridge);
}