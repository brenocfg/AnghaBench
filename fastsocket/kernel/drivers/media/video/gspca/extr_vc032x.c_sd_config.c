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
struct usb_device_id {int driver_info; int idVendor; int idProduct; } ;
struct sd {int bridge; int flags; int /*<<< orphan*/  backlight; int /*<<< orphan*/  autogain; int /*<<< orphan*/  exposure; int /*<<< orphan*/  gain; int /*<<< orphan*/  sharpness; int /*<<< orphan*/  lightfreq; int /*<<< orphan*/  vflip; int /*<<< orphan*/  hflip; int /*<<< orphan*/  colors; int /*<<< orphan*/  contrast; int /*<<< orphan*/  brightness; int /*<<< orphan*/  sensor; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTOGAIN_DEF ; 
 int /*<<< orphan*/  BACKLIGHT_DEF ; 
 int /*<<< orphan*/  BRIGHTNESS_DEF ; 
 int /*<<< orphan*/  COLOR_DEF ; 
 int /*<<< orphan*/  CONTRAST_DEF ; 
 int /*<<< orphan*/  EXPOSURE_DEF ; 
 int /*<<< orphan*/  FREQ_DEF ; 
 int /*<<< orphan*/  GAIN_DEF ; 
 int /*<<< orphan*/  HFLIP_DEF ; 
 int /*<<< orphan*/  SENSOR_POxxxx ; 
 int /*<<< orphan*/  SHARPNESS_DEF ; 
 int /*<<< orphan*/  VFLIP_DEF ; 

__attribute__((used)) static int sd_config(struct gspca_dev *gspca_dev,
			const struct usb_device_id *id)
{
	struct sd *sd = (struct sd *) gspca_dev;

	sd->bridge = id->driver_info >> 8;
	sd->flags = id->driver_info & 0xff;

	if (id->idVendor == 0x046d &&
	    (id->idProduct == 0x0892 || id->idProduct == 0x0896))
		sd->sensor = SENSOR_POxxxx;	/* no probe */

	sd->brightness = BRIGHTNESS_DEF;
	sd->contrast = CONTRAST_DEF;
	sd->colors = COLOR_DEF;
	sd->hflip = HFLIP_DEF;
	sd->vflip = VFLIP_DEF;
	sd->lightfreq = FREQ_DEF;
	sd->sharpness = SHARPNESS_DEF;
	sd->gain = GAIN_DEF;
	sd->exposure = EXPOSURE_DEF;
	sd->autogain = AUTOGAIN_DEF;
	sd->backlight = BACKLIGHT_DEF;

	return 0;
}