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
struct acpiphp_bridge {int /*<<< orphan*/  res_lock; int /*<<< orphan*/  pci_bus; int /*<<< orphan*/ * handle; int /*<<< orphan*/  type; } ;
struct acpi_pci_root {int /*<<< orphan*/  bus; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  BRIDGE_TYPE_HOST ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct acpi_pci_root* acpi_pci_find_root (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_bridge_misc (struct acpiphp_bridge*) ; 
 struct acpiphp_bridge* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void add_host_bridge(acpi_handle *handle)
{
	struct acpiphp_bridge *bridge;
	struct acpi_pci_root *root = acpi_pci_find_root(handle);

	bridge = kzalloc(sizeof(struct acpiphp_bridge), GFP_KERNEL);
	if (bridge == NULL)
		return;

	bridge->type = BRIDGE_TYPE_HOST;
	bridge->handle = handle;

	bridge->pci_bus = root->bus;

	spin_lock_init(&bridge->res_lock);

	init_bridge_misc(bridge);
}