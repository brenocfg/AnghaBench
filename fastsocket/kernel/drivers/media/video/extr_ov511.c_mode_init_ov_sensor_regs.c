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
struct usb_ov511 {int sensor; scalar_t__ bridge; int subw; int subh; scalar_t__ compress; } ;

/* Variables and functions */
 scalar_t__ BRG_OV518 ; 
 int EINVAL ; 
 int /*<<< orphan*/  PDEBUG (int,char*,int) ; 
#define  SEN_OV6620 132 
#define  SEN_OV6630 131 
#define  SEN_OV7610 130 
#define  SEN_OV7620 129 
#define  SEN_OV76BE 128 
 int VIDEO_PALETTE_GREY ; 
 int clockdiv ; 
 int /*<<< orphan*/  err (char*) ; 
 int framedrop ; 
 int /*<<< orphan*/  i2c_w (struct usb_ov511*,int,int) ; 
 int /*<<< orphan*/  i2c_w_mask (struct usb_ov511*,int,int,int) ; 
 scalar_t__ ov518_color ; 
 scalar_t__ testpat ; 

__attribute__((used)) static int
mode_init_ov_sensor_regs(struct usb_ov511 *ov, int width, int height,
			 int mode, int sub_flag, int qvga)
{
	int clock;

	/******** Mode (VGA/QVGA) and sensor specific regs ********/

	switch (ov->sensor) {
	case SEN_OV7610:
		i2c_w(ov, 0x14, qvga?0x24:0x04);
// FIXME: Does this improve the image quality or frame rate?
#if 0
		i2c_w_mask(ov, 0x28, qvga?0x00:0x20, 0x20);
		i2c_w(ov, 0x24, 0x10);
		i2c_w(ov, 0x25, qvga?0x40:0x8a);
		i2c_w(ov, 0x2f, qvga?0x30:0xb0);
		i2c_w(ov, 0x35, qvga?0x1c:0x9c);
#endif
		break;
	case SEN_OV7620:
//		i2c_w(ov, 0x2b, 0x00);
		i2c_w(ov, 0x14, qvga?0xa4:0x84);
		i2c_w_mask(ov, 0x28, qvga?0x00:0x20, 0x20);
		i2c_w(ov, 0x24, qvga?0x20:0x3a);
		i2c_w(ov, 0x25, qvga?0x30:0x60);
		i2c_w_mask(ov, 0x2d, qvga?0x40:0x00, 0x40);
		i2c_w_mask(ov, 0x67, qvga?0xf0:0x90, 0xf0);
		i2c_w_mask(ov, 0x74, qvga?0x20:0x00, 0x20);
		break;
	case SEN_OV76BE:
//		i2c_w(ov, 0x2b, 0x00);
		i2c_w(ov, 0x14, qvga?0xa4:0x84);
// FIXME: Enable this once 7620AE uses 7620 initial settings
#if 0
		i2c_w_mask(ov, 0x28, qvga?0x00:0x20, 0x20);
		i2c_w(ov, 0x24, qvga?0x20:0x3a);
		i2c_w(ov, 0x25, qvga?0x30:0x60);
		i2c_w_mask(ov, 0x2d, qvga?0x40:0x00, 0x40);
		i2c_w_mask(ov, 0x67, qvga?0xb0:0x90, 0xf0);
		i2c_w_mask(ov, 0x74, qvga?0x20:0x00, 0x20);
#endif
		break;
	case SEN_OV6620:
		i2c_w(ov, 0x14, qvga?0x24:0x04);
		break;
	case SEN_OV6630:
		i2c_w(ov, 0x14, qvga?0xa0:0x80);
		break;
	default:
		err("Invalid sensor");
		return -EINVAL;
	}

	/******** Palette-specific regs ********/

	if (mode == VIDEO_PALETTE_GREY) {
		if (ov->sensor == SEN_OV7610 || ov->sensor == SEN_OV76BE) {
			/* these aren't valid on the OV6620/OV7620/6630? */
			i2c_w_mask(ov, 0x0e, 0x40, 0x40);
		}

		if (ov->sensor == SEN_OV6630 && ov->bridge == BRG_OV518
		    && ov518_color) {
			i2c_w_mask(ov, 0x12, 0x00, 0x10);
			i2c_w_mask(ov, 0x13, 0x00, 0x20);
		} else {
			i2c_w_mask(ov, 0x13, 0x20, 0x20);
		}
	} else {
		if (ov->sensor == SEN_OV7610 || ov->sensor == SEN_OV76BE) {
			/* not valid on the OV6620/OV7620/6630? */
			i2c_w_mask(ov, 0x0e, 0x00, 0x40);
		}

		/* The OV518 needs special treatment. Although both the OV518
		 * and the OV6630 support a 16-bit video bus, only the 8 bit Y
		 * bus is actually used. The UV bus is tied to ground.
		 * Therefore, the OV6630 needs to be in 8-bit multiplexed
		 * output mode */

		if (ov->sensor == SEN_OV6630 && ov->bridge == BRG_OV518
		    && ov518_color) {
			i2c_w_mask(ov, 0x12, 0x10, 0x10);
			i2c_w_mask(ov, 0x13, 0x20, 0x20);
		} else {
			i2c_w_mask(ov, 0x13, 0x00, 0x20);
		}
	}

	/******** Clock programming ********/

	/* The OV6620 needs special handling. This prevents the
	 * severe banding that normally occurs */
	if (ov->sensor == SEN_OV6620 || ov->sensor == SEN_OV6630)
	{
		/* Clock down */

		i2c_w(ov, 0x2a, 0x04);

		if (ov->compress) {
//			clock = 0;    /* This ensures the highest frame rate */
			clock = 3;
		} else if (clockdiv == -1) {   /* If user didn't override it */
			clock = 3;    /* Gives better exposure time */
		} else {
			clock = clockdiv;
		}

		PDEBUG(4, "Setting clock divisor to %d", clock);

		i2c_w(ov, 0x11, clock);

		i2c_w(ov, 0x2a, 0x84);
		/* This next setting is critical. It seems to improve
		 * the gain or the contrast. The "reserved" bits seem
		 * to have some effect in this case. */
		i2c_w(ov, 0x2d, 0x85);
	}
	else
	{
		if (ov->compress) {
			clock = 1;    /* This ensures the highest frame rate */
		} else if (clockdiv == -1) {   /* If user didn't override it */
			/* Calculate and set the clock divisor */
			clock = ((sub_flag ? ov->subw * ov->subh
				  : width * height)
				 * (mode == VIDEO_PALETTE_GREY ? 2 : 3) / 2)
				 / 66000;
		} else {
			clock = clockdiv;
		}

		PDEBUG(4, "Setting clock divisor to %d", clock);

		i2c_w(ov, 0x11, clock);
	}

	/******** Special Features ********/

	if (framedrop >= 0)
		i2c_w(ov, 0x16, framedrop);

	/* Test Pattern */
	i2c_w_mask(ov, 0x12, (testpat?0x02:0x00), 0x02);

	/* Enable auto white balance */
	i2c_w_mask(ov, 0x12, 0x04, 0x04);

	// This will go away as soon as ov51x_mode_init_sensor_regs()
	// is fully tested.
	/* 7620/6620/6630? don't have register 0x35, so play it safe */
	if (ov->sensor == SEN_OV7610 || ov->sensor == SEN_OV76BE) {
		if (width == 640 && height == 480)
			i2c_w(ov, 0x35, 0x9e);
		else
			i2c_w(ov, 0x35, 0x1e);
	}

	return 0;
}