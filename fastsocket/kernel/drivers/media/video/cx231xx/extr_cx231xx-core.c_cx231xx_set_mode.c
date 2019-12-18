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
struct cx231xx {int mode; int model; } ;
typedef  enum cx231xx_mode { ____Placeholder_cx231xx_mode } cx231xx_mode ;

/* Variables and functions */
#define  CX231XX_BOARD_CNXT_CARRAERA 135 
#define  CX231XX_BOARD_CNXT_RDE_250 134 
#define  CX231XX_BOARD_CNXT_RDE_253S 133 
#define  CX231XX_BOARD_CNXT_RDU_250 132 
#define  CX231XX_BOARD_CNXT_RDU_253S 131 
#define  CX231XX_BOARD_CNXT_SHELBY 130 
#define  CX231XX_BOARD_HAUPPAUGE_EXETER 129 
#define  CX231XX_BOARD_PV_PLAYTV_USB_HYBRID 128 
 scalar_t__ CX231XX_DIGITAL_MODE ; 
 int CX231XX_SUSPEND ; 
 int EINVAL ; 
 int /*<<< orphan*/  POLARIS_AVMODE_DIGITAL ; 
 int cx231xx_set_agc_analog_digital_mux_select (struct cx231xx*,int) ; 
 int cx231xx_set_power_mode (struct cx231xx*,int /*<<< orphan*/ ) ; 

int cx231xx_set_mode(struct cx231xx *dev, enum cx231xx_mode set_mode)
{
	int errCode = 0;

	if (dev->mode == set_mode)
		return 0;

	if (set_mode == CX231XX_SUSPEND) {
		/* Set the chip in power saving mode */
		dev->mode = set_mode;
	}

	/* Resource is locked */
	if (dev->mode != CX231XX_SUSPEND)
		return -EINVAL;

	dev->mode = set_mode;

	if (dev->mode == CX231XX_DIGITAL_MODE)/* Set Digital power mode */ {
	/* set AGC mode to Digital */
		switch (dev->model) {
		case CX231XX_BOARD_CNXT_CARRAERA:
		case CX231XX_BOARD_CNXT_RDE_250:
		case CX231XX_BOARD_CNXT_SHELBY:
		case CX231XX_BOARD_CNXT_RDU_250:
		errCode = cx231xx_set_agc_analog_digital_mux_select(dev, 0);
			break;
		case CX231XX_BOARD_CNXT_RDE_253S:
		case CX231XX_BOARD_CNXT_RDU_253S:
			errCode = cx231xx_set_agc_analog_digital_mux_select(dev, 1);
			break;
		case CX231XX_BOARD_HAUPPAUGE_EXETER:
			errCode = cx231xx_set_power_mode(dev,
						POLARIS_AVMODE_DIGITAL);
			break;
		default:
			break;
		}
	} else/* Set Analog Power mode */ {
	/* set AGC mode to Analog */
		switch (dev->model) {
		case CX231XX_BOARD_CNXT_CARRAERA:
		case CX231XX_BOARD_CNXT_RDE_250:
		case CX231XX_BOARD_CNXT_SHELBY:
		case CX231XX_BOARD_CNXT_RDU_250:
		errCode = cx231xx_set_agc_analog_digital_mux_select(dev, 1);
			break;
		case CX231XX_BOARD_CNXT_RDE_253S:
		case CX231XX_BOARD_CNXT_RDU_253S:
		case CX231XX_BOARD_HAUPPAUGE_EXETER:
		case CX231XX_BOARD_PV_PLAYTV_USB_HYBRID:
		errCode = cx231xx_set_agc_analog_digital_mux_select(dev, 0);
			break;
		default:
			break;
		}
	}

	return 0;
}