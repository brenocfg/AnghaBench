#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct vfe_cmd_la_config {int /*<<< orphan*/  enable; scalar_t__* table; } ;
typedef  scalar_t__ int16_t ;
typedef  enum VFE_DMI_RAM_SEL { ____Placeholder_VFE_DMI_RAM_SEL } VFE_DMI_RAM_SEL ;
struct TYPE_3__ {int /*<<< orphan*/  lumaAdaptationEnable; } ;
struct TYPE_4__ {scalar_t__ vfeLaBankSel; scalar_t__ vfebase; TYPE_1__ vfeModuleEnableLocal; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDBG (char*,scalar_t__) ; 
 int LUMA_ADAPT_LUT_RAM_BANK0 ; 
 int LUMA_ADAPT_LUT_RAM_BANK1 ; 
 scalar_t__ VFE_DMI_CFG ; 
 scalar_t__ VFE_DMI_CFG_DEFAULT ; 
 scalar_t__ VFE_DMI_DATA_LO ; 
 scalar_t__ VFE_LA_CFG ; 
 scalar_t__ VFE_LA_TABLE_LENGTH ; 
 TYPE_2__* ctrl ; 
 int /*<<< orphan*/  vfe_program_dmi_cfg (int) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

void vfe_la_config(struct vfe_cmd_la_config *in)
{
	uint16_t i;
	int16_t  *pTable;
	enum VFE_DMI_RAM_SEL dmiRamSel;

	pTable = in->table;
	ctrl->vfeModuleEnableLocal.lumaAdaptationEnable = in->enable;

	if (ctrl->vfeLaBankSel == 0)
		dmiRamSel = LUMA_ADAPT_LUT_RAM_BANK0;
	else
		dmiRamSel = LUMA_ADAPT_LUT_RAM_BANK1;

	/* configure the DMI_CFG to select right sram */
	vfe_program_dmi_cfg(dmiRamSel);

	for (i = 0; i < VFE_LA_TABLE_LENGTH; i++) {
		writel((uint32_t)(*pTable), ctrl->vfebase + VFE_DMI_DATA_LO);
		pTable++;
	}

	/* After DMI transfer, to make it safe, need to set the
	 * DMI_CFG to unselect any SRAM */
	writel(VFE_DMI_CFG_DEFAULT, ctrl->vfebase + VFE_DMI_CFG);

	/* can only be bank 0 or bank 1 for now. */
	writel(ctrl->vfeLaBankSel, ctrl->vfebase + VFE_LA_CFG);
	CDBG("VFE Luma adaptation bank selection is 0x%x\n",
			 *(uint32_t *)&ctrl->vfeLaBankSel);
}