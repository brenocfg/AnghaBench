#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int cpu_decrementer; int cpu_timebase; scalar_t__ cpu_base_timebase; void* cpu_tbd_hardware_val; void* cpu_tbd_hardware_addr; int /*<<< orphan*/  cpu_set_decrementer_func; int /*<<< orphan*/  cpu_get_decrementer_func; int /*<<< orphan*/ * cpu_get_fiq_handler; } ;
typedef  TYPE_1__ cpu_data_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_6__ {int /*<<< orphan*/  tbd_set_decrementer; int /*<<< orphan*/  tbd_get_decrementer; int /*<<< orphan*/ * tbd_fiq_handler; } ;

/* Variables and functions */
 TYPE_1__ BootCpuData ; 
 TYPE_1__* getCpuDatap () ; 
 scalar_t__ ml_get_hwclock () ; 
 scalar_t__ rtclock_base_abstime ; 
 scalar_t__ rtclock_timebase_addr ; 
 TYPE_2__ rtclock_timebase_func ; 
 scalar_t__ rtclock_timebase_val ; 
 scalar_t__ wake_abstime ; 

void
cpu_timebase_init(boolean_t from_boot)
{
	cpu_data_t *cdp = getCpuDatap();

	if (cdp->cpu_get_fiq_handler == NULL) {
		cdp->cpu_get_fiq_handler = rtclock_timebase_func.tbd_fiq_handler;
		cdp->cpu_get_decrementer_func = rtclock_timebase_func.tbd_get_decrementer;
		cdp->cpu_set_decrementer_func = rtclock_timebase_func.tbd_set_decrementer;
		cdp->cpu_tbd_hardware_addr = (void *)rtclock_timebase_addr;
		cdp->cpu_tbd_hardware_val = (void *)rtclock_timebase_val;
	}

	if (!from_boot && (cdp == &BootCpuData)) {
		/*
		 * When we wake from sleep, we have no guarantee about the state
		 * of the hardware timebase.  It may have kept ticking across sleep, or
		 * it may have reset.
		 *
		 * To deal with this, we calculate an offset to the clock that will
		 * produce a timebase value wake_abstime at the point the boot
		 * CPU calls cpu_timebase_init on wake.
		 *
		 * This ensures that mach_absolute_time() stops ticking across sleep.
		 */
		rtclock_base_abstime = wake_abstime - ml_get_hwclock();
	}

	cdp->cpu_decrementer = 0x7FFFFFFFUL;
	cdp->cpu_timebase = 0x0UL;
	cdp->cpu_base_timebase = rtclock_base_abstime;
}