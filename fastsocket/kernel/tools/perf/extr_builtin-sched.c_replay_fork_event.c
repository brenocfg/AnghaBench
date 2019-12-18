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
typedef  int u32 ;
struct perf_sched {int dummy; } ;
struct perf_sample {int dummy; } ;
struct perf_evsel {int dummy; } ;

/* Variables and functions */
 int perf_evsel__intval (struct perf_evsel*,struct perf_sample*,char*) ; 
 char* perf_evsel__strval (struct perf_evsel*,struct perf_sample*,char*) ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 int /*<<< orphan*/  register_pid (struct perf_sched*,int const,char const*) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int replay_fork_event(struct perf_sched *sched, struct perf_evsel *evsel,
			     struct perf_sample *sample)
{
	const char *parent_comm = perf_evsel__strval(evsel, sample, "parent_comm"),
		   *child_comm  = perf_evsel__strval(evsel, sample, "child_comm");
	const u32 parent_pid  = perf_evsel__intval(evsel, sample, "parent_pid"),
		  child_pid  = perf_evsel__intval(evsel, sample, "child_pid");

	if (verbose) {
		printf("sched_fork event %p\n", evsel);
		printf("... parent: %s/%d\n", parent_comm, parent_pid);
		printf("...  child: %s/%d\n", child_comm, child_pid);
	}

	register_pid(sched, parent_pid, parent_comm);
	register_pid(sched, child_pid, child_comm);
	return 0;
}