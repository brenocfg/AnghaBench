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
typedef  scalar_t__ u8 ;
struct pci_dev {TYPE_1__* bus; scalar_t__ is_hotplug_bridge; } ;
struct TYPE_2__ {scalar_t__ self; int /*<<< orphan*/  devices; } ;

/* Variables and functions */
 scalar_t__ PCI_EXP_TYPE_ROOT_PORT ; 
 int /*<<< orphan*/  list_is_singular (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_is_pcie (struct pci_dev*) ; 
 scalar_t__ pci_pcie_type (scalar_t__) ; 
 scalar_t__ rh_get_mpss (struct pci_dev*) ; 

__attribute__((used)) static int pcie_find_smpss(struct pci_dev *dev, void *data)
{
	u8 *smpss = data;

	if (!pci_is_pcie(dev))
		return 0;

	/* For PCIE hotplug enabled slots not connected directly to a
	 * PCI-E root port, there can be problems when hotplugging
	 * devices.  This is due to the possibility of hotplugging a
	 * device into the fabric with a smaller MPS that the devices
	 * currently running have configured.  Modifying the MPS on the
	 * running devices could cause a fatal bus error due to an
	 * incoming frame being larger than the newly configured MPS.
	 * To work around this, the MPS for the entire fabric must be
	 * set to the minimum size.  Any devices hotplugged into this
	 * fabric will have the minimum MPS set.  If the PCI hotplug
	 * slot is directly connected to the root port and there are not
	 * other devices on the fabric (which seems to be the most
	 * common case), then this is not an issue and MPS discovery
	 * will occur as normal.
	 */
	if (dev->is_hotplug_bridge && (!list_is_singular(&dev->bus->devices) ||
	     (dev->bus->self &&
	      pci_pcie_type(dev->bus->self) != PCI_EXP_TYPE_ROOT_PORT)))
		*smpss = 0;

	if (*smpss > rh_get_mpss(dev))
		*smpss = rh_get_mpss(dev);

	return 0;
}