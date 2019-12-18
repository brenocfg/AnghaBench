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
struct usb_ov511 {int sensor; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PDEBUG (int,char*,int) ; 
#define  SEN_SAA7111A 128 
 int VIDEO_MODE_AUTO ; 
 int VIDEO_MODE_NTSC ; 
 int VIDEO_MODE_PAL ; 
 int VIDEO_MODE_SECAM ; 
 int /*<<< orphan*/  i2c_w_mask (struct usb_ov511*,int,int,int) ; 

__attribute__((used)) static int
decoder_set_norm(struct usb_ov511 *ov, int norm)
{
	PDEBUG(4, "%d", norm);

	switch (ov->sensor) {
	case SEN_SAA7111A:
	{
		int reg_8, reg_e;

		if (norm == VIDEO_MODE_NTSC) {
			reg_8 = 0x40;	/* 60 Hz */
			reg_e = 0x00;	/* NTSC M / PAL BGHI */
		} else if (norm == VIDEO_MODE_PAL) {
			reg_8 = 0x00;	/* 50 Hz */
			reg_e = 0x00;	/* NTSC M / PAL BGHI */
		} else if (norm == VIDEO_MODE_AUTO) {
			reg_8 = 0x80;	/* Auto field detect */
			reg_e = 0x00;	/* NTSC M / PAL BGHI */
		} else if (norm == VIDEO_MODE_SECAM) {
			reg_8 = 0x00;	/* 50 Hz */
			reg_e = 0x50;	/* SECAM / PAL 4.43 */
		} else {
			return -EINVAL;
		}

		i2c_w_mask(ov, 0x08, reg_8, 0xc0);
		i2c_w_mask(ov, 0x0e, reg_e, 0x70);
		break;
	}
	default:
		return -EINVAL;
	}

	return 0;
}