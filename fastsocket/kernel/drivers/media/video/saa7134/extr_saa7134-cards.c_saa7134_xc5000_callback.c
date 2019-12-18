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
struct saa7134_dev {int board; } ;

/* Variables and functions */
 int SAA7133_ANALOG_IO_SELECT ; 
 int SAA7134_ANALOG_IN_CTRL1 ; 
 int SAA7134_AUDIO_CLOCK0 ; 
 int SAA7134_AUDIO_CLOCKS_PER_FIELD0 ; 
 int SAA7134_AUDIO_PLL_CTRL ; 
#define  SAA7134_BOARD_BEHOLD_A7 130 
#define  SAA7134_BOARD_BEHOLD_H7 129 
#define  SAA7134_BOARD_BEHOLD_X7 128 
 int SAA7134_GPIO_GPMODE0 ; 
 int SAA7134_GPIO_GPSTATUS0 ; 
 int /*<<< orphan*/  SAA7134_SPECIAL_MODE ; 
 int XC5000_TUNER_RESET ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  saa_andorl (int,int,int) ; 
 int /*<<< orphan*/  saa_writeb (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int saa7134_xc5000_callback(struct saa7134_dev *dev,
				   int command, int arg)
{
	switch (dev->board) {
	case SAA7134_BOARD_BEHOLD_X7:
	case SAA7134_BOARD_BEHOLD_H7:
	case SAA7134_BOARD_BEHOLD_A7:
		if (command == XC5000_TUNER_RESET) {
		/* Down and UP pheripherial RESET pin for reset all chips */
			saa_writeb(SAA7134_SPECIAL_MODE, 0x00);
			msleep(10);
			saa_writeb(SAA7134_SPECIAL_MODE, 0x01);
			msleep(10);
		}
		break;
	default:
		saa_andorl(SAA7134_GPIO_GPMODE0 >> 2, 0x06e20000, 0x06e20000);
		saa_andorl(SAA7134_GPIO_GPSTATUS0 >> 2, 0x06a20000, 0x06a20000);
		saa_andorl(SAA7133_ANALOG_IO_SELECT >> 2, 0x02, 0x02);
		saa_andorl(SAA7134_ANALOG_IN_CTRL1 >> 2, 0x81, 0x81);
		saa_andorl(SAA7134_AUDIO_CLOCK0 >> 2, 0x03187de7, 0x03187de7);
		saa_andorl(SAA7134_AUDIO_PLL_CTRL >> 2, 0x03, 0x03);
		saa_andorl(SAA7134_AUDIO_CLOCKS_PER_FIELD0 >> 2,
			   0x0001e000, 0x0001e000);
		break;
	}
	return 0;
}