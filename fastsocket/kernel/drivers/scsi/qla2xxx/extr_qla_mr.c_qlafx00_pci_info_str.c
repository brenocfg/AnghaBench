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
struct scsi_qla_host {struct qla_hw_data* hw; } ;
struct qla_hw_data {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_CAP_ID_EXP ; 
 int pci_find_capability (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

char *
qlafx00_pci_info_str(struct scsi_qla_host *vha, char *str)
{
	struct qla_hw_data *ha = vha->hw;
	int pcie_reg;

	pcie_reg = pci_find_capability(ha->pdev, PCI_CAP_ID_EXP);
	if (pcie_reg) {
		strcpy(str, "PCIe iSA");
		return str;
	}
	return str;
}