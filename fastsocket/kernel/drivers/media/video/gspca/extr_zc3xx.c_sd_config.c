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
struct usb_device_id {int idProduct; int /*<<< orphan*/  driver_info; } ;
struct sd {int /*<<< orphan*/  quality; int /*<<< orphan*/  ctrls; int /*<<< orphan*/  sensor; int /*<<< orphan*/  bridge; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctrls; } ;
struct gspca_dev {TYPE_1__ cam; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRIDGE_ZC301 ; 
 int /*<<< orphan*/  BRIDGE_ZC303 ; 
 int /*<<< orphan*/  QUALITY_DEF ; 

__attribute__((used)) static int sd_config(struct gspca_dev *gspca_dev,
			const struct usb_device_id *id)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (id->idProduct == 0x301b)
		sd->bridge = BRIDGE_ZC301;
	else
		sd->bridge = BRIDGE_ZC303;

	/* define some sensors from the vendor/product */
	sd->sensor = id->driver_info;

	gspca_dev->cam.ctrls = sd->ctrls;
	sd->quality = QUALITY_DEF;

	return 0;
}