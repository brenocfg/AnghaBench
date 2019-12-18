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
typedef  scalar_t__ uint32_t ;
typedef  enum VFE_DMI_RAM_SEL { ____Placeholder_VFE_DMI_RAM_SEL } VFE_DMI_RAM_SEL ;
struct TYPE_2__ {scalar_t__ vfebase; } ;

/* Variables and functions */
 scalar_t__ VFE_DMI_ADDR ; 
 scalar_t__ VFE_DMI_CFG ; 
 scalar_t__ VFE_DMI_CFG_DEFAULT ; 
 TYPE_1__* ctrl ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void vfe_program_dmi_cfg(enum VFE_DMI_RAM_SEL bankSel)
{
	/* set bit 8 for auto increment. */
	uint32_t value = (uint32_t) ctrl->vfebase + VFE_DMI_CFG_DEFAULT;

	value += (uint32_t)bankSel;
	/* CDBG("dmi cfg input bank is  0x%x\n", bankSel); */

	writel(value, ctrl->vfebase + VFE_DMI_CFG);
	writel(0, ctrl->vfebase + VFE_DMI_ADDR);
}