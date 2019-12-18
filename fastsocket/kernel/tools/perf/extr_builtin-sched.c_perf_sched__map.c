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
struct perf_sched {int /*<<< orphan*/  max_cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  _SC_NPROCESSORS_CONF ; 
 scalar_t__ perf_sched__read_events (struct perf_sched*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_bad_events (struct perf_sched*) ; 
 int /*<<< orphan*/  setup_pager () ; 
 int /*<<< orphan*/  sysconf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int perf_sched__map(struct perf_sched *sched)
{
	sched->max_cpu = sysconf(_SC_NPROCESSORS_CONF);

	setup_pager();
	if (perf_sched__read_events(sched, true, NULL))
		return -1;
	print_bad_events(sched);
	return 0;
}