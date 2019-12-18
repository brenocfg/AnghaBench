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
typedef  int /*<<< orphan*/  u8 ;
struct saa7164_dev {int board; TYPE_1__* i2c_bus; } ;
typedef  int /*<<< orphan*/  eeprom ;
struct TYPE_2__ {scalar_t__ i2c_rc; } ;

/* Variables and functions */
#define  SAA7164_BOARD_HAUPPAUGE_HVR2200 133 
#define  SAA7164_BOARD_HAUPPAUGE_HVR2200_2 132 
#define  SAA7164_BOARD_HAUPPAUGE_HVR2200_3 131 
#define  SAA7164_BOARD_HAUPPAUGE_HVR2250 130 
#define  SAA7164_BOARD_HAUPPAUGE_HVR2250_2 129 
#define  SAA7164_BOARD_HAUPPAUGE_HVR2250_3 128 
 int /*<<< orphan*/  hauppauge_eeprom (struct saa7164_dev*,int /*<<< orphan*/ *) ; 
 scalar_t__ saa7164_api_read_eeprom (struct saa7164_dev*,int /*<<< orphan*/ *,int) ; 

void saa7164_card_setup(struct saa7164_dev *dev)
{
	static u8 eeprom[256];

	if (dev->i2c_bus[0].i2c_rc == 0) {
		if (saa7164_api_read_eeprom(dev, &eeprom[0],
			sizeof(eeprom)) < 0)
			return;
	}

	switch (dev->board) {
	case SAA7164_BOARD_HAUPPAUGE_HVR2200:
	case SAA7164_BOARD_HAUPPAUGE_HVR2200_2:
	case SAA7164_BOARD_HAUPPAUGE_HVR2200_3:
	case SAA7164_BOARD_HAUPPAUGE_HVR2250:
	case SAA7164_BOARD_HAUPPAUGE_HVR2250_2:
	case SAA7164_BOARD_HAUPPAUGE_HVR2250_3:
		hauppauge_eeprom(dev, &eeprom[0]);
		break;
	}
}