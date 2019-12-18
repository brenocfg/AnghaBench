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
struct acpiphp_func {struct acpiphp_bridge* bridge; } ;
struct acpiphp_bridge {int flags; struct acpiphp_func* func; int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int BRIDGE_HAS_EJ0 ; 
 int BRIDGE_HAS_PS0 ; 
 int BRIDGE_HAS_PS3 ; 
 int BRIDGE_HAS_STA ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 struct acpiphp_func* acpiphp_bridge_handle_to_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg (char*) ; 

__attribute__((used)) static inline void config_p2p_bridge_flags(struct acpiphp_bridge *bridge)
{
	acpi_handle dummy_handle;

	if (ACPI_SUCCESS(acpi_get_handle(bridge->handle,
					"_STA", &dummy_handle)))
		bridge->flags |= BRIDGE_HAS_STA;

	if (ACPI_SUCCESS(acpi_get_handle(bridge->handle,
					"_EJ0", &dummy_handle)))
		bridge->flags |= BRIDGE_HAS_EJ0;

	if (ACPI_SUCCESS(acpi_get_handle(bridge->handle,
					"_PS0", &dummy_handle)))
		bridge->flags |= BRIDGE_HAS_PS0;

	if (ACPI_SUCCESS(acpi_get_handle(bridge->handle,
					"_PS3", &dummy_handle)))
		bridge->flags |= BRIDGE_HAS_PS3;

	/* is this ejectable p2p bridge? */
	if (bridge->flags & BRIDGE_HAS_EJ0) {
		struct acpiphp_func *func;

		dbg("found ejectable p2p bridge\n");

		/* make link between PCI bridge and PCI function */
		func = acpiphp_bridge_handle_to_function(bridge->handle);
		if (!func)
			return;
		bridge->func = func;
		func->bridge = bridge;
	}
}