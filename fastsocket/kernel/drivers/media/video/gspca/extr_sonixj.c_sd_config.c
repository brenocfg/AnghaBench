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
struct sd {int bridge; int sensor; int flags; int ag_cnt; int jpegqual; int /*<<< orphan*/  quality; int /*<<< orphan*/  ctrls; } ;
struct cam {int npkt; int /*<<< orphan*/  ctrls; void* nmodes; void* cam_mode; } ;
struct gspca_dev {struct cam cam; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  QUALITY_DEF ; 
 int SENSOR_ADCM1700 ; 
 void* cif_mode ; 
 void* vga_mode ; 

__attribute__((used)) static int sd_config(struct gspca_dev *gspca_dev,
			const struct usb_device_id *id)
{
	struct sd *sd = (struct sd *) gspca_dev;
	struct cam *cam;

	sd->bridge = id->driver_info >> 16;
	sd->sensor = id->driver_info >> 8;
	sd->flags = id->driver_info;

	cam = &gspca_dev->cam;
	if (sd->sensor == SENSOR_ADCM1700) {
		cam->cam_mode = cif_mode;
		cam->nmodes = ARRAY_SIZE(cif_mode);
	} else {
		cam->cam_mode = vga_mode;
		cam->nmodes = ARRAY_SIZE(vga_mode);
	}
	cam->npkt = 24;			/* 24 packets per ISOC message */
	cam->ctrls = sd->ctrls;

	sd->ag_cnt = -1;
	sd->quality = QUALITY_DEF;
	sd->jpegqual = 80;

	return 0;
}