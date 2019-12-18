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
 TYPE_2__* s5k3e2fx_ctrl ; 
 int /*<<< orphan*/  s5k3e2fx_power_down () ; 
 int /*<<< orphan*/  s5k3e2fx_sem ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int s5k3e2fx_sensor_release(void)
{
	int rc = -EBADF;

	down(&s5k3e2fx_sem);

	s5k3e2fx_power_down();

	gpio_direction_output(s5k3e2fx_ctrl->sensordata->sensor_reset,
		0);
	gpio_free(s5k3e2fx_ctrl->sensordata->sensor_reset);

	kfree(s5k3e2fx_ctrl);
	s5k3e2fx_ctrl = NULL;

	CDBG("s5k3e2fx_release completed\n");

	up(&s5k3e2fx_sem);
	return rc;
}