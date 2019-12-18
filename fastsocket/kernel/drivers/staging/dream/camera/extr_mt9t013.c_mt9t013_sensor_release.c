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
struct TYPE_4__ {int /*<<< orphan*/  sensor_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDBG (char*) ; 
 int EBADF ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 TYPE_2__* mt9t013_ctrl ; 
 int /*<<< orphan*/  mt9t013_power_down () ; 
 int /*<<< orphan*/  mt9t013_poweroff_af () ; 
 int /*<<< orphan*/  mt9t013_sem ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

int mt9t013_sensor_release(void)
{
	int rc = -EBADF;

	down(&mt9t013_sem);

	mt9t013_poweroff_af();
	mt9t013_power_down();

	gpio_direction_output(mt9t013_ctrl->sensordata->sensor_reset,
			0);
	gpio_free(mt9t013_ctrl->sensordata->sensor_reset);

	kfree(mt9t013_ctrl);

	up(&mt9t013_sem);
	CDBG("mt9t013_release completed!\n");
	return rc;
}