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
struct sd {int frame_rate; int /*<<< orphan*/  freqfltr; int /*<<< orphan*/  vflip; int /*<<< orphan*/  hflip; int /*<<< orphan*/  sharpness; int /*<<< orphan*/  aec; int /*<<< orphan*/  awb; int /*<<< orphan*/  agc; int /*<<< orphan*/  exposure; int /*<<< orphan*/  gain; int /*<<< orphan*/  contrast; int /*<<< orphan*/  brightness; } ;
struct cam {int bulk; int bulk_size; int bulk_nurbs; int /*<<< orphan*/  mode_framerates; int /*<<< orphan*/  nmodes; int /*<<< orphan*/  cam_mode; } ;
struct gspca_dev {int ctrl_inac; struct cam cam; } ;

/* Variables and functions */
 int /*<<< orphan*/  AEC_DEF ; 
 int /*<<< orphan*/  AGC_DEF ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AWB_DEF ; 
 int AWB_IDX ; 
 int /*<<< orphan*/  BRIGHTNESS_DEF ; 
 int /*<<< orphan*/  CONTRAST_DEF ; 
 int /*<<< orphan*/  EXPO_DEF ; 
 int /*<<< orphan*/  FREQFLTR_DEF ; 
 int /*<<< orphan*/  GAIN_DEF ; 
 int /*<<< orphan*/  HFLIP_DEF ; 
 int /*<<< orphan*/  SHARPNESS_DEF ; 
 int /*<<< orphan*/  VFLIP_DEF ; 
 int /*<<< orphan*/  ov772x_framerates ; 
 int /*<<< orphan*/  ov772x_mode ; 

__attribute__((used)) static int sd_config(struct gspca_dev *gspca_dev,
		     const struct usb_device_id *id)
{
	struct sd *sd = (struct sd *) gspca_dev;
	struct cam *cam;

	cam = &gspca_dev->cam;

	cam->cam_mode = ov772x_mode;
	cam->nmodes = ARRAY_SIZE(ov772x_mode);
	cam->mode_framerates = ov772x_framerates;

	cam->bulk = 1;
	cam->bulk_size = 16384;
	cam->bulk_nurbs = 2;

	sd->frame_rate = 30;

	sd->brightness = BRIGHTNESS_DEF;
	sd->contrast = CONTRAST_DEF;
	sd->gain = GAIN_DEF;
	sd->exposure = EXPO_DEF;
#if AGC_DEF != 0
	sd->agc = AGC_DEF;
#else
	gspca_dev->ctrl_inac |= (1 << AWB_IDX);
#endif
	sd->awb = AWB_DEF;
	sd->aec = AEC_DEF;
	sd->sharpness = SHARPNESS_DEF;
	sd->hflip = HFLIP_DEF;
	sd->vflip = VFLIP_DEF;
	sd->freqfltr = FREQFLTR_DEF;

	return 0;
}