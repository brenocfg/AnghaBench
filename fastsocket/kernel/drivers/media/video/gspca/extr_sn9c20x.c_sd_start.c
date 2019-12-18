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
struct sd {int /*<<< orphan*/  vstart; int /*<<< orphan*/  hstart; int /*<<< orphan*/ * jpeg_hdr; int /*<<< orphan*/  quality; } ;
struct TYPE_4__ {TYPE_1__* cam_mode; } ;
struct gspca_dev {int width; int height; int* usb_buf; scalar_t__ curr_mode; TYPE_2__ cam; } ;
struct TYPE_3__ {int priv; } ;

/* Variables and functions */
 int /*<<< orphan*/ * CLR_WIN (int,int) ; 
 int /*<<< orphan*/ * HW_WIN (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t JPEG_QT0_OFFSET ; 
 size_t JPEG_QT1_OFFSET ; 
 int MODE_JPEG ; 
 int MODE_RAW ; 
#define  SCALE_1280x1024 131 
#define  SCALE_160x120 130 
#define  SCALE_320x240 129 
#define  SCALE_640x480 128 
 int SCALE_MASK ; 
 int /*<<< orphan*/  configure_sensor_output (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  info (char*) ; 
 int /*<<< orphan*/  jpeg_define (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  jpeg_set_qual (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  reg_w1 (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  set_cmatrix (struct gspca_dev*) ; 
 int /*<<< orphan*/  set_exposure (struct gspca_dev*) ; 
 int /*<<< orphan*/  set_gain (struct gspca_dev*) ; 
 int /*<<< orphan*/  set_gamma (struct gspca_dev*) ; 
 int /*<<< orphan*/  set_hvflip (struct gspca_dev*) ; 
 int /*<<< orphan*/  set_redblue (struct gspca_dev*) ; 

__attribute__((used)) static int sd_start(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int mode = gspca_dev->cam.cam_mode[(int) gspca_dev->curr_mode].priv;
	int width = gspca_dev->width;
	int height = gspca_dev->height;
	u8 fmt, scale = 0;

	jpeg_define(sd->jpeg_hdr, height, width,
			0x21);
	jpeg_set_qual(sd->jpeg_hdr, sd->quality);

	if (mode & MODE_RAW)
		fmt = 0x2d;
	else if (mode & MODE_JPEG)
		fmt = 0x2c;
	else
		fmt = 0x2f;	/* YUV 420 */

	switch (mode & SCALE_MASK) {
	case SCALE_1280x1024:
		scale = 0xc0;
		info("Set 1280x1024");
		break;
	case SCALE_640x480:
		scale = 0x80;
		info("Set 640x480");
		break;
	case SCALE_320x240:
		scale = 0x90;
		info("Set 320x240");
		break;
	case SCALE_160x120:
		scale = 0xa0;
		info("Set 160x120");
		break;
	}

	configure_sensor_output(gspca_dev, mode);
	reg_w(gspca_dev, 0x1100, &sd->jpeg_hdr[JPEG_QT0_OFFSET], 64);
	reg_w(gspca_dev, 0x1140, &sd->jpeg_hdr[JPEG_QT1_OFFSET], 64);
	reg_w(gspca_dev, 0x10fb, CLR_WIN(width, height), 5);
	reg_w(gspca_dev, 0x1180, HW_WIN(mode, sd->hstart, sd->vstart), 6);
	reg_w1(gspca_dev, 0x1189, scale);
	reg_w1(gspca_dev, 0x10e0, fmt);

	set_cmatrix(gspca_dev);
	set_gamma(gspca_dev);
	set_redblue(gspca_dev);
	set_gain(gspca_dev);
	set_exposure(gspca_dev);
	set_hvflip(gspca_dev);

	reg_w1(gspca_dev, 0x1007, 0x20);

	reg_r(gspca_dev, 0x1061, 1);
	reg_w1(gspca_dev, 0x1061, gspca_dev->usb_buf[0] | 0x02);
	return 0;
}