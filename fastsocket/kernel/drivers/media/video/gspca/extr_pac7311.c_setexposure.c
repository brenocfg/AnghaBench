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
struct sd {int exposure; } ;
struct TYPE_4__ {TYPE_1__* cam_mode; } ;
struct gspca_dev {scalar_t__ curr_mode; TYPE_2__ cam; } ;
typedef  int __u8 ;
struct TYPE_3__ {scalar_t__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void setexposure(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	__u8 reg;

	/* register 2 of frame 3/4 contains the clock divider configuring the
	   no fps according to the formula: 60 / reg. sd->exposure is the
	   desired exposure time in ms. */
	reg = 120 * sd->exposure / 1000;
	if (reg < 2)
		reg = 2;
	else if (reg > 63)
		reg = 63;

	reg_w(gspca_dev, 0xff, 0x04);			/* page 4 */
	reg_w(gspca_dev, 0x02, reg);

	/* Page 1 register 8 must always be 0x08 except when not in
	   640x480 mode and Page3/4 reg 2 <= 3 then it must be 9 */
	reg_w(gspca_dev, 0xff, 0x01);
	if (gspca_dev->cam.cam_mode[(int)gspca_dev->curr_mode].priv &&
			reg <= 3) {
		reg_w(gspca_dev, 0x08, 0x09);
	} else {
		reg_w(gspca_dev, 0x08, 0x08);
	}

	/* load registers to sensor (Bit 0, auto clear) */
	reg_w(gspca_dev, 0x11, 0x01);
}