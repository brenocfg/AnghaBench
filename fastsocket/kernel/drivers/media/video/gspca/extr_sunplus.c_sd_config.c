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
struct usb_device_id {int driver_info; } ;
struct sd {int bridge; int subtype; int /*<<< orphan*/  quality; int /*<<< orphan*/  autogain; int /*<<< orphan*/  colors; int /*<<< orphan*/  contrast; int /*<<< orphan*/  brightness; } ;
struct cam {void* nmodes; void* cam_mode; } ;
struct gspca_dev {int* usb_buf; struct cam cam; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  AUTOGAIN_DEF ; 
 int AiptekMiniPenCam13 ; 
 int BRIDGE_SPCA504B ; 
#define  BRIDGE_SPCA504C 129 
#define  BRIDGE_SPCA533 128 
 int /*<<< orphan*/  BRIGHTNESS_DEF ; 
 int /*<<< orphan*/  COLOR_DEF ; 
 int /*<<< orphan*/  CONTRAST_DEF ; 
 int ENODEV ; 
 int MegaImageVI ; 
 int /*<<< orphan*/  QUALITY_DEF ; 
 void* custom_mode ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int,int /*<<< orphan*/ ,int) ; 
 void* vga_mode ; 
 void* vga_mode2 ; 

__attribute__((used)) static int sd_config(struct gspca_dev *gspca_dev,
			const struct usb_device_id *id)
{
	struct sd *sd = (struct sd *) gspca_dev;
	struct cam *cam;

	cam = &gspca_dev->cam;

	sd->bridge = id->driver_info >> 8;
	sd->subtype = id->driver_info;

	if (sd->subtype == AiptekMiniPenCam13) {

		/* try to get the firmware as some cam answer 2.0.1.2.2
		 * and should be a spca504b then overwrite that setting */
		reg_r(gspca_dev, 0x20, 0, 1);
		switch (gspca_dev->usb_buf[0]) {
		case 1:
			break;		/* (right bridge/subtype) */
		case 2:
			sd->bridge = BRIDGE_SPCA504B;
			sd->subtype = 0;
			break;
		default:
			return -ENODEV;
		}
	}

	switch (sd->bridge) {
	default:
/*	case BRIDGE_SPCA504B: */
/*	case BRIDGE_SPCA504: */
/*	case BRIDGE_SPCA536: */
		cam->cam_mode = vga_mode;
		cam->nmodes = ARRAY_SIZE(vga_mode);
		break;
	case BRIDGE_SPCA533:
		cam->cam_mode = custom_mode;
		if (sd->subtype == MegaImageVI)		/* 320x240 only */
			cam->nmodes = ARRAY_SIZE(custom_mode) - 1;
		else
			cam->nmodes = ARRAY_SIZE(custom_mode);
		break;
	case BRIDGE_SPCA504C:
		cam->cam_mode = vga_mode2;
		cam->nmodes = ARRAY_SIZE(vga_mode2);
		break;
	}
	sd->brightness = BRIGHTNESS_DEF;
	sd->contrast = CONTRAST_DEF;
	sd->colors = COLOR_DEF;
	sd->autogain = AUTOGAIN_DEF;
	sd->quality = QUALITY_DEF;
	return 0;
}