#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_6__ {TYPE_2__* chip_info; } ;
struct TYPE_4__ {scalar_t__ output_interface; int /*<<< orphan*/  tmds_chip_slave_addr; } ;
struct TYPE_5__ {scalar_t__ gfx_chip_name; TYPE_1__ tmds_chip_info; } ;

/* Variables and functions */
 int BIT0 ; 
 int BIT3 ; 
 int BIT6 ; 
 int BIT7 ; 
 int /*<<< orphan*/  CR88 ; 
 int /*<<< orphan*/  CR91 ; 
 int /*<<< orphan*/  CRD2 ; 
 scalar_t__ INTERFACE_DFP_HIGH ; 
 scalar_t__ INTERFACE_DFP_LOW ; 
 scalar_t__ INTERFACE_DVP0 ; 
 scalar_t__ INTERFACE_DVP1 ; 
 scalar_t__ INTERFACE_TMDS ; 
 int /*<<< orphan*/  SR1E ; 
 int /*<<< orphan*/  SR2A ; 
 scalar_t__ UNICHROME_CLE266 ; 
 int /*<<< orphan*/  VIACR ; 
 int /*<<< orphan*/  VIASR ; 
 int /*<<< orphan*/  tmds_register_write (int,int) ; 
 int viafb_bus_width ; 
 int viafb_device_lcd_dualedge ; 
 int /*<<< orphan*/  viafb_i2c_writebyte (int /*<<< orphan*/ ,int,int) ; 
 int viafb_platform_epia_dvi ; 
 int viafb_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  viafb_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  viafb_write_reg_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 TYPE_3__* viaparinfo ; 

void viafb_dvi_enable(void)
{
	u8 data;

	if (viaparinfo->chip_info->
		tmds_chip_info.output_interface == INTERFACE_DVP0) {
		viafb_write_reg(SR1E, VIASR,
			viafb_read_reg(VIASR, SR1E) | 0xC0);
		if (viaparinfo->chip_info->gfx_chip_name == UNICHROME_CLE266)
			tmds_register_write(0x88, 0x3b);
		else
			/*clear CR91[5] to direct on display period
			   in the secondary diplay path */
			viafb_write_reg(CR91, VIACR,
			viafb_read_reg(VIACR, CR91) & 0xDF);
	}

	if (viaparinfo->chip_info->
		tmds_chip_info.output_interface == INTERFACE_DVP1) {
		viafb_write_reg(SR1E, VIASR,
			viafb_read_reg(VIASR, SR1E) | 0x30);

		/*fix dvi cann't be enabled with MB VT5718C4 - Al Zhang */
		if (viaparinfo->chip_info->gfx_chip_name == UNICHROME_CLE266) {
			tmds_register_write(0x88, 0x3b);
		} else {
			/*clear CR91[5] to direct on display period
			  in the secondary diplay path */
			viafb_write_reg(CR91, VIACR,
			viafb_read_reg(VIACR, CR91) & 0xDF);
		}

		/*fix DVI cannot enable on EPIA-M board */
		if (viafb_platform_epia_dvi == 1) {
			viafb_write_reg_mask(CR91, VIACR, 0x1f, 0x1f);
			viafb_write_reg_mask(CR88, VIACR, 0x00, BIT6 + BIT0);
			if (viafb_bus_width == 24) {
				if (viafb_device_lcd_dualedge == 1)
					data = 0x3F;
				else
					data = 0x37;
				viafb_i2c_writebyte(viaparinfo->chip_info->
					     tmds_chip_info.
					     tmds_chip_slave_addr,
					     0x08, data);
			}
		}
	}

	if (viaparinfo->chip_info->
		tmds_chip_info.output_interface == INTERFACE_DFP_HIGH) {
		viafb_write_reg(SR2A, VIASR,
			viafb_read_reg(VIASR, SR2A) | 0x0C);
		viafb_write_reg(CR91, VIACR,
			viafb_read_reg(VIACR, CR91) & 0xDF);
	}

	if (viaparinfo->chip_info->
		tmds_chip_info.output_interface == INTERFACE_DFP_LOW) {
		viafb_write_reg(SR2A, VIASR,
			viafb_read_reg(VIASR, SR2A) | 0x03);
		viafb_write_reg(CR91, VIACR,
			viafb_read_reg(VIACR, CR91) & 0xDF);
	}
	if (viaparinfo->chip_info->
		tmds_chip_info.output_interface == INTERFACE_TMDS) {
		/* Turn on Display period in the panel path. */
		viafb_write_reg_mask(CR91, VIACR, 0, BIT7);

		/* Turn on TMDS power. */
		viafb_write_reg_mask(CRD2, VIACR, 0, BIT3);
	}
}