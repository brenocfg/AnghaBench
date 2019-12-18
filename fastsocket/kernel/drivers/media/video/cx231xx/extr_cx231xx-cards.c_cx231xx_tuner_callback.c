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
struct TYPE_4__ {TYPE_1__* tuner_gpio; } ;
struct cx231xx {scalar_t__ tuner_type; int /*<<< orphan*/  model; TYPE_2__ board; } ;
struct TYPE_3__ {int /*<<< orphan*/  bit; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX231XX_BOARD_PV_PLAYTV_USB_HYBRID ; 
 int EINVAL ; 
#define  TDA18271_CALLBACK_CMD_AGC_ENABLE 128 
 scalar_t__ TUNER_NXP_TDA18271 ; 
 scalar_t__ TUNER_XC5000 ; 
 int XC5000_TUNER_RESET ; 
 int /*<<< orphan*/  cx231xx_info (char*,int,scalar_t__) ; 
 int cx231xx_set_agc_analog_digital_mux_select (struct cx231xx*,int) ; 
 int /*<<< orphan*/  cx231xx_set_gpio_value (struct cx231xx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

int cx231xx_tuner_callback(void *ptr, int component, int command, int arg)
{
	int rc = 0;
	struct cx231xx *dev = ptr;

	if (dev->tuner_type == TUNER_XC5000) {
		if (command == XC5000_TUNER_RESET) {
			cx231xx_info
				("Tuner CB: RESET: cmd %d : tuner type %d \n",
				 command, dev->tuner_type);
			cx231xx_set_gpio_value(dev, dev->board.tuner_gpio->bit,
					       1);
			msleep(10);
			cx231xx_set_gpio_value(dev, dev->board.tuner_gpio->bit,
					       0);
			msleep(330);
			cx231xx_set_gpio_value(dev, dev->board.tuner_gpio->bit,
					       1);
			msleep(10);
		}
	} else if (dev->tuner_type == TUNER_NXP_TDA18271) {
		switch (command) {
		case TDA18271_CALLBACK_CMD_AGC_ENABLE:
			if (dev->model == CX231XX_BOARD_PV_PLAYTV_USB_HYBRID)
				rc = cx231xx_set_agc_analog_digital_mux_select(dev, arg);
			break;
		default:
			rc = -EINVAL;
			break;
		}
	}
	return rc;
}