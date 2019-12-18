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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ int16_t ;
typedef  enum VFE_DMI_RAM_SEL { ____Placeholder_VFE_DMI_RAM_SEL } VFE_DMI_RAM_SEL ;
typedef  int /*<<< orphan*/  boolean ;
struct TYPE_2__ {scalar_t__ vfebase; } ;

/* Variables and functions */
 int NO_MEM_SELECTED ; 
 int RGBLUT_RAM_CH0_BANK0 ; 
 int RGBLUT_RAM_CH0_BANK1 ; 
 int RGBLUT_RAM_CH1_BANK0 ; 
 int RGBLUT_RAM_CH1_BANK1 ; 
 int RGBLUT_RAM_CH2_BANK0 ; 
 int RGBLUT_RAM_CH2_BANK1 ; 
 scalar_t__ VFE_DMI_CFG ; 
 int /*<<< orphan*/  VFE_DMI_CFG_DEFAULT ; 
 scalar_t__ VFE_DMI_DATA_LO ; 
 scalar_t__ VFE_GAMMA_TABLE_LENGTH ; 
 TYPE_1__* ctrl ; 
 int /*<<< orphan*/  vfe_program_dmi_cfg (int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void vfe_write_gamma_table(uint8_t channel,
	boolean bank, int16_t *pTable)
{
	uint16_t i;

	enum VFE_DMI_RAM_SEL dmiRamSel = NO_MEM_SELECTED;

	switch (channel) {
	case 0:
		if (bank == 0)
			dmiRamSel = RGBLUT_RAM_CH0_BANK0;
		else
			dmiRamSel = RGBLUT_RAM_CH0_BANK1;
		break;

	case 1:
		if (bank == 0)
			dmiRamSel = RGBLUT_RAM_CH1_BANK0;
		else
			dmiRamSel = RGBLUT_RAM_CH1_BANK1;
		break;

	case 2:
		if (bank == 0)
			dmiRamSel = RGBLUT_RAM_CH2_BANK0;
		else
			dmiRamSel = RGBLUT_RAM_CH2_BANK1;
		break;

	default:
		break;
	}

	vfe_program_dmi_cfg(dmiRamSel);

	for (i = 0; i < VFE_GAMMA_TABLE_LENGTH; i++) {
		writel((uint32_t)(*pTable), ctrl->vfebase + VFE_DMI_DATA_LO);
		pTable++;
	}

	/* After DMI transfer, need to set the DMI_CFG to unselect any SRAM
	unselect the SRAM Bank. */
	writel(VFE_DMI_CFG_DEFAULT, ctrl->vfebase + VFE_DMI_CFG);
}