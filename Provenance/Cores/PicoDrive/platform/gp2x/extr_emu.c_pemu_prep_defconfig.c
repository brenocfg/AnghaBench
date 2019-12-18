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
typedef  scalar_t__ gp2x_soc_t ;
struct TYPE_2__ {int analog_deadzone; int EmuOpt; int /*<<< orphan*/  s_PicoOpt; int /*<<< orphan*/  renderer32x; int /*<<< orphan*/  CPUclock; } ;

/* Variables and functions */
 int EOPT_SHOW_RTC ; 
 int EOPT_WIZ_TEAR_FIX ; 
 int /*<<< orphan*/  POPT_EN_MCD_GFX ; 
 int /*<<< orphan*/  POPT_EXT_FM ; 
 int /*<<< orphan*/  RT_8BIT_FAST ; 
 scalar_t__ SOCID_MMSP2 ; 
 scalar_t__ SOCID_POLLUX ; 
 TYPE_1__ defaultConfig ; 
 int /*<<< orphan*/  default_cpu_clock ; 
 scalar_t__ soc_detect () ; 

void pemu_prep_defconfig(void)
{
	gp2x_soc_t soc;

	defaultConfig.CPUclock = default_cpu_clock;
	defaultConfig.renderer32x = RT_8BIT_FAST;
	defaultConfig.analog_deadzone = 50;

	soc = soc_detect();
	if (soc == SOCID_MMSP2)
		defaultConfig.s_PicoOpt |= POPT_EXT_FM;
	else if (soc == SOCID_POLLUX) {
		defaultConfig.EmuOpt |= EOPT_WIZ_TEAR_FIX|EOPT_SHOW_RTC;
		defaultConfig.s_PicoOpt |= POPT_EN_MCD_GFX;
	}
}