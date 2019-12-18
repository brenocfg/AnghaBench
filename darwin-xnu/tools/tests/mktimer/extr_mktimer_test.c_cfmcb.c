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
typedef  double uint64_t ;
typedef  int /*<<< orphan*/  CFMachPortRef ;
typedef  int /*<<< orphan*/  CFIndex ;

/* Variables and functions */
 int /*<<< orphan*/  MK_TIMER_CRITICAL ; 
 double conversion ; 
 double deadline ; 
 double interval_abs ; 
 int jiterations ; 
 int /*<<< orphan*/  leeway_abs ; 
 double mach_absolute_time () ; 
 double max_jitter ; 
 double min_jitter ; 
 int /*<<< orphan*/  mk_timer_arm (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  mk_timer_arm_leeway (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,double,double,double) ; 
 int report ; 
 int /*<<< orphan*/  timerPort ; 
 double totaljitter ; 
 scalar_t__ use_leeway ; 

void cfmcb(CFMachPortRef port, void *msg, CFIndex size, void *msginfo) {
	uint64_t ctime = mach_absolute_time();
	uint64_t jitter = 0;

	if (deadline) {
		jitter = (ctime - deadline);
		if (jitter > max_jitter) {
			max_jitter = jitter;
		}

		if (jitter < min_jitter) {
			min_jitter = jitter;
		}

		totaljitter += jitter;
		if ((++jiterations % report) == 0) {
			printf("max_jitter: %g (ns), min_jitter: %g (ns), average_jitter: %g (ns)\n", max_jitter * conversion, min_jitter * conversion, ((double)totaljitter/(double)jiterations) * conversion);
			max_jitter = 0; min_jitter = ~0ULL; jiterations = 0; totaljitter = 0;
		}
	}

	deadline = mach_absolute_time() + interval_abs;

	if (use_leeway) {
		mk_timer_arm_leeway(timerPort, MK_TIMER_CRITICAL, deadline, leeway_abs);
	} else {
		mk_timer_arm(timerPort, deadline);
	}
}