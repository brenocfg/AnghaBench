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
struct sd {struct hdcs* sensor_priv; } ;
struct hdcs {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDCS_REG_CONTROL (struct sd*) ; 
 int /*<<< orphan*/  HDCS_STATE_IDLE ; 
 int stv06xx_write_sensor (struct sd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hdcs_reset(struct sd *sd)
{
	struct hdcs *hdcs = sd->sensor_priv;
	int err;

	err = stv06xx_write_sensor(sd, HDCS_REG_CONTROL(sd), 1);
	if (err < 0)
		return err;

	err = stv06xx_write_sensor(sd, HDCS_REG_CONTROL(sd), 0);
	if (err < 0)
		hdcs->state = HDCS_STATE_IDLE;

	return err;
}