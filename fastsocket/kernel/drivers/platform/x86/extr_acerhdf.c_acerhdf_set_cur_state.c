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
struct thermal_cooling_device {int dummy; } ;

/* Variables and functions */
 int ACERHDF_FAN_AUTO ; 
 int ACERHDF_FAN_OFF ; 
 int EINVAL ; 
 int /*<<< orphan*/  acerhdf_change_fanstate (int) ; 
 int acerhdf_get_fanstate (int*) ; 
 int acerhdf_get_temp (int*) ; 
 int /*<<< orphan*/  acerhdf_revert_to_bios_mode () ; 
 int fanoff ; 
 int /*<<< orphan*/  kernelmode ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int acerhdf_set_cur_state(struct thermal_cooling_device *cdev,
				 unsigned long state)
{
	int cur_temp, cur_state, err = 0;

	if (!kernelmode)
		return 0;

	err = acerhdf_get_temp(&cur_temp);
	if (err) {
		pr_err("error reading temperature, hand off control to BIOS\n");
		goto err_out;
	}

	err = acerhdf_get_fanstate(&cur_state);
	if (err) {
		pr_err("error reading fan state, hand off control to BIOS\n");
		goto err_out;
	}

	if (state == 0) {
		/* turn fan off only if below fanoff temperature */
		if ((cur_state == ACERHDF_FAN_AUTO) &&
		    (cur_temp < fanoff))
			acerhdf_change_fanstate(ACERHDF_FAN_OFF);
	} else {
		if (cur_state == ACERHDF_FAN_OFF)
			acerhdf_change_fanstate(ACERHDF_FAN_AUTO);
	}
	return 0;

err_out:
	acerhdf_revert_to_bios_mode();
	return -EINVAL;
}