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
struct sd {int /*<<< orphan*/  quality; int /*<<< orphan*/  jpeg_hdr; } ;
struct gspca_dev {int width; int alt; int usb_err; int /*<<< orphan*/  iface; int /*<<< orphan*/  dev; int /*<<< orphan*/  height; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_STREAM ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jpeg_define (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  jpeg_set_qual (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcv_val (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_par (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  setbrightness (struct gspca_dev*) ; 
 int /*<<< orphan*/  setcolors (struct gspca_dev*) ; 
 int /*<<< orphan*/  setcontrast (struct gspca_dev*) ; 
 int /*<<< orphan*/  setlightfreq (struct gspca_dev*) ; 
 int /*<<< orphan*/  snd_val (struct gspca_dev*,int,int) ; 
 int usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sd_start(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int ret, value;

	/* create the JPEG header */
	jpeg_define(sd->jpeg_hdr, gspca_dev->height, gspca_dev->width,
			0x22);		/* JPEG 411 */
	jpeg_set_qual(sd->jpeg_hdr, sd->quality);

	/* work on alternate 1 */
	usb_set_interface(gspca_dev->dev, gspca_dev->iface, 1);

	set_par(gspca_dev, 0x10000000);
	set_par(gspca_dev, 0x00000000);
	set_par(gspca_dev, 0x8002e001);
	set_par(gspca_dev, 0x14000000);
	if (gspca_dev->width > 320)
		value = 0x8002e001;		/* 640x480 */
	else
		value = 0x4001f000;		/* 320x240 */
	set_par(gspca_dev, value);
	ret = usb_set_interface(gspca_dev->dev,
					gspca_dev->iface,
					gspca_dev->alt);
	if (ret < 0) {
		err("set intf %d %d failed",
			gspca_dev->iface, gspca_dev->alt);
		gspca_dev->usb_err = ret;
		goto out;
	}
	 reg_r(gspca_dev, 0x0630);
	rcv_val(gspca_dev, 0x000020);	/* << (value ff ff ff ff) */
	reg_r(gspca_dev, 0x0650);
	snd_val(gspca_dev, 0x000020, 0xffffffff);
	reg_w(gspca_dev, 0x0620, 0);
	reg_w(gspca_dev, 0x0630, 0);
	reg_w(gspca_dev, 0x0640, 0);
	reg_w(gspca_dev, 0x0650, 0);
	reg_w(gspca_dev, 0x0660, 0);
	setbrightness(gspca_dev);		/* whiteness */
	setcontrast(gspca_dev);			/* contrast */
	setcolors(gspca_dev);			/* saturation */
	set_par(gspca_dev, 0x09800000);		/* Red ? */
	set_par(gspca_dev, 0x0a800000);		/* Green ? */
	set_par(gspca_dev, 0x0b800000);		/* Blue ? */
	set_par(gspca_dev, 0x0d030000);		/* Gamma ? */
	setlightfreq(gspca_dev);

	/* start the video flow */
	set_par(gspca_dev, 0x01000000);
	set_par(gspca_dev, 0x01000000);
	if (gspca_dev->usb_err >= 0)
		PDEBUG(D_STREAM, "camera started alt: 0x%02x",
				gspca_dev->alt);
out:
	return gspca_dev->usb_err;
}