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
typedef  int u8 ;
struct st6422_settings {TYPE_1__* ctrls; } ;
struct sd {struct st6422_settings* sensor_priv; } ;
struct TYPE_2__ {int val; } ;

/* Variables and functions */
 size_t GAIN ; 
 int stv06xx_write_bridge (struct sd*,int,int) ; 

__attribute__((used)) static int setgain(struct sd *sd)
{
	struct st6422_settings *sensor_settings = sd->sensor_priv;
	u8 gain;
	int err;

	gain = sensor_settings->ctrls[GAIN].val;

	/* Set red, green, blue, gain */
	err = stv06xx_write_bridge(sd, 0x0509, gain);
	if (err < 0)
		return err;

	err = stv06xx_write_bridge(sd, 0x050a, gain);
	if (err < 0)
		return err;

	err = stv06xx_write_bridge(sd, 0x050b, gain);
	if (err < 0)
		return err;

	/* 2 mystery writes */
	err = stv06xx_write_bridge(sd, 0x050c, 0x2a);
	if (err < 0)
		return err;

	return stv06xx_write_bridge(sd, 0x050d, 0x01);
}