#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int dummy; } ;
struct usb_host_interface {TYPE_2__* endpoint; } ;
struct TYPE_6__ {int width; int height; int /*<<< orphan*/  usb_err; int /*<<< orphan*/  alt; int /*<<< orphan*/  iface; int /*<<< orphan*/  dev; } ;
struct sd {int sensor; int clockdiv; TYPE_3__ gspca_dev; scalar_t__ frame_rate; } ;
struct TYPE_4__ {int /*<<< orphan*/  wMaxPacketSize; } ;
struct TYPE_5__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int OV511_RESET_OMNICE ; 
 int /*<<< orphan*/  R511_CAM_LNCNT ; 
 int /*<<< orphan*/  R511_CAM_LNDIV ; 
 int /*<<< orphan*/  R511_CAM_OPTS ; 
 int /*<<< orphan*/  R511_CAM_PXCNT ; 
 int /*<<< orphan*/  R511_CAM_PXDIV ; 
 int /*<<< orphan*/  R511_CAM_UV_EN ; 
 int /*<<< orphan*/  R511_COMP_EN ; 
 int /*<<< orphan*/  R511_COMP_LUT_EN ; 
 int /*<<< orphan*/  R511_SNAP_LNCNT ; 
 int /*<<< orphan*/  R511_SNAP_LNDIV ; 
 int /*<<< orphan*/  R511_SNAP_OPTS ; 
 int /*<<< orphan*/  R511_SNAP_PXCNT ; 
 int /*<<< orphan*/  R511_SNAP_PXDIV ; 
 int /*<<< orphan*/  R511_SNAP_UV_EN ; 
 int /*<<< orphan*/  R51x_FIFO_PSIZE ; 
 int /*<<< orphan*/  R51x_SYS_RESET ; 
#define  SEN_OV6620 137 
#define  SEN_OV6630 136 
#define  SEN_OV7610 135 
#define  SEN_OV7620 134 
#define  SEN_OV7620AE 133 
#define  SEN_OV7640 132 
#define  SEN_OV7648 131 
#define  SEN_OV7670 130 
#define  SEN_OV76BE 129 
#define  SEN_OV8610 128 
 int /*<<< orphan*/  err (char*) ; 
 scalar_t__ frame_rate ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_w (struct sd*,int /*<<< orphan*/ ,int) ; 
 struct usb_host_interface* usb_altnum_to_altsetting (struct usb_interface*,int /*<<< orphan*/ ) ; 
 struct usb_interface* usb_ifnum_to_if (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ov511_mode_init_regs(struct sd *sd)
{
	int hsegs, vsegs, packet_size, fps, needed;
	int interlaced = 0;
	struct usb_host_interface *alt;
	struct usb_interface *intf;

	intf = usb_ifnum_to_if(sd->gspca_dev.dev, sd->gspca_dev.iface);
	alt = usb_altnum_to_altsetting(intf, sd->gspca_dev.alt);
	if (!alt) {
		err("Couldn't get altsetting");
		sd->gspca_dev.usb_err = -EIO;
		return;
	}

	packet_size = le16_to_cpu(alt->endpoint[0].desc.wMaxPacketSize);
	reg_w(sd, R51x_FIFO_PSIZE, packet_size >> 5);

	reg_w(sd, R511_CAM_UV_EN, 0x01);
	reg_w(sd, R511_SNAP_UV_EN, 0x01);
	reg_w(sd, R511_SNAP_OPTS, 0x03);

	/* Here I'm assuming that snapshot size == image size.
	 * I hope that's always true. --claudio
	 */
	hsegs = (sd->gspca_dev.width >> 3) - 1;
	vsegs = (sd->gspca_dev.height >> 3) - 1;

	reg_w(sd, R511_CAM_PXCNT, hsegs);
	reg_w(sd, R511_CAM_LNCNT, vsegs);
	reg_w(sd, R511_CAM_PXDIV, 0x00);
	reg_w(sd, R511_CAM_LNDIV, 0x00);

	/* YUV420, low pass filter on */
	reg_w(sd, R511_CAM_OPTS, 0x03);

	/* Snapshot additions */
	reg_w(sd, R511_SNAP_PXCNT, hsegs);
	reg_w(sd, R511_SNAP_LNCNT, vsegs);
	reg_w(sd, R511_SNAP_PXDIV, 0x00);
	reg_w(sd, R511_SNAP_LNDIV, 0x00);

	/******** Set the framerate ********/
	if (frame_rate > 0)
		sd->frame_rate = frame_rate;

	switch (sd->sensor) {
	case SEN_OV6620:
		/* No framerate control, doesn't like higher rates yet */
		sd->clockdiv = 3;
		break;

	/* Note once the FIXME's in mode_init_ov_sensor_regs() are fixed
	   for more sensors we need to do this for them too */
	case SEN_OV7620:
	case SEN_OV7620AE:
	case SEN_OV7640:
	case SEN_OV7648:
	case SEN_OV76BE:
		if (sd->gspca_dev.width == 320)
			interlaced = 1;
		/* Fall through */
	case SEN_OV6630:
	case SEN_OV7610:
	case SEN_OV7670:
		switch (sd->frame_rate) {
		case 30:
		case 25:
			/* Not enough bandwidth to do 640x480 @ 30 fps */
			if (sd->gspca_dev.width != 640) {
				sd->clockdiv = 0;
				break;
			}
			/* Fall through for 640x480 case */
		default:
/*		case 20: */
/*		case 15: */
			sd->clockdiv = 1;
			break;
		case 10:
			sd->clockdiv = 2;
			break;
		case 5:
			sd->clockdiv = 5;
			break;
		}
		if (interlaced) {
			sd->clockdiv = (sd->clockdiv + 1) * 2 - 1;
			/* Higher then 10 does not work */
			if (sd->clockdiv > 10)
				sd->clockdiv = 10;
		}
		break;

	case SEN_OV8610:
		/* No framerate control ?? */
		sd->clockdiv = 0;
		break;
	}

	/* Check if we have enough bandwidth to disable compression */
	fps = (interlaced ? 60 : 30) / (sd->clockdiv + 1) + 1;
	needed = fps * sd->gspca_dev.width * sd->gspca_dev.height * 3 / 2;
	/* 1400 is a conservative estimate of the max nr of isoc packets/sec */
	if (needed > 1400 * packet_size) {
		/* Enable Y and UV quantization and compression */
		reg_w(sd, R511_COMP_EN, 0x07);
		reg_w(sd, R511_COMP_LUT_EN, 0x03);
	} else {
		reg_w(sd, R511_COMP_EN, 0x06);
		reg_w(sd, R511_COMP_LUT_EN, 0x00);
	}

	reg_w(sd, R51x_SYS_RESET, OV511_RESET_OMNICE);
	reg_w(sd, R51x_SYS_RESET, 0);
}