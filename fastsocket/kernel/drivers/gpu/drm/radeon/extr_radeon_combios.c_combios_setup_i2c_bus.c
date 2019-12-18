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
typedef  void* u32 ;
struct radeon_i2c_bus_rec {int mask_clk_reg; int mask_data_reg; int a_clk_reg; int a_data_reg; int en_clk_reg; int en_data_reg; int y_clk_reg; int y_data_reg; int mask_clk_mask; int mask_data_mask; int a_clk_mask; int a_data_mask; int en_clk_mask; int en_data_mask; int y_clk_mask; int y_data_mask; int hw_capable; int mm_i2c; int i2c_id; int valid; int /*<<< orphan*/  hpd; } ;
struct radeon_device {int family; } ;
typedef  enum radeon_combios_ddc { ____Placeholder_radeon_combios_ddc } radeon_combios_ddc ;

/* Variables and functions */
#define  CHIP_R100 153 
#define  CHIP_R200 152 
#define  CHIP_R300 151 
#define  CHIP_R350 150 
#define  CHIP_RS100 149 
#define  CHIP_RS200 148 
#define  CHIP_RS300 147 
#define  CHIP_RS400 146 
#define  CHIP_RS480 145 
#define  CHIP_RV100 144 
#define  CHIP_RV200 143 
#define  CHIP_RV250 142 
#define  CHIP_RV280 141 
#define  CHIP_RV350 140 
#define  CHIP_RV380 139 
#define  DDC_CRT2 138 
#define  DDC_DVI 137 
#define  DDC_GPIO 136 
#define  DDC_LCD 135 
#define  DDC_MONID 134 
#define  DDC_NONE_DETECTED 133 
#define  DDC_VGA 132 
 void* RADEON_GPIOPAD_A ; 
 void* RADEON_GPIOPAD_EN ; 
 int RADEON_GPIOPAD_MASK ; 
 void* RADEON_GPIOPAD_Y ; 
 int RADEON_GPIO_A_0 ; 
 int RADEON_GPIO_A_1 ; 
#define  RADEON_GPIO_CRT2_DDC 131 
#define  RADEON_GPIO_DVI_DDC 130 
 int RADEON_GPIO_EN_0 ; 
 int RADEON_GPIO_EN_1 ; 
 int RADEON_GPIO_MASK_0 ; 
 int RADEON_GPIO_MASK_1 ; 
#define  RADEON_GPIO_MONID 129 
#define  RADEON_GPIO_VGA_DDC 128 
 int RADEON_GPIO_Y_0 ; 
 int RADEON_GPIO_Y_1 ; 
 int /*<<< orphan*/  RADEON_HPD_NONE ; 
 void* RADEON_MDGPIO_A ; 
 void* RADEON_MDGPIO_EN ; 
 int RADEON_MDGPIO_MASK ; 
 void* RADEON_MDGPIO_Y ; 

