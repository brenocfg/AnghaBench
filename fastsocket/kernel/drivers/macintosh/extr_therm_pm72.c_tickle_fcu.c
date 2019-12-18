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

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int) ; 
 int SLOTS_FAN_DEFAULT_PWM ; 
 int /*<<< orphan*/  SLOTS_FAN_PWM_INDEX ; 
 int SLOTS_PID_OUTPUT_MIN ; 
 int get_pwm_fan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rackmac ; 
 int /*<<< orphan*/  set_pwm_fan (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tickle_fcu(void)
{
	int pwm;

	pwm = get_pwm_fan(SLOTS_FAN_PWM_INDEX);

	DBG("FCU Tickle, slots fan is: %d\n", pwm);
	if (pwm < 0)
		pwm = 100;

	if (!rackmac) {
		pwm = SLOTS_FAN_DEFAULT_PWM;
	} else if (pwm < SLOTS_PID_OUTPUT_MIN)
		pwm = SLOTS_PID_OUTPUT_MIN;

	/* That is hopefully enough to make the FCU happy */
	set_pwm_fan(SLOTS_FAN_PWM_INDEX, pwm);
}