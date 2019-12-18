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
typedef  int u8 ;
struct sd {TYPE_1__* ctrls; int /*<<< orphan*/  quality; int /*<<< orphan*/  jpeg_hdr; } ;
struct gspca_dev {int height; int width; int* usb_buf; int usb_err; scalar_t__ ctrl_inac; } ;
struct TYPE_2__ {int val; } ;

/* Variables and functions */
 size_t BRIGHTNESS ; 
 size_t COLORS ; 
 size_t GAMMA ; 
 size_t SHARPNESS ; 
 int /*<<< orphan*/  jpeg_define (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  jpeg_set_qual (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mi_data ; 
 int /*<<< orphan*/  mi_w (struct gspca_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int) ; 

__attribute__((used)) static int sd_start(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 *data;
	int i;

	/* create the JPEG header */
	jpeg_define(sd->jpeg_hdr, gspca_dev->height, gspca_dev->width,
			0x21);		/* JPEG 422 */
	jpeg_set_qual(sd->jpeg_hdr, sd->quality);

	data = gspca_dev->usb_buf;

	data[0] = 0x01;		/* address */
	data[1] = 0x01;
	reg_w(gspca_dev, 2);

	/*
	   Initialize the MR97113 chip register
	 */
	data[0] = 0x00;		/* address */
	data[1] = 0x0c | 0x01;	/* reg 0 */
	data[2] = 0x01;		/* reg 1 */
	data[3] = gspca_dev->width / 8;		/* h_size , reg 2 */
	data[4] = gspca_dev->height / 8;	/* v_size , reg 3 */
	data[5] = 0x30;		/* reg 4, MI, PAS5101 :
				 *	0x30 for 24mhz , 0x28 for 12mhz */
	data[6] = 0x02;		/* reg 5, H start - was 0x04 */
	data[7] = sd->ctrls[GAMMA].val * 0x40;	/* reg 0x06: gamma */
	data[8] = 0x01;		/* reg 7, V start - was 0x03 */
/*	if (h_size == 320 ) */
/*		data[9]= 0x56;	 * reg 8, 24MHz, 2:1 scale down */
/*	else */
	data[9] = 0x52;		/* reg 8, 24MHz, no scale down */
/*jfm: from win trace*/
	data[10] = 0x18;

	reg_w(gspca_dev, 11);

	data[0] = 0x23;		/* address */
	data[1] = 0x09;		/* reg 35, append frame header */

	reg_w(gspca_dev, 2);

	data[0] = 0x3c;		/* address */
/*	if (gspca_dev->width == 1280) */
/*		data[1] = 200;	 * reg 60, pc-cam frame size
				 *	(unit: 4KB) 800KB */
/*	else */
	data[1] = 50;		/* 50 reg 60, pc-cam frame size
				 *	(unit: 4KB) 200KB */
	reg_w(gspca_dev, 2);

	/* auto dark-gain */
	data[0] = 0x5e;		/* address */
	data[1] = 0;		/* reg 94, Y Gain (auto) */
/*jfm: from win trace*/
				/* reg 0x5f/0x60 (LE) = saturation */
				/* h (60): xxxx x100
				 * l (5f): xxxx x000 */
	data[2] = sd->ctrls[COLORS].val << 3;
	data[3] = ((sd->ctrls[COLORS].val >> 2) & 0xf8) | 0x04;
	data[4] = sd->ctrls[BRIGHTNESS].val; /* reg 0x61 = brightness */
	data[5] = 0x00;

	reg_w(gspca_dev, 6);

	data[0] = 0x67;
/*jfm: from win trace*/
	data[1] = sd->ctrls[SHARPNESS].val * 4 + 3;
	data[2] = 0x14;
	reg_w(gspca_dev, 3);

	data[0] = 0x69;
	data[1] = 0x2f;
	data[2] = 0x28;
	data[3] = 0x42;
	reg_w(gspca_dev, 4);

	data[0] = 0x63;
	data[1] = 0x07;
	reg_w(gspca_dev, 2);
/*jfm: win trace - many writes here to reg 0x64*/

	/* initialize the MI sensor */
	for (i = 0; i < sizeof mi_data; i++)
		mi_w(gspca_dev, i + 1, mi_data[i]);

	data[0] = 0x00;
	data[1] = 0x4d;		/* ISOC transfering enable... */
	reg_w(gspca_dev, 2);

	gspca_dev->ctrl_inac = 0; /* activate the illuminator controls */
	return gspca_dev->usb_err;
}