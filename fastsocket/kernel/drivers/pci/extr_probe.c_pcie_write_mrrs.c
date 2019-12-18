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
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ PCIE_BUS_PERFORMANCE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ pcie_bus_config ; 
 int pcie_get_mps (struct pci_dev*) ; 
 int pcie_get_readrq (struct pci_dev*) ; 
 int pcie_set_readrq (struct pci_dev*,int) ; 

__attribute__((used)) static void pcie_write_mrrs(struct pci_dev *dev)
{
	int rc, mrrs;

	/* In the "safe" case, do not configure the MRRS.  There appear to be
	 * issues with setting MRRS to 0 on a number of devices.
	 */
	if (pcie_bus_config != PCIE_BUS_PERFORMANCE)
		return;

	/* For Max performance, the MRRS must be set to the largest supported
	 * value.  However, it cannot be configured larger than the MPS the
	 * device or the bus can support.  This should already be properly
	 * configured by a prior call to pcie_write_mps.
	 */
	mrrs = pcie_get_mps(dev);

	/* MRRS is a R/W register.  Invalid values can be written, but a
	 * subsequent read will verify if the value is acceptable or not.
	 * If the MRRS value provided is not acceptable (e.g., too large),
	 * shrink the value until it is acceptable to the HW.
 	 */
	while (mrrs != pcie_get_readrq(dev) && mrrs >= 128) {
		rc = pcie_set_readrq(dev, mrrs);
		if (!rc)
			break;

		dev_warn(&dev->dev, "Failed attempting to set the MRRS\n");
		mrrs /= 2;
	}

	if (mrrs < 128)
		dev_err(&dev->dev, "MRRS was unable to be configured with a "
			"safe value.  If problems are experienced, try running "
			"with pci=pcie_bus_safe.\n");
}