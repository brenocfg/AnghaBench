#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int pal; } ;
struct TYPE_6__ {TYPE_1__ m; } ;
struct TYPE_5__ {scalar_t__ CPUclock; int filter; int /*<<< orphan*/  gamma; } ;

/* Variables and functions */
 TYPE_3__ Pico ; 
 TYPE_2__ currentConfig ; 
 int /*<<< orphan*/  pemu_loop_prep () ; 
 scalar_t__ plat_target_cpu_clock_get () ; 
 int /*<<< orphan*/  plat_target_cpu_clock_set (scalar_t__) ; 
 int /*<<< orphan*/  plat_target_gamma_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plat_target_hwfilter_set (int) ; 
 int /*<<< orphan*/  plat_target_lcdrate_set (int) ; 

__attribute__((used)) static void emu_loop_prep(void)
{
	static int pal_old = -1;
	static int filter_old = -1;

	if (currentConfig.CPUclock != plat_target_cpu_clock_get())
		plat_target_cpu_clock_set(currentConfig.CPUclock);

	if (Pico.m.pal != pal_old) {
		plat_target_lcdrate_set(Pico.m.pal);
		pal_old = Pico.m.pal;
	}

	if (currentConfig.filter != filter_old) {
		plat_target_hwfilter_set(currentConfig.filter);
		filter_old = currentConfig.filter;
	}

	plat_target_gamma_set(currentConfig.gamma, 0);

	pemu_loop_prep();
}