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
typedef  int /*<<< orphan*/  u32 ;
struct acpiphp_bridge {scalar_t__ type; int flags; int /*<<< orphan*/  handle; TYPE_1__* func; int /*<<< orphan*/  list; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SYSTEM_NOTIFY ; 
 int /*<<< orphan*/  ACPI_TYPE_DEVICE ; 
 int BRIDGE_HAS_EJ0 ; 
 scalar_t__ BRIDGE_TYPE_HOST ; 
 int /*<<< orphan*/  acpi_install_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpiphp_bridge*) ; 
 int /*<<< orphan*/  acpi_remove_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_walk_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpiphp_bridge*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bridge_list ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  handle_hotplug_event_bridge ; 
 int /*<<< orphan*/  handle_hotplug_event_func ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  register_slot ; 

__attribute__((used)) static void init_bridge_misc(struct acpiphp_bridge *bridge)
{
	acpi_status status;

	/* must be added to the list prior to calling register_slot */
	list_add(&bridge->list, &bridge_list);

	/* register all slot objects under this bridge */
	status = acpi_walk_namespace(ACPI_TYPE_DEVICE, bridge->handle, (u32)1,
				     register_slot, bridge, NULL);
	if (ACPI_FAILURE(status)) {
		list_del(&bridge->list);
		return;
	}

	/* install notify handler */
	if (bridge->type != BRIDGE_TYPE_HOST) {
		if ((bridge->flags & BRIDGE_HAS_EJ0) && bridge->func) {
			status = acpi_remove_notify_handler(bridge->func->handle,
						ACPI_SYSTEM_NOTIFY,
						handle_hotplug_event_func);
			if (ACPI_FAILURE(status))
				err("failed to remove notify handler\n");
		}
		status = acpi_install_notify_handler(bridge->handle,
					     ACPI_SYSTEM_NOTIFY,
					     handle_hotplug_event_bridge,
					     bridge);

		if (ACPI_FAILURE(status)) {
			err("failed to register interrupt notify handler\n");
		}
	}
}