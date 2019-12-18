#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct acpiphp_bridge {TYPE_2__* pci_dev; int /*<<< orphan*/  res_lock; TYPE_1__* pci_bus; int /*<<< orphan*/ * handle; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  acpi_handle ;
struct TYPE_5__ {TYPE_1__* subordinate; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRIDGE_TYPE_P2P ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_2__* acpi_get_pci_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_p2p_bridge_flags (struct acpiphp_bridge*) ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_bridge_misc (struct acpiphp_bridge*) ; 
 int /*<<< orphan*/  kfree (struct acpiphp_bridge*) ; 
 struct acpiphp_bridge* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dev_put (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void add_p2p_bridge(acpi_handle *handle)
{
	struct acpiphp_bridge *bridge;

	bridge = kzalloc(sizeof(struct acpiphp_bridge), GFP_KERNEL);
	if (bridge == NULL) {
		err("out of memory\n");
		return;
	}

	bridge->type = BRIDGE_TYPE_P2P;
	bridge->handle = handle;
	config_p2p_bridge_flags(bridge);

	bridge->pci_dev = acpi_get_pci_dev(handle);
	bridge->pci_bus = bridge->pci_dev->subordinate;
	if (!bridge->pci_bus) {
		err("This is not a PCI-to-PCI bridge!\n");
		goto err;
	}

	/*
	 * Grab a ref to the subordinate PCI bus in case the bus is
	 * removed via PCI core logical hotplug. The ref pins the bus
	 * (which we access during module unload).
	 */
	get_device(&bridge->pci_bus->dev);
	spin_lock_init(&bridge->res_lock);

	init_bridge_misc(bridge);
	return;
 err:
	pci_dev_put(bridge->pci_dev);
	kfree(bridge);
	return;
}