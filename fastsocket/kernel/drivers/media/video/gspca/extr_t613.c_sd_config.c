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
struct usb_device_id {int dummy; } ;
struct sd {int red_gain; int blue_gain; int green_gain; int /*<<< orphan*/  effect; int /*<<< orphan*/  sharpness; int /*<<< orphan*/  awb; int /*<<< orphan*/  freq; int /*<<< orphan*/  mirror; int /*<<< orphan*/  autogain; int /*<<< orphan*/  gamma; int /*<<< orphan*/  colors; int /*<<< orphan*/  contrast; int /*<<< orphan*/  brightness; } ;
struct cam {int /*<<< orphan*/  nmodes; int /*<<< orphan*/  cam_mode; } ;
struct gspca_dev {struct cam cam; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AUTOGAIN_DEF ; 
 int /*<<< orphan*/  AWB_DEF ; 
 int BLUE_GAIN_DEF ; 
 int /*<<< orphan*/  BRIGHTNESS_DEF ; 
 int /*<<< orphan*/  COLORS_DEF ; 
 int /*<<< orphan*/  CONTRAST_DEF ; 
 int /*<<< orphan*/  EFFECTS_DEF ; 
 int /*<<< orphan*/  FREQ_DEF ; 
 int GAIN_DEF ; 
 int /*<<< orphan*/  GAMMA_DEF ; 
 int /*<<< orphan*/  MIRROR_DEF ; 
 int RED_GAIN_DEF ; 
 int /*<<< orphan*/  SHARPNESS_DEF ; 
 int /*<<< orphan*/  vga_mode_t16 ; 

__attribute__((used)) static int sd_config(struct gspca_dev *gspca_dev,
		     const struct usb_device_id *id)
{
	struct sd *sd = (struct sd *) gspca_dev;
	struct cam *cam;

	cam = &gspca_dev->cam;

	cam->cam_mode = vga_mode_t16;
	cam->nmodes = ARRAY_SIZE(vga_mode_t16);

	sd->brightness = BRIGHTNESS_DEF;
	sd->contrast = CONTRAST_DEF;
	sd->colors = COLORS_DEF;
	sd->gamma = GAMMA_DEF;
	sd->autogain = AUTOGAIN_DEF;
	sd->mirror = MIRROR_DEF;
	sd->freq = FREQ_DEF;
	sd->awb = AWB_DEF;
	sd->sharpness = SHARPNESS_DEF;
	sd->effect = EFFECTS_DEF;
	sd->red_gain = RED_GAIN_DEF;
	sd->blue_gain = BLUE_GAIN_DEF;
	sd->green_gain = GAIN_DEF * 3 - RED_GAIN_DEF - BLUE_GAIN_DEF;

	return 0;
}