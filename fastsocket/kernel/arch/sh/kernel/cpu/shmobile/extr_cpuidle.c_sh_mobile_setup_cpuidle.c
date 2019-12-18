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
struct cpuidle_state {char* name; char* desc; int exit_latency; int target_residency; int power_usage; void* enter; int /*<<< orphan*/  flags; } ;
struct cpuidle_device {int state_count; struct cpuidle_state* states; struct cpuidle_state* safe_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUIDLE_DESC_LEN ; 
 int CPUIDLE_DRIVER_STATE_START ; 
 int /*<<< orphan*/  CPUIDLE_FLAG_SHALLOW ; 
 int /*<<< orphan*/  CPUIDLE_FLAG_TIME_VALID ; 
 int /*<<< orphan*/  CPUIDLE_NAME_LEN ; 
 int CPUIDLE_STATE_MAX ; 
 struct cpuidle_device cpuidle_dev ; 
 int /*<<< orphan*/  cpuidle_driver ; 
 int /*<<< orphan*/  cpuidle_register_device (struct cpuidle_device*) ; 
 int /*<<< orphan*/  cpuidle_register_driver (int /*<<< orphan*/ *) ; 
 void* cpuidle_sleep_enter ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int /*<<< orphan*/ ) ; 

void sh_mobile_setup_cpuidle(void)
{
	struct cpuidle_device *dev = &cpuidle_dev;
	struct cpuidle_state *state;
	int i;

	cpuidle_register_driver(&cpuidle_driver);

	for (i = 0; i < CPUIDLE_STATE_MAX; i++) {
		dev->states[i].name[0] = '\0';
		dev->states[i].desc[0] = '\0';
	}

	i = CPUIDLE_DRIVER_STATE_START;

	state = &dev->states[i++];
	snprintf(state->name, CPUIDLE_NAME_LEN, "C0");
	strncpy(state->desc, "SuperH Sleep Mode", CPUIDLE_DESC_LEN);
	state->exit_latency = 1;
	state->target_residency = 1 * 2;
	state->power_usage = 3;
	state->flags = 0;
	state->flags |= CPUIDLE_FLAG_SHALLOW;
	state->flags |= CPUIDLE_FLAG_TIME_VALID;
	state->enter = cpuidle_sleep_enter;

	dev->safe_state = state;

	state = &dev->states[i++];
	snprintf(state->name, CPUIDLE_NAME_LEN, "C1");
	strncpy(state->desc, "SuperH Sleep Mode [SF]", CPUIDLE_DESC_LEN);
	state->exit_latency = 100;
	state->target_residency = 1 * 2;
	state->power_usage = 1;
	state->flags = 0;
	state->flags |= CPUIDLE_FLAG_TIME_VALID;
	state->enter = cpuidle_sleep_enter;

	state = &dev->states[i++];
	snprintf(state->name, CPUIDLE_NAME_LEN, "C2");
	strncpy(state->desc, "SuperH Mobile Standby Mode [SF]", CPUIDLE_DESC_LEN);
	state->exit_latency = 2300;
	state->target_residency = 1 * 2;
	state->power_usage = 1;
	state->flags = 0;
	state->flags |= CPUIDLE_FLAG_TIME_VALID;
	state->enter = cpuidle_sleep_enter;

	dev->state_count = i;

	cpuidle_register_device(dev);
}