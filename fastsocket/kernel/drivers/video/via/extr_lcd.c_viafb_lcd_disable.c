#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ lvds_chip_name; } ;
struct TYPE_6__ {TYPE_1__* chip_info; int /*<<< orphan*/  lvds_setting_info; } ;
struct TYPE_5__ {scalar_t__ gfx_chip_name; TYPE_3__ lvds_chip_info; TYPE_3__ lvds_chip_info2; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR6A ; 
 int /*<<< orphan*/  CR6B ; 
 int /*<<< orphan*/  CR79 ; 
 int /*<<< orphan*/  CR91 ; 
 scalar_t__ INTEGRATED_LVDS ; 
 int /*<<< orphan*/  SR16 ; 
 int /*<<< orphan*/  SR1E ; 
 int /*<<< orphan*/  SR2A ; 
 int /*<<< orphan*/  SR3D ; 
 scalar_t__ UNICHROME_CLE266 ; 
 scalar_t__ UNICHROME_CX700 ; 
 int /*<<< orphan*/  VIACR ; 
 int /*<<< orphan*/  VIASR ; 
 scalar_t__ VT1636_LVDS ; 
 int /*<<< orphan*/  integrated_lvds_disable (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  lcd_powersequence_off () ; 
 scalar_t__ viafb_LCD2_ON ; 
 int /*<<< orphan*/  viafb_disable_lvds_vt1636 (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  viafb_write_reg_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 TYPE_2__* viaparinfo ; 

void viafb_lcd_disable(void)
{

	if (viaparinfo->chip_info->gfx_chip_name == UNICHROME_CLE266) {
		lcd_powersequence_off();
		/* DI1 pad off */
		viafb_write_reg_mask(SR1E, VIASR, 0x00, 0x30);
	} else if (viaparinfo->chip_info->gfx_chip_name == UNICHROME_CX700) {
		if (viafb_LCD2_ON
		    && (INTEGRATED_LVDS ==
			viaparinfo->chip_info->lvds_chip_info2.lvds_chip_name))
			integrated_lvds_disable(viaparinfo->lvds_setting_info,
				&viaparinfo->chip_info->lvds_chip_info2);
		if (INTEGRATED_LVDS ==
			viaparinfo->chip_info->lvds_chip_info.lvds_chip_name)
			integrated_lvds_disable(viaparinfo->lvds_setting_info,
				&viaparinfo->chip_info->lvds_chip_info);
		if (VT1636_LVDS == viaparinfo->chip_info->
			lvds_chip_info.lvds_chip_name)
			viafb_disable_lvds_vt1636(viaparinfo->lvds_setting_info,
				&viaparinfo->chip_info->lvds_chip_info);
	} else if (VT1636_LVDS ==
	viaparinfo->chip_info->lvds_chip_info.lvds_chip_name) {
		viafb_disable_lvds_vt1636(viaparinfo->lvds_setting_info,
				    &viaparinfo->chip_info->lvds_chip_info);
	} else {
		/* DFP-HL pad off          */
		viafb_write_reg_mask(SR2A, VIASR, 0x00, 0x0F);
		/* Backlight off           */
		viafb_write_reg_mask(SR3D, VIASR, 0x00, 0x20);
		/* 24 bit DI data paht off */
		viafb_write_reg_mask(CR91, VIACR, 0x80, 0x80);
		/* Simultaneout disabled   */
		viafb_write_reg_mask(CR6B, VIACR, 0x00, 0x08);
	}

	/* Disable expansion bit   */
	viafb_write_reg_mask(CR79, VIACR, 0x00, 0x01);
	/* CRT path set to IGA1    */
	viafb_write_reg_mask(SR16, VIASR, 0x00, 0x40);
	/* Simultaneout disabled   */
	viafb_write_reg_mask(CR6B, VIACR, 0x00, 0x08);
	/* IGA2 path disabled      */
	viafb_write_reg_mask(CR6A, VIACR, 0x00, 0x80);

}