#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* sensordata; } ;
struct TYPE_4__ {int /*<<< orphan*/  vcm_pwd; int /*<<< orphan*/  sensor_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDBG (char*) ; 
 int EBADF ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 TYPE_2__* mt9p012_ctrl ; 
 int /*<<< orphan*/  mt9p012_power_down () ; 
 int /*<<< orphan*/  mt9p012_sem ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

int mt9p012_sensor_release(void)
{
	int rc = -EBADF;

	down(&mt9p012_sem);

	mt9p012_power_down();

	gpio_direction_output(mt9p012_ctrl->sensordata->sensor_reset,
		0);
	gpio_free(mt9p012_ctrl->sensordata->sensor_reset);

	gpio_direction_output(mt9p012_ctrl->sensordata->vcm_pwd, 0);
	gpio_free(mt9p012_ctrl->sensordata->vcm_pwd);

	kfree(mt9p012_ctrl);
	mt9p012_ctrl = NULL;

	CDBG("mt9p012_release completed\n");

	up(&mt9p012_sem);
	return rc;
}