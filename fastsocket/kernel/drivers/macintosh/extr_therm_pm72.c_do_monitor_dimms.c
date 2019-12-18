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
struct dimm_pid_state {scalar_t__ ticks; int output; int last_temp; int cur_sample; int* sample_history; int* error_history; scalar_t__ first; int /*<<< orphan*/  monitor; } ;
typedef  int s64 ;
typedef  int s32 ;
struct TYPE_4__ {int /*<<< orphan*/  output_min; } ;
struct TYPE_3__ {int pwm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKSIDE_FAN_PWM_INDEX ; 
 int /*<<< orphan*/  DBG (char*,...) ; 
 scalar_t__ DIMM_PID_G_d ; 
 scalar_t__ DIMM_PID_G_p ; 
 scalar_t__ DIMM_PID_G_r ; 
 int DIMM_PID_HISTORY_SIZE ; 
 int DIMM_PID_INPUT_TARGET ; 
 int DIMM_PID_INTERVAL ; 
 int /*<<< orphan*/  DIMM_PID_OUTPUT_MAX ; 
 int /*<<< orphan*/  DIMM_PID_OUTPUT_MIN ; 
 int /*<<< orphan*/  FIX32TOPRINT (int) ; 
 int /*<<< orphan*/  LM87_INT_TEMP ; 
 TYPE_2__ backside_params ; 
 TYPE_1__ backside_state ; 
 int dimm_output_clamp ; 
 void* max (int,int /*<<< orphan*/ ) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int read_lm87_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pwm_fan (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void do_monitor_dimms(struct dimm_pid_state *state)
{
	s32 temp, integral, derivative, fan_min;
	s64 integ_p, deriv_p, prop_p, sum;
	int i;

	if (--state->ticks != 0)
		return;
	state->ticks = DIMM_PID_INTERVAL;

	DBG("DIMM:\n");

	DBG("  current value: %d\n", state->output);

	temp = read_lm87_reg(state->monitor, LM87_INT_TEMP);
	if (temp < 0)
		return;
	temp <<= 16;
	state->last_temp = temp;
	DBG("  temp: %d.%03d, target: %d.%03d\n", FIX32TOPRINT(temp),
	    FIX32TOPRINT(DIMM_PID_INPUT_TARGET));

	/* Store temperature and error in history array */
	state->cur_sample = (state->cur_sample + 1) % DIMM_PID_HISTORY_SIZE;
	state->sample_history[state->cur_sample] = temp;
	state->error_history[state->cur_sample] = temp - DIMM_PID_INPUT_TARGET;

	/* If first loop, fill the history table */
	if (state->first) {
		for (i = 0; i < (DIMM_PID_HISTORY_SIZE - 1); i++) {
			state->cur_sample = (state->cur_sample + 1) %
				DIMM_PID_HISTORY_SIZE;
			state->sample_history[state->cur_sample] = temp;
			state->error_history[state->cur_sample] =
				temp - DIMM_PID_INPUT_TARGET;
		}
		state->first = 0;
	}

	/* Calculate the integral term */
	sum = 0;
	integral = 0;
	for (i = 0; i < DIMM_PID_HISTORY_SIZE; i++)
		integral += state->error_history[i];
	integral *= DIMM_PID_INTERVAL;
	DBG("  integral: %08x\n", integral);
	integ_p = ((s64)DIMM_PID_G_r) * (s64)integral;
	DBG("   integ_p: %d\n", (int)(integ_p >> 36));
	sum += integ_p;

	/* Calculate the derivative term */
	derivative = state->error_history[state->cur_sample] -
		state->error_history[(state->cur_sample + DIMM_PID_HISTORY_SIZE - 1)
				    % DIMM_PID_HISTORY_SIZE];
	derivative /= DIMM_PID_INTERVAL;
	deriv_p = ((s64)DIMM_PID_G_d) * (s64)derivative;
	DBG("   deriv_p: %d\n", (int)(deriv_p >> 36));
	sum += deriv_p;

	/* Calculate the proportional term */
	prop_p = ((s64)DIMM_PID_G_p) * (s64)(state->error_history[state->cur_sample]);
	DBG("   prop_p: %d\n", (int)(prop_p >> 36));
	sum += prop_p;

	/* Scale sum */
	sum >>= 36;

	DBG("   sum: %d\n", (int)sum);
	state->output = (s32)sum;
	state->output = max(state->output, DIMM_PID_OUTPUT_MIN);
	state->output = min(state->output, DIMM_PID_OUTPUT_MAX);
	dimm_output_clamp = state->output;

	DBG("** DIMM clamp value: %d\n", (int)state->output);

	/* Backside PID is only every 5 seconds, force backside fan clamping now */
	fan_min = (dimm_output_clamp * 100) / 14000;
	fan_min = max(fan_min, backside_params.output_min);
	if (backside_state.pwm < fan_min) {
		backside_state.pwm = fan_min;
		DBG(" -> applying clamp to backside fan now: %d  !\n", fan_min);
		set_pwm_fan(BACKSIDE_FAN_PWM_INDEX, fan_min);
	}
}