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
struct perf_tool {int ordered_samples; int /*<<< orphan*/  comm; int /*<<< orphan*/  sample; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  input_name ; 
 int /*<<< orphan*/  lock_tracepoints ; 
 int /*<<< orphan*/  perf_event__process_comm ; 
 int /*<<< orphan*/  perf_session__new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct perf_tool*) ; 
 int perf_session__process_events (int /*<<< orphan*/ ,struct perf_tool*) ; 
 scalar_t__ perf_session__set_tracepoints_handlers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  process_sample_event ; 
 int /*<<< orphan*/  session ; 

__attribute__((used)) static int read_events(void)
{
	struct perf_tool eops = {
		.sample		 = process_sample_event,
		.comm		 = perf_event__process_comm,
		.ordered_samples = true,
	};
	session = perf_session__new(input_name, O_RDONLY, 0, false, &eops);
	if (!session) {
		pr_err("Initializing perf session failed\n");
		return -1;
	}

	if (perf_session__set_tracepoints_handlers(session, lock_tracepoints)) {
		pr_err("Initializing perf session tracepoint handlers failed\n");
		return -1;
	}

	return perf_session__process_events(session, &eops);
}