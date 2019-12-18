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
struct TYPE_3__ {int /*<<< orphan*/ * nr_events; int /*<<< orphan*/  total_lost; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;
struct perf_session {TYPE_2__ hists; } ;
struct perf_sched {int /*<<< orphan*/  nr_lost_chunks; int /*<<< orphan*/  nr_lost_events; int /*<<< orphan*/  nr_events; int /*<<< orphan*/  tool; } ;
struct perf_evsel_str_handler {char* member_0; int /*<<< orphan*/  member_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 size_t PERF_RECORD_LOST ; 
 int /*<<< orphan*/  input_name ; 
 int /*<<< orphan*/  perf_session__delete (struct perf_session*) ; 
 scalar_t__ perf_session__has_traces (struct perf_session*,char*) ; 
 struct perf_session* perf_session__new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int perf_session__process_events (struct perf_session*,int /*<<< orphan*/ *) ; 
 scalar_t__ perf_session__set_tracepoints_handlers (struct perf_session*,struct perf_evsel_str_handler const*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  process_sched_exit_event ; 
 int /*<<< orphan*/  process_sched_fork_event ; 
 int /*<<< orphan*/  process_sched_migrate_task_event ; 
 int /*<<< orphan*/  process_sched_runtime_event ; 
 int /*<<< orphan*/  process_sched_switch_event ; 
 int /*<<< orphan*/  process_sched_wakeup_event ; 

__attribute__((used)) static int perf_sched__read_events(struct perf_sched *sched, bool destroy,
				   struct perf_session **psession)
{
	const struct perf_evsel_str_handler handlers[] = {
		{ "sched:sched_switch",	      process_sched_switch_event, },
		{ "sched:sched_stat_runtime", process_sched_runtime_event, },
		{ "sched:sched_wakeup",	      process_sched_wakeup_event, },
		{ "sched:sched_wakeup_new",   process_sched_wakeup_event, },
		{ "sched:sched_process_fork", process_sched_fork_event, },
		{ "sched:sched_process_exit", process_sched_exit_event, },
		{ "sched:sched_migrate_task", process_sched_migrate_task_event, },
	};
	struct perf_session *session;

	session = perf_session__new(input_name, O_RDONLY, 0, false, &sched->tool);
	if (session == NULL) {
		pr_debug("No Memory for session\n");
		return -1;
	}

	if (perf_session__set_tracepoints_handlers(session, handlers))
		goto out_delete;

	if (perf_session__has_traces(session, "record -R")) {
		int err = perf_session__process_events(session, &sched->tool);
		if (err) {
			pr_err("Failed to process events, error %d", err);
			goto out_delete;
		}

		sched->nr_events      = session->hists.stats.nr_events[0];
		sched->nr_lost_events = session->hists.stats.total_lost;
		sched->nr_lost_chunks = session->hists.stats.nr_events[PERF_RECORD_LOST];
	}

	if (destroy)
		perf_session__delete(session);

	if (psession)
		*psession = session;

	return 0;

out_delete:
	perf_session__delete(session);
	return -1;
}