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
struct sd {int sensor; int i2c_addr; int flags; int exposure_step; int quality; int /*<<< orphan*/  auto_exposure; int /*<<< orphan*/  gain; int /*<<< orphan*/  exposure; int /*<<< orphan*/  vflip; int /*<<< orphan*/  hflip; int /*<<< orphan*/  blue; int /*<<< orphan*/  red; int /*<<< orphan*/  gamma; int /*<<< orphan*/  hue; int /*<<< orphan*/  saturation; int /*<<< orphan*/  contrast; int /*<<< orphan*/  brightness; scalar_t__ older_step; scalar_t__ old_step; } ;
struct cam {void* nmodes; void* cam_mode; } ;
struct gspca_dev {struct cam cam; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  AUTO_EXPOSURE_DEFAULT ; 
 int /*<<< orphan*/  BLUE_DEFAULT ; 
 int /*<<< orphan*/  BRIGHTNESS_DEFAULT ; 
 int /*<<< orphan*/  CONTRAST_DEFAULT ; 
 int /*<<< orphan*/  EXPOSURE_DEFAULT ; 
 int /*<<< orphan*/  GAIN_DEFAULT ; 
 int /*<<< orphan*/  GAMMA_DEFAULT ; 
 int /*<<< orphan*/  HFLIP_DEFAULT ; 
 int /*<<< orphan*/  HUE_DEFAULT ; 
 int /*<<< orphan*/  RED_DEFAULT ; 
 int /*<<< orphan*/  SATURATION_DEFAULT ; 
#define  SENSOR_MT9M001 132 
#define  SENSOR_MT9M111 131 
#define  SENSOR_MT9M112 130 
#define  SENSOR_OV9650 129 
#define  SENSOR_SOI968 128 
 int /*<<< orphan*/  VFLIP_DEFAULT ; 
 void* mono_mode ; 
 void* sxga_mode ; 
 void* vga_mode ; 

__attribute__((used)) static int sd_config(struct gspca_dev *gspca_dev,
			const struct usb_device_id *id)
{
	struct sd *sd = (struct sd *) gspca_dev;
	struct cam *cam;

	cam = &gspca_dev->cam;

	sd->sensor = (id->driver_info >> 8) & 0xff;
	sd->i2c_addr = id->driver_info & 0xff;
	sd->flags = (id->driver_info >> 16) & 0xff;

	switch (sd->sensor) {
	case SENSOR_MT9M112:
	case SENSOR_MT9M111:
	case SENSOR_OV9650:
	case SENSOR_SOI968:
		cam->cam_mode = sxga_mode;
		cam->nmodes = ARRAY_SIZE(sxga_mode);
		break;
	case SENSOR_MT9M001:
		cam->cam_mode = mono_mode;
		cam->nmodes = ARRAY_SIZE(mono_mode);
		break;
	default:
		cam->cam_mode = vga_mode;
		cam->nmodes = ARRAY_SIZE(vga_mode);
		break;
	}

	sd->old_step = 0;
	sd->older_step = 0;
	sd->exposure_step = 16;

	sd->brightness = BRIGHTNESS_DEFAULT;
	sd->contrast = CONTRAST_DEFAULT;
	sd->saturation = SATURATION_DEFAULT;
	sd->hue = HUE_DEFAULT;
	sd->gamma = GAMMA_DEFAULT;
	sd->red = RED_DEFAULT;
	sd->blue = BLUE_DEFAULT;

	sd->hflip = HFLIP_DEFAULT;
	sd->vflip = VFLIP_DEFAULT;
	sd->exposure = EXPOSURE_DEFAULT;
	sd->gain = GAIN_DEFAULT;
	sd->auto_exposure = AUTO_EXPOSURE_DEFAULT;

	sd->quality = 95;

	return 0;
}