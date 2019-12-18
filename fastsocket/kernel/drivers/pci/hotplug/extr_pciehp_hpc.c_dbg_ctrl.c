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
typedef  char* u16 ;
struct pci_dev {char* vendor; char* device; char* subsystem_device; char* subsystem_vendor; int /*<<< orphan*/ * resource; int /*<<< orphan*/  irq; } ;
struct controller {char* slot_cap; TYPE_1__* pcie; } ;
struct TYPE_2__ {struct pci_dev* port; } ;

/* Variables and functions */
 scalar_t__ ATTN_BUTTN (struct controller*) ; 
 scalar_t__ ATTN_LED (struct controller*) ; 
 int DEVICE_COUNT_RESOURCE ; 
 scalar_t__ EMI (struct controller*) ; 
 scalar_t__ HP_SUPR_RM (struct controller*) ; 
 scalar_t__ MRL_SENS (struct controller*) ; 
 scalar_t__ NO_CMD_CMPL (struct controller*) ; 
 int /*<<< orphan*/  PCI_EXP_SLTCTL ; 
 int /*<<< orphan*/  PCI_EXP_SLTSTA ; 
 scalar_t__ POWER_CTRL (struct controller*) ; 
 char* PSN (struct controller*) ; 
 scalar_t__ PWR_LED (struct controller*) ; 
 int /*<<< orphan*/  ctrl_info (struct controller*,char*,...) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 char* pci_pcie_cap (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pciehp_debug ; 
 int /*<<< orphan*/  pciehp_readw (struct controller*,int /*<<< orphan*/ ,char**) ; 

__attribute__((used)) static inline void dbg_ctrl(struct controller *ctrl)
{
	int i;
	u16 reg16;
	struct pci_dev *pdev = ctrl->pcie->port;

	if (!pciehp_debug)
		return;

	ctrl_info(ctrl, "Hotplug Controller:\n");
	ctrl_info(ctrl, "  Seg/Bus/Dev/Func/IRQ : %s IRQ %d\n",
		  pci_name(pdev), pdev->irq);
	ctrl_info(ctrl, "  Vendor ID            : 0x%04x\n", pdev->vendor);
	ctrl_info(ctrl, "  Device ID            : 0x%04x\n", pdev->device);
	ctrl_info(ctrl, "  Subsystem ID         : 0x%04x\n",
		  pdev->subsystem_device);
	ctrl_info(ctrl, "  Subsystem Vendor ID  : 0x%04x\n",
		  pdev->subsystem_vendor);
	ctrl_info(ctrl, "  PCIe Cap offset      : 0x%02x\n",
		  pci_pcie_cap(pdev));
	for (i = 0; i < DEVICE_COUNT_RESOURCE; i++) {
		if (!pci_resource_len(pdev, i))
			continue;
		ctrl_info(ctrl, "  PCI resource [%d]     : %pR\n",
			  i, &pdev->resource[i]);
	}
	ctrl_info(ctrl, "Slot Capabilities      : 0x%08x\n", ctrl->slot_cap);
	ctrl_info(ctrl, "  Physical Slot Number : %d\n", PSN(ctrl));
	ctrl_info(ctrl, "  Attention Button     : %3s\n",
		  ATTN_BUTTN(ctrl) ? "yes" : "no");
	ctrl_info(ctrl, "  Power Controller     : %3s\n",
		  POWER_CTRL(ctrl) ? "yes" : "no");
	ctrl_info(ctrl, "  MRL Sensor           : %3s\n",
		  MRL_SENS(ctrl)   ? "yes" : "no");
	ctrl_info(ctrl, "  Attention Indicator  : %3s\n",
		  ATTN_LED(ctrl)   ? "yes" : "no");
	ctrl_info(ctrl, "  Power Indicator      : %3s\n",
		  PWR_LED(ctrl)    ? "yes" : "no");
	ctrl_info(ctrl, "  Hot-Plug Surprise    : %3s\n",
		  HP_SUPR_RM(ctrl) ? "yes" : "no");
	ctrl_info(ctrl, "  EMI Present          : %3s\n",
		  EMI(ctrl)        ? "yes" : "no");
	ctrl_info(ctrl, "  Command Completed    : %3s\n",
		  NO_CMD_CMPL(ctrl) ? "no" : "yes");
	pciehp_readw(ctrl, PCI_EXP_SLTSTA, &reg16);
	ctrl_info(ctrl, "Slot Status            : 0x%04x\n", reg16);
	pciehp_readw(ctrl, PCI_EXP_SLTCTL, &reg16);
	ctrl_info(ctrl, "Slot Control           : 0x%04x\n", reg16);
}