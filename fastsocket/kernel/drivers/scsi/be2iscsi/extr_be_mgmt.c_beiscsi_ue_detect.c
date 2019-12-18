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
typedef  size_t uint8_t ;
typedef  int uint32_t ;
struct beiscsi_hba {int ue_detected; int /*<<< orphan*/  pcidev; } ;

/* Variables and functions */
 int BEISCSI_LOG_CONFIG ; 
 int BEISCSI_LOG_MBOX ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  PCICFG_UE_STATUS_HIGH ; 
 int /*<<< orphan*/  PCICFG_UE_STATUS_LOW ; 
 int /*<<< orphan*/  PCICFG_UE_STATUS_MASK_HI ; 
 int /*<<< orphan*/  PCICFG_UE_STATUS_MASK_LOW ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/ * desc_ue_status_hi ; 
 int /*<<< orphan*/ * desc_ue_status_low ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

void beiscsi_ue_detect(struct beiscsi_hba *phba)
{
	uint32_t ue_hi = 0, ue_lo = 0;
	uint32_t ue_mask_hi = 0, ue_mask_lo = 0;
	uint8_t i = 0;

	if (phba->ue_detected)
		return;

	pci_read_config_dword(phba->pcidev,
			      PCICFG_UE_STATUS_LOW, &ue_lo);
	pci_read_config_dword(phba->pcidev,
			      PCICFG_UE_STATUS_MASK_LOW,
			      &ue_mask_lo);
	pci_read_config_dword(phba->pcidev,
			      PCICFG_UE_STATUS_HIGH,
			      &ue_hi);
	pci_read_config_dword(phba->pcidev,
			      PCICFG_UE_STATUS_MASK_HI,
			      &ue_mask_hi);

	ue_lo = (ue_lo & ~ue_mask_lo);
	ue_hi = (ue_hi & ~ue_mask_hi);


	if (ue_lo || ue_hi) {
		phba->ue_detected = true;
		beiscsi_log(phba, KERN_ERR,
			    BEISCSI_LOG_CONFIG | BEISCSI_LOG_MBOX,
			    "BG_%d : Error detected on the adapter\n");
	}

	if (ue_lo) {
		for (i = 0; ue_lo; ue_lo >>= 1, i++) {
			if (ue_lo & 1)
				beiscsi_log(phba, KERN_ERR,
					    BEISCSI_LOG_CONFIG,
					    "BG_%d : UE_LOW %s bit set\n",
					    desc_ue_status_low[i]);
		}
	}

	if (ue_hi) {
		for (i = 0; ue_hi; ue_hi >>= 1, i++) {
			if (ue_hi & 1)
				beiscsi_log(phba, KERN_ERR,
					    BEISCSI_LOG_CONFIG,
					    "BG_%d : UE_HIGH %s bit set\n",
					    desc_ue_status_hi[i]);
		}
	}
}