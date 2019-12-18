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
typedef  int u8 ;
struct cx231xx {int model; } ;
typedef  enum AV_MODE { ____Placeholder_AV_MODE } AV_MODE ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_PWRDN_CLAMP_CH1 ; 
 int /*<<< orphan*/  ADC_PWRDN_CLAMP_CH2 ; 
 int /*<<< orphan*/  ADC_PWRDN_CLAMP_CH3 ; 
#define  CX231XX_BOARD_CNXT_CARRAERA 137 
#define  CX231XX_BOARD_CNXT_RDE_250 136 
#define  CX231XX_BOARD_CNXT_RDE_253S 135 
#define  CX231XX_BOARD_CNXT_RDU_250 134 
#define  CX231XX_BOARD_CNXT_RDU_253S 133 
#define  CX231XX_BOARD_CNXT_SHELBY 132 
#define  CX231XX_BOARD_CNXT_VIDEO_GRABBER 131 
#define  CX231XX_BOARD_HAUPPAUGE_EXETER 130 
#define  CX231XX_BOARD_HAUPPAUGE_USBLIVE2 129 
#define  CX231XX_BOARD_PV_PLAYTV_USB_HYBRID 128 
 int FLD_PWRDN_ENABLE_PLL ; 
 int FLD_PWRDN_PD_BANDGAP ; 
 int FLD_PWRDN_PD_BIAS ; 
 int FLD_PWRDN_PD_TUNECK ; 
 int FLD_PWRDN_TUNING_BIAS ; 
 int POLARIS_AVMODE_ANALOGT_TV ; 
 int POLARIS_AVMODE_DIGITAL ; 
 int POLARIS_AVMODE_ENXTERNAL_AV ; 
 int /*<<< orphan*/  SUP_BLK_PWRDN ; 
 int afe_read_byte (struct cx231xx*,int /*<<< orphan*/ ,int*) ; 
 int afe_write_byte (struct cx231xx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cx231xx_info (char*) ; 

int cx231xx_afe_update_power_control(struct cx231xx *dev,
					enum AV_MODE avmode)
{
	u8 afe_power_status = 0;
	int status = 0;

	switch (dev->model) {
	case CX231XX_BOARD_CNXT_CARRAERA:
	case CX231XX_BOARD_CNXT_RDE_250:
	case CX231XX_BOARD_CNXT_SHELBY:
	case CX231XX_BOARD_CNXT_RDU_250:
	case CX231XX_BOARD_CNXT_RDE_253S:
	case CX231XX_BOARD_CNXT_RDU_253S:
	case CX231XX_BOARD_CNXT_VIDEO_GRABBER:
	case CX231XX_BOARD_HAUPPAUGE_EXETER:
	case CX231XX_BOARD_HAUPPAUGE_USBLIVE2:
	case CX231XX_BOARD_PV_PLAYTV_USB_HYBRID:
		if (avmode == POLARIS_AVMODE_ANALOGT_TV) {
			while (afe_power_status != (FLD_PWRDN_TUNING_BIAS |
						FLD_PWRDN_ENABLE_PLL)) {
				status = afe_write_byte(dev, SUP_BLK_PWRDN,
							FLD_PWRDN_TUNING_BIAS |
							FLD_PWRDN_ENABLE_PLL);
				status |= afe_read_byte(dev, SUP_BLK_PWRDN,
							&afe_power_status);
				if (status < 0)
					break;
			}

			status = afe_write_byte(dev, ADC_PWRDN_CLAMP_CH1,
							0x00);
			status |= afe_write_byte(dev, ADC_PWRDN_CLAMP_CH2,
							0x00);
			status |= afe_write_byte(dev, ADC_PWRDN_CLAMP_CH3,
							0x00);
		} else if (avmode == POLARIS_AVMODE_DIGITAL) {
			status = afe_write_byte(dev, ADC_PWRDN_CLAMP_CH1,
							0x70);
			status |= afe_write_byte(dev, ADC_PWRDN_CLAMP_CH2,
							0x70);
			status |= afe_write_byte(dev, ADC_PWRDN_CLAMP_CH3,
							0x70);

			status |= afe_read_byte(dev, SUP_BLK_PWRDN,
						  &afe_power_status);
			afe_power_status |= FLD_PWRDN_PD_BANDGAP |
						FLD_PWRDN_PD_BIAS |
						FLD_PWRDN_PD_TUNECK;
			status |= afe_write_byte(dev, SUP_BLK_PWRDN,
						   afe_power_status);
		} else if (avmode == POLARIS_AVMODE_ENXTERNAL_AV) {
			while (afe_power_status != (FLD_PWRDN_TUNING_BIAS |
						FLD_PWRDN_ENABLE_PLL)) {
				status = afe_write_byte(dev, SUP_BLK_PWRDN,
							FLD_PWRDN_TUNING_BIAS |
							FLD_PWRDN_ENABLE_PLL);
				status |= afe_read_byte(dev, SUP_BLK_PWRDN,
							&afe_power_status);
				if (status < 0)
					break;
			}

			status |= afe_write_byte(dev, ADC_PWRDN_CLAMP_CH1,
						0x00);
			status |= afe_write_byte(dev, ADC_PWRDN_CLAMP_CH2,
						0x00);
			status |= afe_write_byte(dev, ADC_PWRDN_CLAMP_CH3,
						0x00);
		} else {
			cx231xx_info("Invalid AV mode input\n");
			status = -1;
		}
		break;
	default:
		if (avmode == POLARIS_AVMODE_ANALOGT_TV) {
			while (afe_power_status != (FLD_PWRDN_TUNING_BIAS |
						FLD_PWRDN_ENABLE_PLL)) {
				status = afe_write_byte(dev, SUP_BLK_PWRDN,
							FLD_PWRDN_TUNING_BIAS |
							FLD_PWRDN_ENABLE_PLL);
				status |= afe_read_byte(dev, SUP_BLK_PWRDN,
							&afe_power_status);
				if (status < 0)
					break;
			}

			status |= afe_write_byte(dev, ADC_PWRDN_CLAMP_CH1,
							0x40);
			status |= afe_write_byte(dev, ADC_PWRDN_CLAMP_CH2,
							0x40);
			status |= afe_write_byte(dev, ADC_PWRDN_CLAMP_CH3,
							0x00);
		} else if (avmode == POLARIS_AVMODE_DIGITAL) {
			status = afe_write_byte(dev, ADC_PWRDN_CLAMP_CH1,
							0x70);
			status |= afe_write_byte(dev, ADC_PWRDN_CLAMP_CH2,
							0x70);
			status |= afe_write_byte(dev, ADC_PWRDN_CLAMP_CH3,
							0x70);

			status |= afe_read_byte(dev, SUP_BLK_PWRDN,
						       &afe_power_status);
			afe_power_status |= FLD_PWRDN_PD_BANDGAP |
						FLD_PWRDN_PD_BIAS |
						FLD_PWRDN_PD_TUNECK;
			status |= afe_write_byte(dev, SUP_BLK_PWRDN,
							afe_power_status);
		} else if (avmode == POLARIS_AVMODE_ENXTERNAL_AV) {
			while (afe_power_status != (FLD_PWRDN_TUNING_BIAS |
						FLD_PWRDN_ENABLE_PLL)) {
				status = afe_write_byte(dev, SUP_BLK_PWRDN,
							FLD_PWRDN_TUNING_BIAS |
							FLD_PWRDN_ENABLE_PLL);
				status |= afe_read_byte(dev, SUP_BLK_PWRDN,
							&afe_power_status);
				if (status < 0)
					break;
			}

			status |= afe_write_byte(dev, ADC_PWRDN_CLAMP_CH1,
							0x00);
			status |= afe_write_byte(dev, ADC_PWRDN_CLAMP_CH2,
							0x00);
			status |= afe_write_byte(dev, ADC_PWRDN_CLAMP_CH3,
							0x40);
		} else {
			cx231xx_info("Invalid AV mode input\n");
			status = -1;
		}
	}			/* switch  */

	return status;
}