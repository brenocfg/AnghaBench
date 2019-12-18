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
struct TYPE_4__ {TYPE_1__* sensordata; } ;
struct TYPE_3__ {int /*<<< orphan*/  vcm_pwd; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 TYPE_2__* mt9t013_ctrl ; 

__attribute__((used)) static void mt9t013_poweroff_af(void)
{
	gpio_direction_output(mt9t013_ctrl->sensordata->vcm_pwd, 1);
	gpio_free(mt9t013_ctrl->sensordata->vcm_pwd);
}