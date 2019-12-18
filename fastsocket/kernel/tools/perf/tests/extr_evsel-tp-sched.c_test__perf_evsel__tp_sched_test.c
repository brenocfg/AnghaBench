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
struct perf_evsel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_evsel__delete (struct perf_evsel*) ; 
 struct perf_evsel* perf_evsel__newtp (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ perf_evsel__test_field (struct perf_evsel*,char*,int,int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

int test__perf_evsel__tp_sched_test(void)
{
	struct perf_evsel *evsel = perf_evsel__newtp("sched", "sched_switch", 0);
	int ret = 0;

	if (evsel == NULL) {
		pr_debug("perf_evsel__new\n");
		return -1;
	}

	if (perf_evsel__test_field(evsel, "prev_comm", 16, true))
		ret = -1;

	if (perf_evsel__test_field(evsel, "prev_pid", 4, true))
		ret = -1;

	if (perf_evsel__test_field(evsel, "prev_prio", 4, true))
		ret = -1;

	if (perf_evsel__test_field(evsel, "prev_state", sizeof(long), true))
		ret = -1;

	if (perf_evsel__test_field(evsel, "next_comm", 16, true))
		ret = -1;

	if (perf_evsel__test_field(evsel, "next_pid", 4, true))
		ret = -1;

	if (perf_evsel__test_field(evsel, "next_prio", 4, true))
		ret = -1;

	perf_evsel__delete(evsel);

	evsel = perf_evsel__newtp("sched", "sched_wakeup", 0);

	if (perf_evsel__test_field(evsel, "comm", 16, true))
		ret = -1;

	if (perf_evsel__test_field(evsel, "pid", 4, true))
		ret = -1;

	if (perf_evsel__test_field(evsel, "prio", 4, true))
		ret = -1;

	if (perf_evsel__test_field(evsel, "success", 4, true))
		ret = -1;

	if (perf_evsel__test_field(evsel, "target_cpu", 4, true))
		ret = -1;

	return ret;
}