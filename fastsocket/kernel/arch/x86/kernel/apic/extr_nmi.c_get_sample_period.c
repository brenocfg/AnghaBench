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

/* Variables and functions */
 scalar_t__ NMI_LOCAL_APIC ; 
 unsigned long NSEC_PER_SEC ; 
 int /*<<< orphan*/  do_div (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nmi_hz ; 
 scalar_t__ nmi_watchdog ; 

__attribute__((used)) static unsigned long get_sample_period(void)
{
	unsigned long count = NSEC_PER_SEC;

	/*
	 * for the NMI_LOCAL_APIC case:
	 * nmi_hz is set to the period of the nmi watchdog
	 * a timer is needed to match that frequency otherwise
	 * the nmi watchdog thinks the cpu is deadlock
	 * nb: the nmi watchdog can handle 5 misses before declaring a
	 * deadlock, so match the frequency in this case is ok
	 */
	if (nmi_watchdog == NMI_LOCAL_APIC)
		do_div(count, nmi_hz);

	return count;
}