__attribute__((used)) static struct radeon_i2c_bus_rec combios_setup_i2c_bus(struct radeon_device *rdev,
						       enum radeon_combios_ddc ddc,
						       u32 clk_mask,
						       u32 data_mask)
{
	struct radeon_i2c_bus_rec i2c;
	int ddc_line = 0;

	/* ddc id            = mask reg
	 * DDC_NONE_DETECTED = none
	 * DDC_DVI           = RADEON_GPIO_DVI_DDC
	 * DDC_VGA           = RADEON_GPIO_VGA_DDC
	 * DDC_LCD           = RADEON_GPIOPAD_MASK
	 * DDC_GPIO          = RADEON_MDGPIO_MASK
	 * r1xx
	 * DDC_MONID         = RADEON_GPIO_MONID
	 * DDC_CRT2          = RADEON_GPIO_CRT2_DDC
	 * r200
	 * DDC_MONID         = RADEON_GPIO_MONID
	 * DDC_CRT2          = RADEON_GPIO_DVI_DDC
	 * r300/r350
	 * DDC_MONID         = RADEON_GPIO_DVI_DDC
	 * DDC_CRT2          = RADEON_GPIO_DVI_DDC
	 * rv2xx/rv3xx
	 * DDC_MONID         = RADEON_GPIO_MONID
	 * DDC_CRT2          = RADEON_GPIO_MONID
	 * rs3xx/rs4xx
	 * DDC_MONID         = RADEON_GPIOPAD_MASK
	 * DDC_CRT2          = RADEON_GPIO_MONID
	 */
	switch (ddc) {
	case DDC_NONE_DETECTED:
	default:
		ddc_line = 0;
		break;
	case DDC_DVI:
		ddc_line = RADEON_GPIO_DVI_DDC;
		break;
	case DDC_VGA:
		ddc_line = RADEON_GPIO_VGA_DDC;
		break;
	case DDC_LCD:
		ddc_line = RADEON_GPIOPAD_MASK;
		break;
	case DDC_GPIO:
		ddc_line = RADEON_MDGPIO_MASK;
		break;
	case DDC_MONID:
		if (rdev->family == CHIP_RS300 ||
		    rdev->family == CHIP_RS400 ||
		    rdev->family == CHIP_RS480)
			ddc_line = RADEON_GPIOPAD_MASK;
		else if (rdev->family == CHIP_R300 ||
			 rdev->family == CHIP_R350) {
			ddc_line = RADEON_GPIO_DVI_DDC;
			ddc = DDC_DVI;
		} else
			ddc_line = RADEON_GPIO_MONID;
		break;
	case DDC_CRT2:
		if (rdev->family == CHIP_R200 ||
		    rdev->family == CHIP_R300 ||
		    rdev->family == CHIP_R350) {
			ddc_line = RADEON_GPIO_DVI_DDC;
			ddc = DDC_DVI;
		} else if (rdev->family == CHIP_RS300 ||
			   rdev->family == CHIP_RS400 ||
			   rdev->family == CHIP_RS480)
			ddc_line = RADEON_GPIO_MONID;
		else if (rdev->family >= CHIP_RV350) {
			ddc_line = RADEON_GPIO_MONID;
			ddc = DDC_MONID;
		} else
			ddc_line = RADEON_GPIO_CRT2_DDC;
		break;
	}

	if (ddc_line == RADEON_GPIOPAD_MASK) {
		i2c.mask_clk_reg = RADEON_GPIOPAD_MASK;
		i2c.mask_data_reg = RADEON_GPIOPAD_MASK;
		i2c.a_clk_reg = RADEON_GPIOPAD_A;
		i2c.a_data_reg = RADEON_GPIOPAD_A;
		i2c.en_clk_reg = RADEON_GPIOPAD_EN;
		i2c.en_data_reg = RADEON_GPIOPAD_EN;
		i2c.y_clk_reg = RADEON_GPIOPAD_Y;
		i2c.y_data_reg = RADEON_GPIOPAD_Y;
	} else if (ddc_line == RADEON_MDGPIO_MASK) {
		i2c.mask_clk_reg = RADEON_MDGPIO_MASK;
		i2c.mask_data_reg = RADEON_MDGPIO_MASK;
		i2c.a_clk_reg = RADEON_MDGPIO_A;
		i2c.a_data_reg = RADEON_MDGPIO_A;
		i2c.en_clk_reg = RADEON_MDGPIO_EN;
		i2c.en_data_reg = RADEON_MDGPIO_EN;
		i2c.y_clk_reg = RADEON_MDGPIO_Y;
		i2c.y_data_reg = RADEON_MDGPIO_Y;
	} else {
		i2c.mask_clk_reg = ddc_line;
		i2c.mask_data_reg = ddc_line;
		i2c.a_clk_reg = ddc_line;
		i2c.a_data_reg = ddc_line;
		i2c.en_clk_reg = ddc_line;
		i2c.en_data_reg = ddc_line;
		i2c.y_clk_reg = ddc_line;
		i2c.y_data_reg = ddc_line;
	}

	if (clk_mask && data_mask) {
		/* system specific masks */
		i2c.mask_clk_mask = clk_mask;
		i2c.mask_data_mask = data_mask;
		i2c.a_clk_mask = clk_mask;
		i2c.a_data_mask = data_mask;
		i2c.en_clk_mask = clk_mask;
		i2c.en_data_mask = data_mask;
		i2c.y_clk_mask = clk_mask;
		i2c.y_data_mask = data_mask;
	} else if ((ddc_line == RADEON_GPIOPAD_MASK) ||
		   (ddc_line == RADEON_MDGPIO_MASK)) {
		/* default gpiopad masks */
		i2c.mask_clk_mask = (0x20 << 8);
		i2c.mask_data_mask = 0x80;
		i2c.a_clk_mask = (0x20 << 8);
		i2c.a_data_mask = 0x80;
		i2c.en_clk_mask = (0x20 << 8);
		i2c.en_data_mask = 0x80;
		i2c.y_clk_mask = (0x20 << 8);
		i2c.y_data_mask = 0x80;
	} else {
		/* default masks for ddc pads */
		i2c.mask_clk_mask = RADEON_GPIO_MASK_1;
		i2c.mask_data_mask = RADEON_GPIO_MASK_0;
		i2c.a_clk_mask = RADEON_GPIO_A_1;
		i2c.a_data_mask = RADEON_GPIO_A_0;
		i2c.en_clk_mask = RADEON_GPIO_EN_1;
		i2c.en_data_mask = RADEON_GPIO_EN_0;
		i2c.y_clk_mask = RADEON_GPIO_Y_1;
		i2c.y_data_mask = RADEON_GPIO_Y_0;
	}

	switch (rdev->family) {
	case CHIP_R100:
	case CHIP_RV100:
	case CHIP_RS100:
	case CHIP_RV200:
	case CHIP_RS200:
	case CHIP_RS300:
		switch (ddc_line) {
		case RADEON_GPIO_DVI_DDC:
			i2c.hw_capable = true;
			break;
		default:
			i2c.hw_capable = false;
			break;
		}
		break;
	case CHIP_R200:
		switch (ddc_line) {
		case RADEON_GPIO_DVI_DDC:
		case RADEON_GPIO_MONID:
			i2c.hw_capable = true;
			break;
		default:
			i2c.hw_capable = false;
			break;
		}
		break;
	case CHIP_RV250:
	case CHIP_RV280:
		switch (ddc_line) {
		case RADEON_GPIO_VGA_DDC:
		case RADEON_GPIO_DVI_DDC:
		case RADEON_GPIO_CRT2_DDC:
			i2c.hw_capable = true;
			break;
		default:
			i2c.hw_capable = false;
			break;
		}
		break;
	case CHIP_R300:
	case CHIP_R350:
		switch (ddc_line) {
		case RADEON_GPIO_VGA_DDC:
		case RADEON_GPIO_DVI_DDC:
			i2c.hw_capable = true;
			break;
		default:
			i2c.hw_capable = false;
			break;
		}
		break;
	case CHIP_RV350:
	case CHIP_RV380:
	case CHIP_RS400:
	case CHIP_RS480:
		switch (ddc_line) {
		case RADEON_GPIO_VGA_DDC:
		case RADEON_GPIO_DVI_DDC:
			i2c.hw_capable = true;
			break;
		case RADEON_GPIO_MONID:
			/* hw i2c on RADEON_GPIO_MONID doesn't seem to work
			 * reliably on some pre-r4xx hardware; not sure why.
			 */
			i2c.hw_capable = false;
			break;
		default:
			i2c.hw_capable = false;
			break;
		}
		break;
	default:
		i2c.hw_capable = false;
		break;
	}
	i2c.mm_i2c = false;

	i2c.i2c_id = ddc;
	i2c.hpd = RADEON_HPD_NONE;

	if (ddc_line)
		i2c.valid = true;
	else
		i2c.valid = false;

	return i2c;
}