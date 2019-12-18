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
struct backside_pid_state {int /*<<< orphan*/ * monitor; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_backside_fan_pwm ; 
 int /*<<< orphan*/  dev_attr_backside_temperature ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* of_dev ; 

__attribute__((used)) static void dispose_backside_state(struct backside_pid_state *state)
{
	if (state->monitor == NULL)
		return;

	device_remove_file(&of_dev->dev, &dev_attr_backside_temperature);
	device_remove_file(&of_dev->dev, &dev_attr_backside_fan_pwm);

	state->monitor = NULL;
}