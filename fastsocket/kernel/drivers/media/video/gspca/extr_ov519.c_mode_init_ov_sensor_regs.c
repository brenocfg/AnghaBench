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
typedef  int u8 ;
struct TYPE_4__ {TYPE_1__* cam_mode; } ;
struct gspca_dev {size_t curr_mode; int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_2__ cam; } ;
struct sd {int sensor; int clockdiv; struct gspca_dev gspca_dev; } ;
struct TYPE_3__ {int priv; } ;

/* Variables and functions */
 int OV7610_REG_COM_C ; 
 int OV7670_COM7_FMT_MASK ; 
 int OV7670_COM7_FMT_QVGA ; 
 int OV7670_COM7_FMT_VGA ; 
 int OV7670_COM8_AWB ; 
 int OV7670_R03_VREF ; 
 int OV7670_R12_COM7 ; 
 int OV7670_R13_COM8 ; 
 int OV7670_R17_HSTART ; 
 int OV7670_R18_HSTOP ; 
 int OV7670_R19_VSTART ; 
 int OV7670_R1A_VSTOP ; 
 int OV7670_R32_HREF ; 
#define  SEN_OV2610 140 
#define  SEN_OV3610 139 
#define  SEN_OV6620 138 
#define  SEN_OV6630 137 
#define  SEN_OV66308AF 136 
#define  SEN_OV7610 135 
#define  SEN_OV7620 134 
#define  SEN_OV7620AE 133 
#define  SEN_OV7640 132 
#define  SEN_OV7648 131 
#define  SEN_OV7670 130 
#define  SEN_OV76BE 129 
#define  SEN_OV8610 128 
 int i2c_r (struct sd*,int) ; 
 int /*<<< orphan*/  i2c_w (struct sd*,int,int) ; 
 int /*<<< orphan*/  i2c_w_mask (struct sd*,int,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void mode_init_ov_sensor_regs(struct sd *sd)
{
	struct gspca_dev *gspca_dev;
	int qvga, xstart, xend, ystart, yend;
	u8 v;

	gspca_dev = &sd->gspca_dev;
	qvga = gspca_dev->cam.cam_mode[gspca_dev->curr_mode].priv & 1;

	/******** Mode (VGA/QVGA) and sensor specific regs ********/
	switch (sd->sensor) {
	case SEN_OV2610:
		i2c_w_mask(sd, 0x14, qvga ? 0x20 : 0x00, 0x20);
		i2c_w_mask(sd, 0x28, qvga ? 0x00 : 0x20, 0x20);
		i2c_w(sd, 0x24, qvga ? 0x20 : 0x3a);
		i2c_w(sd, 0x25, qvga ? 0x30 : 0x60);
		i2c_w_mask(sd, 0x2d, qvga ? 0x40 : 0x00, 0x40);
		i2c_w_mask(sd, 0x67, qvga ? 0xf0 : 0x90, 0xf0);
		i2c_w_mask(sd, 0x74, qvga ? 0x20 : 0x00, 0x20);
		return;
	case SEN_OV3610:
		if (qvga) {
			xstart = (1040 - gspca_dev->width) / 2 + (0x1f << 4);
			ystart = (776 - gspca_dev->height) / 2;
		} else {
			xstart = (2076 - gspca_dev->width) / 2 + (0x10 << 4);
			ystart = (1544 - gspca_dev->height) / 2;
		}
		xend = xstart + gspca_dev->width;
		yend = ystart + gspca_dev->height;
		/* Writing to the COMH register resets the other windowing regs
		   to their default values, so we must do this first. */
		i2c_w_mask(sd, 0x12, qvga ? 0x40 : 0x00, 0xf0);
		i2c_w_mask(sd, 0x32,
			   (((xend >> 1) & 7) << 3) | ((xstart >> 1) & 7),
			   0x3f);
		i2c_w_mask(sd, 0x03,
			   (((yend >> 1) & 3) << 2) | ((ystart >> 1) & 3),
			   0x0f);
		i2c_w(sd, 0x17, xstart >> 4);
		i2c_w(sd, 0x18, xend >> 4);
		i2c_w(sd, 0x19, ystart >> 3);
		i2c_w(sd, 0x1a, yend >> 3);
		return;
	case SEN_OV8610:
		/* For OV8610 qvga means qsvga */
		i2c_w_mask(sd, OV7610_REG_COM_C, qvga ? (1 << 5) : 0, 1 << 5);
		i2c_w_mask(sd, 0x13, 0x00, 0x20); /* Select 16 bit data bus */
		i2c_w_mask(sd, 0x12, 0x04, 0x06); /* AWB: 1 Test pattern: 0 */
		i2c_w_mask(sd, 0x2d, 0x00, 0x40); /* from windrv 090403 */
		i2c_w_mask(sd, 0x28, 0x20, 0x20); /* progressive mode on */
		break;
	case SEN_OV7610:
		i2c_w_mask(sd, 0x14, qvga ? 0x20 : 0x00, 0x20);
		i2c_w(sd, 0x35, qvga ? 0x1e : 0x9e);
		i2c_w_mask(sd, 0x13, 0x00, 0x20); /* Select 16 bit data bus */
		i2c_w_mask(sd, 0x12, 0x04, 0x06); /* AWB: 1 Test pattern: 0 */
		break;
	case SEN_OV7620:
	case SEN_OV7620AE:
	case SEN_OV76BE:
		i2c_w_mask(sd, 0x14, qvga ? 0x20 : 0x00, 0x20);
		i2c_w_mask(sd, 0x28, qvga ? 0x00 : 0x20, 0x20);
		i2c_w(sd, 0x24, qvga ? 0x20 : 0x3a);
		i2c_w(sd, 0x25, qvga ? 0x30 : 0x60);
		i2c_w_mask(sd, 0x2d, qvga ? 0x40 : 0x00, 0x40);
		i2c_w_mask(sd, 0x67, qvga ? 0xb0 : 0x90, 0xf0);
		i2c_w_mask(sd, 0x74, qvga ? 0x20 : 0x00, 0x20);
		i2c_w_mask(sd, 0x13, 0x00, 0x20); /* Select 16 bit data bus */
		i2c_w_mask(sd, 0x12, 0x04, 0x06); /* AWB: 1 Test pattern: 0 */
		if (sd->sensor == SEN_OV76BE)
			i2c_w(sd, 0x35, qvga ? 0x1e : 0x9e);
		break;
	case SEN_OV7640:
	case SEN_OV7648:
		i2c_w_mask(sd, 0x14, qvga ? 0x20 : 0x00, 0x20);
		i2c_w_mask(sd, 0x28, qvga ? 0x00 : 0x20, 0x20);
		/* Setting this undocumented bit in qvga mode removes a very
		   annoying vertical shaking of the image */
		i2c_w_mask(sd, 0x2d, qvga ? 0x40 : 0x00, 0x40);
		/* Unknown */
		i2c_w_mask(sd, 0x67, qvga ? 0xf0 : 0x90, 0xf0);
		/* Allow higher automatic gain (to allow higher framerates) */
		i2c_w_mask(sd, 0x74, qvga ? 0x20 : 0x00, 0x20);
		i2c_w_mask(sd, 0x12, 0x04, 0x04); /* AWB: 1 */
		break;
	case SEN_OV7670:
		/* set COM7_FMT_VGA or COM7_FMT_QVGA
		 * do we need to set anything else?
		 *	HSTART etc are set in set_ov_sensor_window itself */
		i2c_w_mask(sd, OV7670_R12_COM7,
			 qvga ? OV7670_COM7_FMT_QVGA : OV7670_COM7_FMT_VGA,
			 OV7670_COM7_FMT_MASK);
		i2c_w_mask(sd, 0x13, 0x00, 0x20); /* Select 16 bit data bus */
		i2c_w_mask(sd, OV7670_R13_COM8, OV7670_COM8_AWB,
				OV7670_COM8_AWB);
		if (qvga) {		/* QVGA from ov7670.c by
					 * Jonathan Corbet */
			xstart = 164;
			xend = 28;
			ystart = 14;
			yend = 494;
		} else {		/* VGA */
			xstart = 158;
			xend = 14;
			ystart = 10;
			yend = 490;
		}
		/* OV7670 hardware window registers are split across
		 * multiple locations */
		i2c_w(sd, OV7670_R17_HSTART, xstart >> 3);
		i2c_w(sd, OV7670_R18_HSTOP, xend >> 3);
		v = i2c_r(sd, OV7670_R32_HREF);
		v = (v & 0xc0) | ((xend & 0x7) << 3) | (xstart & 0x07);
		msleep(10);	/* need to sleep between read and write to
				 * same reg! */
		i2c_w(sd, OV7670_R32_HREF, v);

		i2c_w(sd, OV7670_R19_VSTART, ystart >> 2);
		i2c_w(sd, OV7670_R1A_VSTOP, yend >> 2);
		v = i2c_r(sd, OV7670_R03_VREF);
		v = (v & 0xc0) | ((yend & 0x3) << 2) | (ystart & 0x03);
		msleep(10);	/* need to sleep between read and write to
				 * same reg! */
		i2c_w(sd, OV7670_R03_VREF, v);
		break;
	case SEN_OV6620:
		i2c_w_mask(sd, 0x14, qvga ? 0x20 : 0x00, 0x20);
		i2c_w_mask(sd, 0x13, 0x00, 0x20); /* Select 16 bit data bus */
		i2c_w_mask(sd, 0x12, 0x04, 0x06); /* AWB: 1 Test pattern: 0 */
		break;
	case SEN_OV6630:
	case SEN_OV66308AF:
		i2c_w_mask(sd, 0x14, qvga ? 0x20 : 0x00, 0x20);
		i2c_w_mask(sd, 0x12, 0x04, 0x06); /* AWB: 1 Test pattern: 0 */
		break;
	default:
		return;
	}

	/******** Clock programming ********/
	i2c_w(sd, 0x11, sd->clockdiv);
}