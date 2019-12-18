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
typedef  int u32 ;
struct TYPE_2__ {int tmax; int ttarget; scalar_t__ pid_gp; scalar_t__ pid_gd; scalar_t__ pid_gr; scalar_t__ padjmax; scalar_t__ pmaxh; } ;
struct cpu_pid_state {int cur_temp; int* temp_history; int cur_power; int count_power; int* power_history; int* error_history; int /*<<< orphan*/  rpm; TYPE_1__ mpu; scalar_t__ first; } ;
typedef  int s64 ;
typedef  int s32 ;

/* Variables and functions */
 int CPU_PID_INTERVAL ; 
 int CPU_TEMP_HISTORY_SIZE ; 
 int /*<<< orphan*/  DBG (char*,int,...) ; 
 int /*<<< orphan*/  FIX32TOPRINT (int) ; 

__attribute__((used)) static void do_cpu_pid(struct cpu_pid_state *state, s32 temp, s32 power)
{
	s32 power_target, integral, derivative, proportional, adj_in_target, sval;
	s64 integ_p, deriv_p, prop_p, sum; 
	int i;

	/* Calculate power target value (could be done once for all)
	 * and convert to a 16.16 fp number
	 */
	power_target = ((u32)(state->mpu.pmaxh - state->mpu.padjmax)) << 16;
	DBG("  power target: %d.%03d, error: %d.%03d\n",
	    FIX32TOPRINT(power_target), FIX32TOPRINT(power_target - power));

	/* Store temperature and power in history array */
	state->cur_temp = (state->cur_temp + 1) % CPU_TEMP_HISTORY_SIZE;
	state->temp_history[state->cur_temp] = temp;
	state->cur_power = (state->cur_power + 1) % state->count_power;
	state->power_history[state->cur_power] = power;
	state->error_history[state->cur_power] = power_target - power;
	
	/* If first loop, fill the history table */
	if (state->first) {
		for (i = 0; i < (state->count_power - 1); i++) {
			state->cur_power = (state->cur_power + 1) % state->count_power;
			state->power_history[state->cur_power] = power;
			state->error_history[state->cur_power] = power_target - power;
		}
		for (i = 0; i < (CPU_TEMP_HISTORY_SIZE - 1); i++) {
			state->cur_temp = (state->cur_temp + 1) % CPU_TEMP_HISTORY_SIZE;
			state->temp_history[state->cur_temp] = temp;			
		}
		state->first = 0;
	}

	/* Calculate the integral term normally based on the "power" values */
	sum = 0;
	integral = 0;
	for (i = 0; i < state->count_power; i++)
		integral += state->error_history[i];
	integral *= CPU_PID_INTERVAL;
	DBG("  integral: %08x\n", integral);

	/* Calculate the adjusted input (sense value).
	 *   G_r is 12.20
	 *   integ is 16.16
	 *   so the result is 28.36
	 *
	 * input target is mpu.ttarget, input max is mpu.tmax
	 */
	integ_p = ((s64)state->mpu.pid_gr) * (s64)integral;
	DBG("   integ_p: %d\n", (int)(integ_p >> 36));
	sval = (state->mpu.tmax << 16) - ((integ_p >> 20) & 0xffffffff);
	adj_in_target = (state->mpu.ttarget << 16);
	if (adj_in_target > sval)
		adj_in_target = sval;
	DBG("   adj_in_target: %d.%03d, ttarget: %d\n", FIX32TOPRINT(adj_in_target),
	    state->mpu.ttarget);

	/* Calculate the derivative term */
	derivative = state->temp_history[state->cur_temp] -
		state->temp_history[(state->cur_temp + CPU_TEMP_HISTORY_SIZE - 1)
				    % CPU_TEMP_HISTORY_SIZE];
	derivative /= CPU_PID_INTERVAL;
	deriv_p = ((s64)state->mpu.pid_gd) * (s64)derivative;
	DBG("   deriv_p: %d\n", (int)(deriv_p >> 36));
	sum += deriv_p;

	/* Calculate the proportional term */
	proportional = temp - adj_in_target;
	prop_p = ((s64)state->mpu.pid_gp) * (s64)proportional;
	DBG("   prop_p: %d\n", (int)(prop_p >> 36));
	sum += prop_p;

	/* Scale sum */
	sum >>= 36;

	DBG("   sum: %d\n", (int)sum);
	state->rpm += (s32)sum;
}