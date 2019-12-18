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
typedef  scalar_t__ u8 ;
struct slot {int dummy; } ;
struct pcie_device {int /*<<< orphan*/  device; struct pci_dev* port; } ;
struct pci_dev {int dummy; } ;
struct controller {struct slot* slot; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 scalar_t__ POWER_CTRL (struct controller*) ; 
 int /*<<< orphan*/  cleanup_slot (struct controller*) ; 
 int /*<<< orphan*/  ctrl_err (struct controller*,char*) ; 
 int /*<<< orphan*/  ctrl_warn (struct controller*,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int init_slot (struct controller*) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 struct controller* pcie_init (struct pcie_device*) ; 
 int pcie_init_notification (struct controller*) ; 
 scalar_t__ pciehp_acpi_slot_detection_check (struct pci_dev*) ; 
 scalar_t__ pciehp_disable ; 
 int /*<<< orphan*/  pciehp_enable_slot (struct slot*) ; 
 scalar_t__ pciehp_force ; 
 int /*<<< orphan*/  pciehp_get_adapter_status (struct slot*,scalar_t__*) ; 
 int pciehp_power_off_slot (struct slot*) ; 
 int /*<<< orphan*/  pciehp_release_ctrl (struct controller*) ; 
 int /*<<< orphan*/  set_service_data (struct pcie_device*,struct controller*) ; 

__attribute__((used)) static int pciehp_probe(struct pcie_device *dev)
{
	int rc;
	struct controller *ctrl;
	struct slot *slot;
	u8 value;
	struct pci_dev *pdev = dev->port;

	if (pciehp_disable)
		goto err_out_none;

	if (pciehp_force)
		dev_info(&dev->device,
			 "Bypassing BIOS check for pciehp use on %s\n",
			 pci_name(pdev));
	else if (pciehp_acpi_slot_detection_check(dev->port))
		goto err_out_none;

	ctrl = pcie_init(dev);
	if (!ctrl) {
		dev_err(&dev->device, "Controller initialization failed\n");
		goto err_out_none;
	}
	set_service_data(dev, ctrl);

	/* Setup the slot information structures */
	rc = init_slot(ctrl);
	if (rc) {
		if (rc == -EBUSY)
			ctrl_warn(ctrl, "Slot already registered by another "
				  "hotplug driver\n");
		else
			ctrl_err(ctrl, "Slot initialization failed\n");
		goto err_out_release_ctlr;
	}

	/* Enable events after we have setup the data structures */
	rc = pcie_init_notification(ctrl);
	if (rc) {
		ctrl_err(ctrl, "Notification initialization failed\n");
		goto err_out_release_ctlr;
	}

	/* Check if slot is occupied */
	slot = ctrl->slot;
	pciehp_get_adapter_status(slot, &value);
	if (value) {
		if (pciehp_force)
			pciehp_enable_slot(slot);
	} else {
		/* Power off slot if not occupied */
		if (POWER_CTRL(ctrl)) {
			rc = pciehp_power_off_slot(slot);
			if (rc)
				goto err_out_free_ctrl_slot;
		}
	}

	return 0;

err_out_free_ctrl_slot:
	cleanup_slot(ctrl);
err_out_release_ctlr:
	pciehp_release_ctrl(ctrl);
err_out_none:
	return -ENODEV;
}