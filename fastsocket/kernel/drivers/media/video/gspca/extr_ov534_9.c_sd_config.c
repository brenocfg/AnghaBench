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
struct sd {int /*<<< orphan*/  freq; int /*<<< orphan*/  satur; int /*<<< orphan*/  sharpness; int /*<<< orphan*/  exposure; int /*<<< orphan*/  autogain; int /*<<< orphan*/  contrast; int /*<<< orphan*/  brightness; } ;
struct cam {int /*<<< orphan*/  nmodes; int /*<<< orphan*/  cam_mode; } ;
struct gspca_dev {int ctrl_inac; struct cam cam; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AUTOGAIN_DEF ; 
 int /*<<< orphan*/  BRIGHTNESS_DEF ; 
 int /*<<< orphan*/  CONTRAST_DEF ; 
 int /*<<< orphan*/  EXPO_DEF ; 
 int EXPO_IDX ; 
 int /*<<< orphan*/  FREQ_DEF ; 
 int /*<<< orphan*/  SATUR_DEF ; 
 int /*<<< orphan*/  SHARPNESS_DEF ; 
 int /*<<< orphan*/  ov965x_mode ; 

__attribute__((used)) static int sd_config(struct gspca_dev *gspca_dev,
		     const struct usb_device_id *id)
{
	struct sd *sd = (struct sd *) gspca_dev;
	struct cam *cam;

	cam = &gspca_dev->cam;

	cam->cam_mode = ov965x_mode;
	cam->nmodes = ARRAY_SIZE(ov965x_mode);

	sd->brightness = BRIGHTNESS_DEF;
	sd->contrast = CONTRAST_DEF;
#if AUTOGAIN_DEF != 0
	sd->autogain = AUTOGAIN_DEF;
	gspca_dev->ctrl_inac |= (1 << EXPO_IDX);
#endif
#if EXPO_DEF != 0
	sd->exposure = EXPO_DEF;
#endif
#if SHARPNESS_DEF != 0
	sd->sharpness = SHARPNESS_DEF;
#endif
	sd->satur = SATUR_DEF;
	sd->freq = FREQ_DEF;

	return 0;
}