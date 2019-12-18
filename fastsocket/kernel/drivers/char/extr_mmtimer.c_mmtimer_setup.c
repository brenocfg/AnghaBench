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
 int mmtimer_int_pending (int) ; 
 int /*<<< orphan*/  mmtimer_setup_int_0 (int,unsigned long) ; 
 int /*<<< orphan*/  mmtimer_setup_int_1 (int,unsigned long) ; 
 int /*<<< orphan*/  mmtimer_setup_int_2 (int,unsigned long) ; 
 unsigned long rtc_time () ; 

__attribute__((used)) static int mmtimer_setup(int cpu, int comparator, unsigned long expires)
{

	switch (comparator) {
	case 0:
		mmtimer_setup_int_0(cpu, expires);
		break;
	case 1:
		mmtimer_setup_int_1(cpu, expires);
		break;
	case 2:
		mmtimer_setup_int_2(cpu, expires);
		break;
	}
	/* We might've missed our expiration time */
	if (rtc_time() <= expires)
		return 1;

	/*
	 * If an interrupt is already pending then its okay
	 * if not then we failed
	 */
	return mmtimer_int_pending(comparator);
}