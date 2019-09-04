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
typedef  int /*<<< orphan*/  i386_intr_func_t ;
typedef  int /*<<< orphan*/  TSC_deadline_timer ;

/* Variables and functions */
 int CPUID_FEATURE_TSCTMR ; 
 int NSEC_PER_USEC ; 
 int /*<<< orphan*/  PE_parse_boot_argn (char*,int*,int) ; 
 int /*<<< orphan*/  UINT64_MAX ; 
 int /*<<< orphan*/  busFCvtt2n ; 
 int cpuid_features () ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lapic_set_timer_func (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  rtc_decrementer_max ; 
 int rtc_decrementer_min ; 
 int /*<<< orphan*/ * rtc_timer ; 
 int /*<<< orphan*/  rtc_timer_tsc_deadline ; 
 scalar_t__ rtclock_intr ; 
 int /*<<< orphan*/  tmrCvt (int,int /*<<< orphan*/ ) ; 

void
rtc_timer_init(void)
{
	int	TSC_deadline_timer = 0;

	/* See whether we can use the local apic in TSC-deadline mode */
	if ((cpuid_features() & CPUID_FEATURE_TSCTMR)) {
		TSC_deadline_timer = 1;
		PE_parse_boot_argn("TSC_deadline_timer", &TSC_deadline_timer,
				   sizeof(TSC_deadline_timer));
		printf("TSC Deadline Timer supported %s enabled\n",
			TSC_deadline_timer ? "and" : "but not");
	}

	if (TSC_deadline_timer) {
		rtc_timer = &rtc_timer_tsc_deadline;
		rtc_decrementer_max = UINT64_MAX;	/* effectively none */
		/*
		 * The min could be as low as 1nsec,
		 * but we're being conservative for now and making it the same
		 * as for the local apic timer.
		 */
		rtc_decrementer_min = 1*NSEC_PER_USEC;	/* 1 usec */
	} else {
		/*
		 * Compute the longest interval using LAPIC timer.
		 */
		rtc_decrementer_max = tmrCvt(0x7fffffffULL, busFCvtt2n);
		kprintf("maxDec: %lld\n", rtc_decrementer_max);
		rtc_decrementer_min = 1*NSEC_PER_USEC;	/* 1 usec */
	}

	/* Point LAPIC interrupts to hardclock() */
	lapic_set_timer_func((i386_intr_func_t) rtclock_intr);
}