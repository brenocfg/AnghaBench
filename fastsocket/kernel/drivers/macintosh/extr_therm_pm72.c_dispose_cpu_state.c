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
struct cpu_pid_state {scalar_t__ index; int /*<<< orphan*/ * monitor; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_cpu0_current ; 
 int /*<<< orphan*/  dev_attr_cpu0_exhaust_fan_rpm ; 
 int /*<<< orphan*/  dev_attr_cpu0_intake_fan_rpm ; 
 int /*<<< orphan*/  dev_attr_cpu0_temperature ; 
 int /*<<< orphan*/  dev_attr_cpu0_voltage ; 
 int /*<<< orphan*/  dev_attr_cpu1_current ; 
 int /*<<< orphan*/  dev_attr_cpu1_exhaust_fan_rpm ; 
 int /*<<< orphan*/  dev_attr_cpu1_intake_fan_rpm ; 
 int /*<<< orphan*/  dev_attr_cpu1_temperature ; 
 int /*<<< orphan*/  dev_attr_cpu1_voltage ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* of_dev ; 

__attribute__((used)) static void dispose_cpu_state(struct cpu_pid_state *state)
{
	if (state->monitor == NULL)
		return;

	if (state->index == 0) {
		device_remove_file(&of_dev->dev, &dev_attr_cpu0_temperature);
		device_remove_file(&of_dev->dev, &dev_attr_cpu0_voltage);
		device_remove_file(&of_dev->dev, &dev_attr_cpu0_current);
		device_remove_file(&of_dev->dev, &dev_attr_cpu0_exhaust_fan_rpm);
		device_remove_file(&of_dev->dev, &dev_attr_cpu0_intake_fan_rpm);
	} else {
		device_remove_file(&of_dev->dev, &dev_attr_cpu1_temperature);
		device_remove_file(&of_dev->dev, &dev_attr_cpu1_voltage);
		device_remove_file(&of_dev->dev, &dev_attr_cpu1_current);
		device_remove_file(&of_dev->dev, &dev_attr_cpu1_exhaust_fan_rpm);
		device_remove_file(&of_dev->dev, &dev_attr_cpu1_intake_fan_rpm);
	}

	state->monitor = NULL;
}