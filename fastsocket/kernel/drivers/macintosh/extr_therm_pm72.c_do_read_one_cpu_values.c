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
typedef  int u64 ;
struct TYPE_2__ {int mdiode; int bdiode; } ;
struct cpu_pid_state {int cur_temp; int cur_power; scalar_t__ index; int rpm; int last_temp; int voltage; int current_a; int last_power; TYPE_1__ mpu; int /*<<< orphan*/  overtemp; } ;
typedef  int s32 ;

/* Variables and functions */
 int ADC_CPU_CURRENT_SCALE ; 
 int ADC_CPU_VOLTAGE_SCALE ; 
 int CPUA_EXHAUST_FAN_RPM_INDEX ; 
 int CPUB_EXHAUST_FAN_RPM_INDEX ; 
 int CPU_A1_FAN_RPM_INDEX ; 
 int CPU_B1_FAN_RPM_INDEX ; 
 scalar_t__ CPU_PID_TYPE_RACKMAC ; 
 int /*<<< orphan*/  DBG (char*,scalar_t__,...) ; 
 int EIO ; 
 int FIX32TOPRINT (int) ; 
 int /*<<< orphan*/  RPM_PID_USE_ACTUAL_SPEED ; 
 scalar_t__ cpu_pid_type ; 
 int get_rpm_fan (int,int) ; 
 int read_smon_adc (struct cpu_pid_state*,int) ; 

__attribute__((used)) static int do_read_one_cpu_values(struct cpu_pid_state *state, s32 *temp, s32 *power)
{
	s32 ltemp, volts, amps;
	int index, rc = 0;

	/* Default (in case of error) */
	*temp = state->cur_temp;
	*power = state->cur_power;

	if (cpu_pid_type == CPU_PID_TYPE_RACKMAC)
		index = (state->index == 0) ?
			CPU_A1_FAN_RPM_INDEX : CPU_B1_FAN_RPM_INDEX;
	else
		index = (state->index == 0) ?
			CPUA_EXHAUST_FAN_RPM_INDEX : CPUB_EXHAUST_FAN_RPM_INDEX;

	/* Read current fan status */
	rc = get_rpm_fan(index, !RPM_PID_USE_ACTUAL_SPEED);
	if (rc < 0) {
		/* XXX What do we do now ? Nothing for now, keep old value, but
		 * return error upstream
		 */
		DBG("  cpu %d, fan reading error !\n", state->index);
	} else {
		state->rpm = rc;
		DBG("  cpu %d, exhaust RPM: %d\n", state->index, state->rpm);
	}

	/* Get some sensor readings and scale it */
	ltemp = read_smon_adc(state, 1);
	if (ltemp == -1) {
		/* XXX What do we do now ? */
		state->overtemp++;
		if (rc == 0)
			rc = -EIO;
		DBG("  cpu %d, temp reading error !\n", state->index);
	} else {
		/* Fixup temperature according to diode calibration
		 */
		DBG("  cpu %d, temp raw: %04x, m_diode: %04x, b_diode: %04x\n",
		    state->index,
		    ltemp, state->mpu.mdiode, state->mpu.bdiode);
		*temp = ((s32)ltemp * (s32)state->mpu.mdiode + ((s32)state->mpu.bdiode << 12)) >> 2;
		state->last_temp = *temp;
		DBG("  temp: %d.%03d\n", FIX32TOPRINT((*temp)));
	}

	/*
	 * Read voltage & current and calculate power
	 */
	volts = read_smon_adc(state, 3);
	amps = read_smon_adc(state, 4);

	/* Scale voltage and current raw sensor values according to fixed scales
	 * obtained in Darwin and calculate power from I and V
	 */
	volts *= ADC_CPU_VOLTAGE_SCALE;
	amps *= ADC_CPU_CURRENT_SCALE;
	*power = (((u64)volts) * ((u64)amps)) >> 16;
	state->voltage = volts;
	state->current_a = amps;
	state->last_power = *power;

	DBG("  cpu %d, current: %d.%03d, voltage: %d.%03d, power: %d.%03d W\n",
	    state->index, FIX32TOPRINT(state->current_a),
	    FIX32TOPRINT(state->voltage), FIX32TOPRINT(*power));

	return 0;
}