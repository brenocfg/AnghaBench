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
struct sd {TYPE_1__* sensor; } ;
struct gspca_dev {int dummy; } ;
struct TYPE_2__ {int (* init ) (struct sd*) ;int /*<<< orphan*/  (* dump ) (struct sd*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  D_PROBE ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ dump_sensor ; 
 int /*<<< orphan*/  msleep (int) ; 
 int stub1 (struct sd*) ; 
 int /*<<< orphan*/  stub2 (struct sd*) ; 

__attribute__((used)) static int stv06xx_init(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int err;

	PDEBUG(D_PROBE, "Initializing camera");

	/* Let the usb init settle for a bit
	   before performing the initialization */
	msleep(250);

	err = sd->sensor->init(sd);

	if (dump_sensor && sd->sensor->dump)
		sd->sensor->dump(sd);

	return (err < 0) ? err : 0;
}