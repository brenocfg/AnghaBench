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
struct saa7134_dev {int /*<<< orphan*/  board; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SAA7134_BOARD_HAUPPAUGE_HVR1120 131 
#define  SAA7134_BOARD_HAUPPAUGE_HVR1150 130 
#define  SAA7134_BOARD_KWORLD_PCI_SBTVD_FULLSEG 129 
#define  TDA18271_CALLBACK_CMD_AGC_ENABLE 128 
 int saa7134_kworld_sbtvd_toggle_agc (struct saa7134_dev*,int) ; 
 int saa7134_tda18271_hvr11x0_toggle_agc (struct saa7134_dev*,int) ; 

__attribute__((used)) static int saa7134_tda8290_18271_callback(struct saa7134_dev *dev,
					  int command, int arg)
{
	int ret = 0;

	switch (command) {
	case TDA18271_CALLBACK_CMD_AGC_ENABLE: /* 0 */
		switch (dev->board) {
		case SAA7134_BOARD_HAUPPAUGE_HVR1150:
		case SAA7134_BOARD_HAUPPAUGE_HVR1120:
			ret = saa7134_tda18271_hvr11x0_toggle_agc(dev, arg);
			break;
		case SAA7134_BOARD_KWORLD_PCI_SBTVD_FULLSEG:
			ret = saa7134_kworld_sbtvd_toggle_agc(dev, arg);
			break;
		default:
			break;
		}
		break;
	default:
		ret = -EINVAL;
		break;
	}
	return ret;
}