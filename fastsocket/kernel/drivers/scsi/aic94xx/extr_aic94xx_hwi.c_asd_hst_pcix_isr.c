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
typedef  int u32 ;
typedef  int u16 ;
struct asd_ha_struct {int /*<<< orphan*/  pcidev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECC_CTRL_STAT ; 
 int /*<<< orphan*/  PCIX_STATUS ; 
 int /*<<< orphan*/  PCI_STATUS ; 
 int PCI_STATUS_DETECTED_PARITY ; 
 int PCI_STATUS_PARITY ; 
 int PCI_STATUS_REC_MASTER_ABORT ; 
 int PCI_STATUS_REC_TARGET_ABORT ; 
 int RCV_SCE ; 
 int SC_DISCARD ; 
 int UNCOR_ECCERR ; 
 int UNEXP_SC ; 
 int /*<<< orphan*/  asd_chip_reset (struct asd_ha_struct*) ; 
 int /*<<< orphan*/  asd_printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void asd_hst_pcix_isr(struct asd_ha_struct *asd_ha)
{
	u16 status;
	u32 pcix_status;
	u32 ecc_status;

	pci_read_config_word(asd_ha->pcidev, PCI_STATUS, &status);
	pci_read_config_dword(asd_ha->pcidev, PCIX_STATUS, &pcix_status);
	pci_read_config_dword(asd_ha->pcidev, ECC_CTRL_STAT, &ecc_status);

	if (status & PCI_STATUS_DETECTED_PARITY)
		asd_printk("parity error for %s\n", pci_name(asd_ha->pcidev));
	else if (status & PCI_STATUS_REC_MASTER_ABORT)
		asd_printk("master abort for %s\n", pci_name(asd_ha->pcidev));
	else if (status & PCI_STATUS_REC_TARGET_ABORT)
		asd_printk("target abort for %s\n", pci_name(asd_ha->pcidev));
	else if (status & PCI_STATUS_PARITY)
		asd_printk("data parity for %s\n", pci_name(asd_ha->pcidev));
	else if (pcix_status & RCV_SCE) {
		asd_printk("received split completion error for %s\n",
			   pci_name(asd_ha->pcidev));
		pci_write_config_dword(asd_ha->pcidev,PCIX_STATUS,pcix_status);
		/* XXX: Abort task? */
		return;
	} else if (pcix_status & UNEXP_SC) {
		asd_printk("unexpected split completion for %s\n",
			   pci_name(asd_ha->pcidev));
		pci_write_config_dword(asd_ha->pcidev,PCIX_STATUS,pcix_status);
		/* ignore */
		return;
	} else if (pcix_status & SC_DISCARD)
		asd_printk("split completion discarded for %s\n",
			   pci_name(asd_ha->pcidev));
	else if (ecc_status & UNCOR_ECCERR)
		asd_printk("uncorrectable ECC error for %s\n",
			   pci_name(asd_ha->pcidev));
	asd_chip_reset(asd_ha);
}