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
struct w9968cf_device {int dummy; } ;
struct ovcamchip_control {int id; int value; } ;

/* Variables and functions */
 int /*<<< orphan*/  OVCAMCHIP_CMD_G_CTRL ; 
 int w9968cf_sensor_cmd (struct w9968cf_device*,int /*<<< orphan*/ ,struct ovcamchip_control*) ; 

__attribute__((used)) static int
w9968cf_sensor_get_control(struct w9968cf_device* cam, int cid, int* val)
{
	struct ovcamchip_control ctl;
	int err;

	ctl.id = cid;

	err = w9968cf_sensor_cmd(cam, OVCAMCHIP_CMD_G_CTRL, &ctl);
	if (!err)
		*val = ctl.value;

	return err;
}