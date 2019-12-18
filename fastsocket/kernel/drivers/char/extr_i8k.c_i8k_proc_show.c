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
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMI_PRODUCT_SERIAL ; 
 int /*<<< orphan*/  I8K_FAN_LEFT ; 
 int /*<<< orphan*/  I8K_FAN_RIGHT ; 
 int /*<<< orphan*/  I8K_PROC_FMT ; 
 int /*<<< orphan*/  bios_version ; 
 int /*<<< orphan*/  i8k_get_dmi_data (int /*<<< orphan*/ ) ; 
 int i8k_get_fan_speed (int /*<<< orphan*/ ) ; 
 int i8k_get_fan_status (int /*<<< orphan*/ ) ; 
 int i8k_get_fn_status () ; 
 int i8k_get_power_status () ; 
 int i8k_get_temp (int /*<<< orphan*/ ) ; 
 scalar_t__ power_status ; 
 int seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int,int) ; 

__attribute__((used)) static int i8k_proc_show(struct seq_file *seq, void *offset)
{
	int fn_key, cpu_temp, ac_power;
	int left_fan, right_fan, left_speed, right_speed;

	cpu_temp	= i8k_get_temp(0);			/* 11100 µs */
	left_fan	= i8k_get_fan_status(I8K_FAN_LEFT);	/*   580 µs */
	right_fan	= i8k_get_fan_status(I8K_FAN_RIGHT);	/*   580 µs */
	left_speed	= i8k_get_fan_speed(I8K_FAN_LEFT);	/*   580 µs */
	right_speed	= i8k_get_fan_speed(I8K_FAN_RIGHT);	/*   580 µs */
	fn_key		= i8k_get_fn_status();			/*   750 µs */
	if (power_status)
		ac_power = i8k_get_power_status();		/* 14700 µs */
	else
		ac_power = -1;

	/*
	 * Info:
	 *
	 * 1)  Format version (this will change if format changes)
	 * 2)  BIOS version
	 * 3)  BIOS machine ID
	 * 4)  Cpu temperature
	 * 5)  Left fan status
	 * 6)  Right fan status
	 * 7)  Left fan speed
	 * 8)  Right fan speed
	 * 9)  AC power
	 * 10) Fn Key status
	 */
	return seq_printf(seq, "%s %s %s %d %d %d %d %d %d %d\n",
			  I8K_PROC_FMT,
			  bios_version,
			  i8k_get_dmi_data(DMI_PRODUCT_SERIAL),
			  cpu_temp,
			  left_fan, right_fan, left_speed, right_speed,
			  ac_power, fn_key);
}