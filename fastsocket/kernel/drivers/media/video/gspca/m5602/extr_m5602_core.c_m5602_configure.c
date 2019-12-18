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
struct sd {int /*<<< orphan*/ * desc; } ;
struct cam {scalar_t__ nmodes; int /*<<< orphan*/ * cam_mode; } ;
struct gspca_dev {struct cam cam; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_ERR ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ dump_bridge ; 
 int /*<<< orphan*/  m5602_dump_bridge (struct sd*) ; 
 int m5602_probe_sensor (struct sd*) ; 
 int /*<<< orphan*/  sd_desc ; 

__attribute__((used)) static int m5602_configure(struct gspca_dev *gspca_dev,
			   const struct usb_device_id *id)
{
	struct sd *sd = (struct sd *) gspca_dev;
	struct cam *cam;
	int err;

	cam = &gspca_dev->cam;
	sd->desc = &sd_desc;

	if (dump_bridge)
		m5602_dump_bridge(sd);

	/* Probe sensor */
	err = m5602_probe_sensor(sd);
	if (err)
		goto fail;

	return 0;

fail:
	PDEBUG(D_ERR, "ALi m5602 webcam failed");
	cam->cam_mode = NULL;
	cam->nmodes = 0;

	return err;
}