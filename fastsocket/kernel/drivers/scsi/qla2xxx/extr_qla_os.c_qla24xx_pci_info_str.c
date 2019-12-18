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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct scsi_qla_host {struct qla_hw_data* hw; } ;
struct qla_hw_data {int pci_attr; int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  lwstr ;

/* Variables and functions */
 int BIT_0 ; 
 int BIT_1 ; 
 int BIT_2 ; 
 int BIT_3 ; 
 int BIT_4 ; 
 int BIT_5 ; 
 int BIT_6 ; 
 int BIT_7 ; 
 int BIT_8 ; 
 int BIT_9 ; 
 int CSRX_PCIX_BUS_MODE_MASK ; 
 scalar_t__ PCI_EXP_LNKCAP ; 
 int pci_pcie_cap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static char *
qla24xx_pci_info_str(struct scsi_qla_host *vha, char *str)
{
	static char *pci_bus_modes[] = { "33", "66", "100", "133", };
	struct qla_hw_data *ha = vha->hw;
	uint32_t pci_bus;
	int pcie_reg;

	pcie_reg = pci_pcie_cap(ha->pdev);
	if (pcie_reg) {
		char lwstr[6];
		uint16_t pcie_lstat, lspeed, lwidth;

		pcie_reg += PCI_EXP_LNKCAP;
		pci_read_config_word(ha->pdev, pcie_reg, &pcie_lstat);
		lspeed = pcie_lstat & (BIT_0 | BIT_1 | BIT_2 | BIT_3);
		lwidth = (pcie_lstat &
		    (BIT_4 | BIT_5 | BIT_6 | BIT_7 | BIT_8 | BIT_9)) >> 4;

		strcpy(str, "PCIe (");
		switch (lspeed) {
		case 1:
			strcat(str, "2.5GT/s ");
			break;
		case 2:
			strcat(str, "5.0GT/s ");
			break;
		case 3:
			strcat(str, "8.0GT/s ");
			break;
		default:
			strcat(str, "<unknown> ");
			break;
		}
		snprintf(lwstr, sizeof(lwstr), "x%d)", lwidth);
		strcat(str, lwstr);

		return str;
	}

	strcpy(str, "PCI");
	pci_bus = (ha->pci_attr & CSRX_PCIX_BUS_MODE_MASK) >> 8;
	if (pci_bus == 0 || pci_bus == 8) {
		strcat(str, " (");
		strcat(str, pci_bus_modes[pci_bus >> 3]);
	} else {
		strcat(str, "-X ");
		if (pci_bus & BIT_2)
			strcat(str, "Mode 2");
		else
			strcat(str, "Mode 1");
		strcat(str, " (");
		strcat(str, pci_bus_modes[pci_bus & ~BIT_2]);
	}
	strcat(str, " MHz)");

	return str;
}