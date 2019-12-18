#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_device_id {int driver_info; } ;
struct sd {int sensor; int bridge; int /*<<< orphan*/  freq; scalar_t__ autogain; int /*<<< orphan*/  exposure; int /*<<< orphan*/  gain; int /*<<< orphan*/  brightness; } ;
struct cam {int npkt; void* nmodes; void* cam_mode; } ;
struct gspca_dev {int* usb_buf; int ctrl_dis; struct cam cam; } ;
struct TYPE_2__ {int ctrl_dis; int flags; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 scalar_t__ AUTOGAIN_DEF ; 
 int AUTOGAIN_IDX ; 
 int /*<<< orphan*/  BRIGHTNESS_DEF ; 
 int /*<<< orphan*/  COARSE_EXPOSURE_DEF ; 
 int COARSE_EXPOSURE_IDX ; 
 int ENODEV ; 
 int /*<<< orphan*/  EXPOSURE_DEF ; 
 int EXPOSURE_IDX ; 
 int /*<<< orphan*/  FREQ_DEF ; 
 int F_COARSE_EXPO ; 
 int F_SIF ; 
 int /*<<< orphan*/  GAIN_DEF ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int) ; 
 TYPE_1__* sensor_data ; 
 void* sif_mode ; 
 void* vga_mode ; 

__attribute__((used)) static int sd_config(struct gspca_dev *gspca_dev,
			const struct usb_device_id *id)
{
	struct sd *sd = (struct sd *) gspca_dev;
	struct cam *cam;

	reg_r(gspca_dev, 0x00);
	if (gspca_dev->usb_buf[0] != 0x10)
		return -ENODEV;

	/* copy the webcam info from the device id */
	sd->sensor = id->driver_info >> 8;
	sd->bridge = id->driver_info & 0xff;
	gspca_dev->ctrl_dis = sensor_data[sd->sensor].ctrl_dis;

	cam = &gspca_dev->cam;
	if (!(sensor_data[sd->sensor].flags & F_SIF)) {
		cam->cam_mode = vga_mode;
		cam->nmodes = ARRAY_SIZE(vga_mode);
	} else {
		cam->cam_mode = sif_mode;
		cam->nmodes = ARRAY_SIZE(sif_mode);
	}
	cam->npkt = 36;			/* 36 packets per ISOC message */

	sd->brightness = BRIGHTNESS_DEF;
	sd->gain = GAIN_DEF;
	if (sensor_data[sd->sensor].flags & F_COARSE_EXPO) {
		sd->exposure = COARSE_EXPOSURE_DEF;
		gspca_dev->ctrl_dis |= (1 << EXPOSURE_IDX);
	} else {
		sd->exposure = EXPOSURE_DEF;
		gspca_dev->ctrl_dis |= (1 << COARSE_EXPOSURE_IDX);
	}
	if (gspca_dev->ctrl_dis & (1 << AUTOGAIN_IDX))
		sd->autogain = 0; /* Disable do_autogain callback */
	else
		sd->autogain = AUTOGAIN_DEF;
	sd->freq = FREQ_DEF;

	return 0;
}