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
typedef  void* uint64_t ;
struct TYPE_4__ {void* cpu_frequency_max_hz; void* cpu_frequency_min_hz; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* rtc_config ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  clock_timebase_init () ; 
 scalar_t__ cpu_number () ; 
 TYPE_2__ gPEClockFrequencyInfo ; 
 scalar_t__ master_cpu ; 
 int /*<<< orphan*/  ml_get_interrupts_enabled () ; 
 int /*<<< orphan*/  ml_init_delay_spin_threshold (int) ; 
 int /*<<< orphan*/  ml_init_lock_timeout () ; 
 void* rtc_export_speed (int) ; 
 TYPE_1__* rtc_timer ; 
 int /*<<< orphan*/  rtc_timer_init () ; 
 int /*<<< orphan*/  rtc_timer_start () ; 
 int /*<<< orphan*/  stub1 () ; 
 int tscFreq ; 

int
rtclock_init(void)
{
	uint64_t	cycles;

	assert(!ml_get_interrupts_enabled());

	if (cpu_number() == master_cpu) {

		assert(tscFreq);

		/*
		 * Adjust and set the exported cpu speed.
		 */
		cycles = rtc_export_speed(tscFreq);

		/*
		 * Set min/max to actual.
		 * ACPI may update these later if speed-stepping is detected.
		 */
		gPEClockFrequencyInfo.cpu_frequency_min_hz = cycles;
		gPEClockFrequencyInfo.cpu_frequency_max_hz = cycles;

		rtc_timer_init();
		clock_timebase_init();
		ml_init_lock_timeout();
		ml_init_delay_spin_threshold(10);
	}

    	/* Set fixed configuration for lapic timers */
	rtc_timer->rtc_config();
	rtc_timer_start();

	return (1);
}