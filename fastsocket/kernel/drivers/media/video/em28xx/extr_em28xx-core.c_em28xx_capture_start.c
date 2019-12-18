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
struct TYPE_2__ {scalar_t__ is_webcam; } ;
struct em28xx {scalar_t__ chip_id; scalar_t__ mode; TYPE_1__ board; } ;

/* Variables and functions */
 scalar_t__ CHIP_ID_EM2874 ; 
 int /*<<< orphan*/  EM2874_R5F_TS_ENABLE ; 
 int EM2874_TS1_CAPTURE_ENABLE ; 
 scalar_t__ EM28XX_ANALOG_MODE ; 
 int /*<<< orphan*/  EM28XX_R0C_USBSUSP ; 
 int EM28XX_R12_VINENABLE ; 
 int em28xx_write_reg (struct em28xx*,int,int) ; 
 int em28xx_write_reg_bits (struct em28xx*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

int em28xx_capture_start(struct em28xx *dev, int start)
{
	int rc;

	if (dev->chip_id == CHIP_ID_EM2874) {
		/* The Transport Stream Enable Register moved in em2874 */
		if (!start) {
			rc = em28xx_write_reg_bits(dev, EM2874_R5F_TS_ENABLE,
						   0x00,
						   EM2874_TS1_CAPTURE_ENABLE);
			return rc;
		}

		/* Enable Transport Stream */
		rc = em28xx_write_reg_bits(dev, EM2874_R5F_TS_ENABLE,
					   EM2874_TS1_CAPTURE_ENABLE,
					   EM2874_TS1_CAPTURE_ENABLE);
		return rc;
	}


	/* FIXME: which is the best order? */
	/* video registers are sampled by VREF */
	rc = em28xx_write_reg_bits(dev, EM28XX_R0C_USBSUSP,
				   start ? 0x10 : 0x00, 0x10);
	if (rc < 0)
		return rc;

	if (!start) {
		/* disable video capture */
		rc = em28xx_write_reg(dev, EM28XX_R12_VINENABLE, 0x27);
		return rc;
	}

	if (dev->board.is_webcam)
		rc = em28xx_write_reg(dev, 0x13, 0x0c);

	/* enable video capture */
	rc = em28xx_write_reg(dev, 0x48, 0x00);

	if (dev->mode == EM28XX_ANALOG_MODE)
		rc = em28xx_write_reg(dev, EM28XX_R12_VINENABLE, 0x67);
	else
		rc = em28xx_write_reg(dev, EM28XX_R12_VINENABLE, 0x37);

	msleep(6);

	return rc;
}