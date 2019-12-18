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
typedef  int u32 ;
struct be_adapter {int hw_error; TYPE_1__* pdev; scalar_t__ db; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCICFG_UE_STATUS_HIGH ; 
 int /*<<< orphan*/  PCICFG_UE_STATUS_HI_MASK ; 
 int /*<<< orphan*/  PCICFG_UE_STATUS_LOW ; 
 int /*<<< orphan*/  PCICFG_UE_STATUS_LOW_MASK ; 
 scalar_t__ SLIPORT_ERROR1_OFFSET ; 
 scalar_t__ SLIPORT_ERROR2_OFFSET ; 
 int SLIPORT_STATUS_ERR_MASK ; 
 scalar_t__ SLIPORT_STATUS_OFFSET ; 
 scalar_t__ be_hw_error (struct be_adapter*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int ioread32 (scalar_t__) ; 
 scalar_t__ lancer_chip (struct be_adapter*) ; 
 int /*<<< orphan*/  pci_read_config_dword (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int* ue_status_hi_desc ; 
 int* ue_status_low_desc ; 

void be_detect_error(struct be_adapter *adapter)
{
	u32 ue_lo = 0, ue_hi = 0, ue_lo_mask = 0, ue_hi_mask = 0;
	u32 sliport_status = 0, sliport_err1 = 0, sliport_err2 = 0;
	u32 i;

	if (be_hw_error(adapter))
		return;

	if (lancer_chip(adapter)) {
		sliport_status = ioread32(adapter->db + SLIPORT_STATUS_OFFSET);
		if (sliport_status & SLIPORT_STATUS_ERR_MASK) {
			sliport_err1 = ioread32(adapter->db +
					SLIPORT_ERROR1_OFFSET);
			sliport_err2 = ioread32(adapter->db +
					SLIPORT_ERROR2_OFFSET);
		}
	} else {
		pci_read_config_dword(adapter->pdev,
				PCICFG_UE_STATUS_LOW, &ue_lo);
		pci_read_config_dword(adapter->pdev,
				PCICFG_UE_STATUS_HIGH, &ue_hi);
		pci_read_config_dword(adapter->pdev,
				PCICFG_UE_STATUS_LOW_MASK, &ue_lo_mask);
		pci_read_config_dword(adapter->pdev,
				PCICFG_UE_STATUS_HI_MASK, &ue_hi_mask);

		ue_lo = (ue_lo & ~ue_lo_mask);
		ue_hi = (ue_hi & ~ue_hi_mask);
	}

	/* On certain platforms BE hardware can indicate spurious UEs.
	 * Allow the h/w to stop working completely in case of a real UE.
	 * Hence not setting the hw_error for UE detection.
	 */
	if (sliport_status & SLIPORT_STATUS_ERR_MASK) {
		adapter->hw_error = true;
		dev_err(&adapter->pdev->dev,
			"Error detected in the card\n");
	}

	if (sliport_status & SLIPORT_STATUS_ERR_MASK) {
		dev_err(&adapter->pdev->dev,
			"ERR: sliport status 0x%x\n", sliport_status);
		dev_err(&adapter->pdev->dev,
			"ERR: sliport error1 0x%x\n", sliport_err1);
		dev_err(&adapter->pdev->dev,
			"ERR: sliport error2 0x%x\n", sliport_err2);
	}

	if (ue_lo) {
		for (i = 0; ue_lo; ue_lo >>= 1, i++) {
			if (ue_lo & 1)
				dev_err(&adapter->pdev->dev,
				"UE: %s bit set\n", ue_status_low_desc[i]);
		}
	}

	if (ue_hi) {
		for (i = 0; ue_hi; ue_hi >>= 1, i++) {
			if (ue_hi & 1)
				dev_err(&adapter->pdev->dev,
				"UE: %s bit set\n", ue_status_hi_desc[i]);
		}
	}

}