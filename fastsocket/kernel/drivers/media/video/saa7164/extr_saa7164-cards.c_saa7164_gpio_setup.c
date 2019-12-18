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
struct saa7164_dev {int board; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIEBRIDGE_UNITID ; 
#define  SAA7164_BOARD_HAUPPAUGE_HVR2200 133 
#define  SAA7164_BOARD_HAUPPAUGE_HVR2200_2 132 
#define  SAA7164_BOARD_HAUPPAUGE_HVR2200_3 131 
#define  SAA7164_BOARD_HAUPPAUGE_HVR2250 130 
#define  SAA7164_BOARD_HAUPPAUGE_HVR2250_2 129 
#define  SAA7164_BOARD_HAUPPAUGE_HVR2250_3 128 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  saa7164_api_clear_gpiobit (struct saa7164_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  saa7164_api_set_gpiobit (struct saa7164_dev*,int /*<<< orphan*/ ,int) ; 

void saa7164_gpio_setup(struct saa7164_dev *dev)
{
	switch (dev->board) {
	case SAA7164_BOARD_HAUPPAUGE_HVR2200:
	case SAA7164_BOARD_HAUPPAUGE_HVR2200_2:
	case SAA7164_BOARD_HAUPPAUGE_HVR2200_3:
	case SAA7164_BOARD_HAUPPAUGE_HVR2250:
	case SAA7164_BOARD_HAUPPAUGE_HVR2250_2:
	case SAA7164_BOARD_HAUPPAUGE_HVR2250_3:
		/*
		GPIO 2: s5h1411 / tda10048-1 demod reset
		GPIO 3: s5h1411 / tda10048-2 demod reset
		GPIO 7: IRBlaster Zilog reset
		 */

		/* Reset parts by going in and out of reset */
		saa7164_api_clear_gpiobit(dev, PCIEBRIDGE_UNITID, 2);
		saa7164_api_clear_gpiobit(dev, PCIEBRIDGE_UNITID, 3);

		msleep(20);

		saa7164_api_set_gpiobit(dev, PCIEBRIDGE_UNITID, 2);
		saa7164_api_set_gpiobit(dev, PCIEBRIDGE_UNITID, 3);
		break;
	}
}