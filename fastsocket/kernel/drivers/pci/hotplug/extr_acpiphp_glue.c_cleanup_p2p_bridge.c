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
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_TYPE_DEVICE ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_walk_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void**),int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct acpiphp_bridge* acpiphp_handle_to_bridge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_bridge (struct acpiphp_bridge*) ; 

__attribute__((used)) static acpi_status
cleanup_p2p_bridge(acpi_handle handle, u32 lvl, void *context, void **rv)
{
	struct acpiphp_bridge *bridge;

	/* cleanup p2p bridges under this P2P bridge
	   in a depth-first manner */
	acpi_walk_namespace(ACPI_TYPE_DEVICE, handle, (u32)1,
				cleanup_p2p_bridge, NULL, NULL);

	bridge = acpiphp_handle_to_bridge(handle);
	if (bridge)
		cleanup_bridge(bridge);

	return AE_OK;
}