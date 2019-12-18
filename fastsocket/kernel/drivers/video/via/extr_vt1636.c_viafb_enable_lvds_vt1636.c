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
struct lvds_setting_information {int dummy; } ;
struct lvds_chip_information {int output_interface; } ;

/* Variables and functions */
#define  INTERFACE_DFP_HIGH 131 
#define  INTERFACE_DFP_LOW 130 
#define  INTERFACE_DVP0 129 
#define  INTERFACE_DVP1 128 
 int /*<<< orphan*/  SR1E ; 
 int /*<<< orphan*/  SR2A ; 
 int /*<<< orphan*/ * VDD_ON_TBL_VT1636 ; 
 int /*<<< orphan*/  VIASR ; 
 int /*<<< orphan*/  viafb_gpio_i2c_write_mask_lvds (struct lvds_setting_information*,struct lvds_chip_information*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  viafb_write_reg_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

void viafb_enable_lvds_vt1636(struct lvds_setting_information
			*plvds_setting_info,
			struct lvds_chip_information *plvds_chip_info)
{

	viafb_gpio_i2c_write_mask_lvds(plvds_setting_info, plvds_chip_info,
				 VDD_ON_TBL_VT1636[0]);

	/* Pad on: */
	switch (plvds_chip_info->output_interface) {
	case INTERFACE_DVP0:
		{
			viafb_write_reg_mask(SR1E, VIASR, 0xC0, 0xC0);
			break;
		}

	case INTERFACE_DVP1:
		{
			viafb_write_reg_mask(SR1E, VIASR, 0x30, 0x30);
			break;
		}

	case INTERFACE_DFP_LOW:
		{
			viafb_write_reg_mask(SR2A, VIASR, 0x03, 0x03);
			break;
		}

	case INTERFACE_DFP_HIGH:
		{
			viafb_write_reg_mask(SR2A, VIASR, 0x03, 0x0C);
			break;
		}

	}
}