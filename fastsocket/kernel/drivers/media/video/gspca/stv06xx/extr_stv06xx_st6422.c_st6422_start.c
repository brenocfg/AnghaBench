#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cam {TYPE_2__* cam_mode; } ;
struct TYPE_3__ {size_t curr_mode; struct cam cam; } ;
struct sd {TYPE_1__ gspca_dev; } ;
struct TYPE_4__ {scalar_t__ priv; } ;

/* Variables and functions */
 int setbrightness (struct sd*) ; 
 int setcontrast (struct sd*) ; 
 int setexposure (struct sd*) ; 
 int setgain (struct sd*) ; 
 int stv06xx_write_bridge (struct sd*,int,int) ; 

__attribute__((used)) static int st6422_start(struct sd *sd)
{
	int err;
	struct cam *cam = &sd->gspca_dev.cam;

	if (cam->cam_mode[sd->gspca_dev.curr_mode].priv)
		err = stv06xx_write_bridge(sd, 0x1505, 0x0f);
	else
		err = stv06xx_write_bridge(sd, 0x1505, 0x02);
	if (err < 0)
		return err;

	err = setbrightness(sd);
	if (err < 0)
		return err;

	err = setcontrast(sd);
	if (err < 0)
		return err;

	err = setexposure(sd);
	if (err < 0)
		return err;

	err = setgain(sd);
	if (err < 0)
		return err;

	/* commit settings */
	err = stv06xx_write_bridge(sd, 0x143f, 0x01);
	return (err < 0) ? err : 0;
}