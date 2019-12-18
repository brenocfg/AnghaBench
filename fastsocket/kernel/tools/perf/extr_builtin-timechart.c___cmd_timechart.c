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
struct perf_tool {int ordered_samples; int /*<<< orphan*/  sample; int /*<<< orphan*/  exit; int /*<<< orphan*/  fork; int /*<<< orphan*/  comm; } ;
struct perf_session {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  end_sample_processing () ; 
 double first_time ; 
 int /*<<< orphan*/  input_name ; 
 double last_time ; 
 int /*<<< orphan*/  perf_session__delete (struct perf_session*) ; 
 int /*<<< orphan*/  perf_session__has_traces (struct perf_session*,char*) ; 
 struct perf_session* perf_session__new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct perf_tool*) ; 
 int perf_session__process_events (struct perf_session*,struct perf_tool*) ; 
 int /*<<< orphan*/  pr_info (char*,double,char const*) ; 
 int /*<<< orphan*/  process_comm_event ; 
 int /*<<< orphan*/  process_exit_event ; 
 int /*<<< orphan*/  process_fork_event ; 
 int /*<<< orphan*/  process_sample_event ; 
 int /*<<< orphan*/  sort_pids () ; 
 int /*<<< orphan*/  write_svg_file (char const*) ; 

__attribute__((used)) static int __cmd_timechart(const char *output_name)
{
	struct perf_tool perf_timechart = {
		.comm		 = process_comm_event,
		.fork		 = process_fork_event,
		.exit		 = process_exit_event,
		.sample		 = process_sample_event,
		.ordered_samples = true,
	};
	struct perf_session *session = perf_session__new(input_name, O_RDONLY,
							 0, false, &perf_timechart);
	int ret = -EINVAL;

	if (session == NULL)
		return -ENOMEM;

	if (!perf_session__has_traces(session, "timechart record"))
		goto out_delete;

	ret = perf_session__process_events(session, &perf_timechart);
	if (ret)
		goto out_delete;

	end_sample_processing();

	sort_pids();

	write_svg_file(output_name);

	pr_info("Written %2.1f seconds of trace to %s.\n",
		(last_time - first_time) / 1000000000.0, output_name);
out_delete:
	perf_session__delete(session);
	return ret;
}