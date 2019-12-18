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
struct pci_dev {int /*<<< orphan*/  subordinate; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_DEVICE ; 
 int /*<<< orphan*/  AE_OK ; 
 struct pci_dev* acpi_get_pci_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_walk_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void**),int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_p2p_bridge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ detect_ejectable_slots (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static acpi_status
find_p2p_bridge(acpi_handle handle, u32 lvl, void *context, void **rv)
{
	acpi_status status;
	struct pci_dev *dev;

	dev = acpi_get_pci_dev(handle);
	if (!dev || !dev->subordinate)
		goto out;

	/* check if this bridge has ejectable slots */
	if ((detect_ejectable_slots(handle) > 0)) {
		dbg("found PCI-to-PCI bridge at PCI %s\n", pci_name(dev));
		add_p2p_bridge(handle);
	}

	/* search P2P bridges under this p2p bridge */
	status = acpi_walk_namespace(ACPI_TYPE_DEVICE, handle, (u32)1,
				     find_p2p_bridge, NULL, NULL);
	if (ACPI_FAILURE(status))
		warn("find_p2p_bridge failed (error code = 0x%x)\n", status);

 out:
	pci_dev_put(dev);
	return AE_OK;
}