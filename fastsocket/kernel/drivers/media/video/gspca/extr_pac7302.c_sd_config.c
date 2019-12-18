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
struct usb_device_id {int /*<<< orphan*/  driver_info; } ;
struct sd {int /*<<< orphan*/  flags; int /*<<< orphan*/  vflip; int /*<<< orphan*/  hflip; int /*<<< orphan*/  autogain; int /*<<< orphan*/  exposure; int /*<<< orphan*/  gain; int /*<<< orphan*/  blue_balance; int /*<<< orphan*/  red_balance; int /*<<< orphan*/  white_balance; int /*<<< orphan*/  colors; int /*<<< orphan*/  contrast; int /*<<< orphan*/  brightness; } ;
struct cam {int /*<<< orphan*/  nmodes; int /*<<< orphan*/  cam_mode; } ;
struct gspca_dev {struct cam cam; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AUTOGAIN_DEF ; 
 int /*<<< orphan*/  BLUEBALANCE_DEF ; 
 int /*<<< orphan*/  BRIGHTNESS_DEF ; 
 int /*<<< orphan*/  COLOR_DEF ; 
 int /*<<< orphan*/  CONTRAST_DEF ; 
 int /*<<< orphan*/  D_CONF ; 
 int /*<<< orphan*/  EXPOSURE_DEF ; 
 int /*<<< orphan*/  GAIN_DEF ; 
 int /*<<< orphan*/  HFLIP_DEF ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  REDBALANCE_DEF ; 
 int /*<<< orphan*/  VFLIP_DEF ; 
 int /*<<< orphan*/  WHITEBALANCE_DEF ; 
 int /*<<< orphan*/  vga_mode ; 

__attribute__((used)) static int sd_config(struct gspca_dev *gspca_dev,
			const struct usb_device_id *id)
{
	struct sd *sd = (struct sd *) gspca_dev;
	struct cam *cam;

	cam = &gspca_dev->cam;

	PDEBUG(D_CONF, "Find Sensor PAC7302");
	cam->cam_mode = vga_mode;	/* only 640x480 */
	cam->nmodes = ARRAY_SIZE(vga_mode);

	sd->brightness = BRIGHTNESS_DEF;
	sd->contrast = CONTRAST_DEF;
	sd->colors = COLOR_DEF;
	sd->white_balance = WHITEBALANCE_DEF;
	sd->red_balance = REDBALANCE_DEF;
	sd->blue_balance = BLUEBALANCE_DEF;
	sd->gain = GAIN_DEF;
	sd->exposure = EXPOSURE_DEF;
	sd->autogain = AUTOGAIN_DEF;
	sd->hflip = HFLIP_DEF;
	sd->vflip = VFLIP_DEF;
	sd->flags = id->driver_info;
	return 0;
}