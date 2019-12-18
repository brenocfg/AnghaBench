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
typedef  int u8 ;
typedef  int u32 ;
struct slot {TYPE_1__* ctrl; } ;
struct TYPE_2__ {int pcix_misc2_reg; int /*<<< orphan*/  pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIX_MEM_BASE_LIMIT_OFFSET ; 
 int /*<<< orphan*/  PCIX_MISCII_OFFSET ; 
 int /*<<< orphan*/  PCIX_MISC_BRIDGE_ERRORS_OFFSET ; 
 int PERRFATALENABLE_MASK ; 
 int PERRFLOODENABLE_MASK ; 
 int PERRNONFATALENABLE_MASK ; 
 int PERR_OBSERVED_MASK ; 
 int RSE_MASK ; 
 int SERRFATALENABLE_MASK ; 
 int SERRNONFATALENABLE_MASK ; 
 int /*<<< orphan*/  ctrl_dbg (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void amd_pogo_errata_restore_misc_reg(struct slot *p_slot)
{
	u32 pcix_misc2_temp;
	u32 pcix_bridge_errors_reg;
	u32 pcix_mem_base_reg;
	u8  perr_set;
	u8  rse_set;

	/* write-one-to-clear Bridge_Errors[ PERR_OBSERVED ] */
	pci_read_config_dword(p_slot->ctrl->pci_dev, PCIX_MISC_BRIDGE_ERRORS_OFFSET, &pcix_bridge_errors_reg);
	perr_set = pcix_bridge_errors_reg & PERR_OBSERVED_MASK;
	if (perr_set) {
		ctrl_dbg(p_slot->ctrl,
			 "Bridge_Errors[ PERR_OBSERVED = %08X] (W1C)\n",
			 perr_set);

		pci_write_config_dword(p_slot->ctrl->pci_dev, PCIX_MISC_BRIDGE_ERRORS_OFFSET, perr_set);
	}

	/* write-one-to-clear Memory_Base_Limit[ RSE ] */
	pci_read_config_dword(p_slot->ctrl->pci_dev, PCIX_MEM_BASE_LIMIT_OFFSET, &pcix_mem_base_reg);
	rse_set = pcix_mem_base_reg & RSE_MASK;
	if (rse_set) {
		ctrl_dbg(p_slot->ctrl, "Memory_Base_Limit[ RSE ] (W1C)\n");

		pci_write_config_dword(p_slot->ctrl->pci_dev, PCIX_MEM_BASE_LIMIT_OFFSET, rse_set);
	}
	/* restore MiscII register */
	pci_read_config_dword( p_slot->ctrl->pci_dev, PCIX_MISCII_OFFSET, &pcix_misc2_temp );

	if (p_slot->ctrl->pcix_misc2_reg & SERRFATALENABLE_MASK)
		pcix_misc2_temp |= SERRFATALENABLE_MASK;
	else
		pcix_misc2_temp &= ~SERRFATALENABLE_MASK;

	if (p_slot->ctrl->pcix_misc2_reg & SERRNONFATALENABLE_MASK)
		pcix_misc2_temp |= SERRNONFATALENABLE_MASK;
	else
		pcix_misc2_temp &= ~SERRNONFATALENABLE_MASK;

	if (p_slot->ctrl->pcix_misc2_reg & PERRFLOODENABLE_MASK)
		pcix_misc2_temp |= PERRFLOODENABLE_MASK;
	else
		pcix_misc2_temp &= ~PERRFLOODENABLE_MASK;

	if (p_slot->ctrl->pcix_misc2_reg & PERRFATALENABLE_MASK)
		pcix_misc2_temp |= PERRFATALENABLE_MASK;
	else
		pcix_misc2_temp &= ~PERRFATALENABLE_MASK;

	if (p_slot->ctrl->pcix_misc2_reg & PERRNONFATALENABLE_MASK)
		pcix_misc2_temp |= PERRNONFATALENABLE_MASK;
	else
		pcix_misc2_temp &= ~PERRNONFATALENABLE_MASK;
	pci_write_config_dword(p_slot->ctrl->pci_dev, PCIX_MISCII_OFFSET, pcix_misc2_temp);
}