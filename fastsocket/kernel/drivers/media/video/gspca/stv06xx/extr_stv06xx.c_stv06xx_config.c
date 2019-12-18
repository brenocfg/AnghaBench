#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct usb_device_id {int /*<<< orphan*/  driver_info; } ;
struct sd {TYPE_1__* sensor; int /*<<< orphan*/  desc; int /*<<< orphan*/  bridge; } ;
struct cam {int dummy; } ;
struct gspca_dev {int /*<<< orphan*/ * sd_desc; struct cam cam; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* probe ) (struct sd*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  D_PROBE ; 
 int ENODEV ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ dump_bridge ; 
 int /*<<< orphan*/  sd_desc ; 
 int /*<<< orphan*/  stub1 (struct sd*) ; 
 int /*<<< orphan*/  stub2 (struct sd*) ; 
 int /*<<< orphan*/  stub3 (struct sd*) ; 
 int /*<<< orphan*/  stub4 (struct sd*) ; 
 int /*<<< orphan*/  stub5 (struct sd*) ; 
 int /*<<< orphan*/  stv06xx_dump_bridge (struct sd*) ; 
 TYPE_1__ stv06xx_sensor_hdcs1020 ; 
 TYPE_1__ stv06xx_sensor_hdcs1x00 ; 
 TYPE_1__ stv06xx_sensor_pb0100 ; 
 TYPE_1__ stv06xx_sensor_st6422 ; 
 TYPE_1__ stv06xx_sensor_vv6410 ; 

__attribute__((used)) static int stv06xx_config(struct gspca_dev *gspca_dev,
			  const struct usb_device_id *id)
{
	struct sd *sd = (struct sd *) gspca_dev;
	struct cam *cam;

	PDEBUG(D_PROBE, "Configuring camera");

	cam = &gspca_dev->cam;
	sd->desc = sd_desc;
	sd->bridge = id->driver_info;
	gspca_dev->sd_desc = &sd->desc;

	if (dump_bridge)
		stv06xx_dump_bridge(sd);

	sd->sensor = &stv06xx_sensor_st6422;
	if (!sd->sensor->probe(sd))
		return 0;

	sd->sensor = &stv06xx_sensor_vv6410;
	if (!sd->sensor->probe(sd))
		return 0;

	sd->sensor = &stv06xx_sensor_hdcs1x00;
	if (!sd->sensor->probe(sd))
		return 0;

	sd->sensor = &stv06xx_sensor_hdcs1020;
	if (!sd->sensor->probe(sd))
		return 0;

	sd->sensor = &stv06xx_sensor_pb0100;
	if (!sd->sensor->probe(sd))
		return 0;

	sd->sensor = NULL;
	return -ENODEV;
}