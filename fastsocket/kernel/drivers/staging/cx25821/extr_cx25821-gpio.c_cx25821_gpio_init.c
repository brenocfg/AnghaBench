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
struct cx25821_dev {int board; } ;

/* Variables and functions */
#define  CX25821_BOARD_CONEXANT_ATHENA10 128 
 int /*<<< orphan*/  cx25821_set_gpiopin_logicvalue (struct cx25821_dev*,int,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

void cx25821_gpio_init(struct cx25821_dev *dev)
{
	if (dev == NULL) {
		return;
	}

	switch (dev->board) {
	case CX25821_BOARD_CONEXANT_ATHENA10:
	default:
		//set GPIO 5 to select the path for Medusa/Athena
		cx25821_set_gpiopin_logicvalue(dev, 5, 1);
		mdelay(20);
		break;
	}

}