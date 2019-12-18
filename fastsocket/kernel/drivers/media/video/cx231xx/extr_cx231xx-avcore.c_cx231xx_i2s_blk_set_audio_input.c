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
struct cx231xx {int ctl_ainput; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_PWR_CTRL1 ; 
 int /*<<< orphan*/  CH_PWR_CTRL2 ; 
#define  CX231XX_AMUX_LINE_IN 129 
#define  CX231XX_AMUX_VIDEO 128 
 int /*<<< orphan*/  I2S_BLK_DEVICE_ADDRESS ; 
 int cx231xx_write_i2c_data (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

int cx231xx_i2s_blk_set_audio_input(struct cx231xx *dev, u8 audio_input)
{
	int status = 0;

	switch (audio_input) {
	case CX231XX_AMUX_LINE_IN:
		status = cx231xx_write_i2c_data(dev, I2S_BLK_DEVICE_ADDRESS,
						CH_PWR_CTRL2, 1, 0x00, 1);
		status = cx231xx_write_i2c_data(dev, I2S_BLK_DEVICE_ADDRESS,
						CH_PWR_CTRL1, 1, 0x80, 1);
		break;
	case CX231XX_AMUX_VIDEO:
	default:
		break;
	}

	dev->ctl_ainput = audio_input;

	return status;
}