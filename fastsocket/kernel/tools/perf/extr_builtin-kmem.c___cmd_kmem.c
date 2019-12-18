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
struct perf_session {int dummy; } ;
struct perf_evsel_str_handler {char* member_0; int /*<<< orphan*/  member_1; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  input_name ; 
 int /*<<< orphan*/  perf_evsel__process_alloc_event ; 
 int /*<<< orphan*/  perf_evsel__process_alloc_node_event ; 
 int /*<<< orphan*/  perf_evsel__process_free_event ; 
 int /*<<< orphan*/  perf_kmem ; 
 scalar_t__ perf_session__create_kernel_maps (struct perf_session*) ; 
 int /*<<< orphan*/  perf_session__delete (struct perf_session*) ; 
 int /*<<< orphan*/  perf_session__has_traces (struct perf_session*,char*) ; 
 struct perf_session* perf_session__new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int perf_session__process_events (struct perf_session*,int /*<<< orphan*/ *) ; 
 scalar_t__ perf_session__set_tracepoints_handlers (struct perf_session*,struct perf_evsel_str_handler const*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  print_result (struct perf_session*) ; 
 int /*<<< orphan*/  setup_pager () ; 
 int /*<<< orphan*/  sort_result () ; 

__attribute__((used)) static int __cmd_kmem(void)
{
	int err = -EINVAL;
	struct perf_session *session;
	const struct perf_evsel_str_handler kmem_tracepoints[] = {
		{ "kmem:kmalloc",		perf_evsel__process_alloc_event, },
    		{ "kmem:kmem_cache_alloc",	perf_evsel__process_alloc_event, },
		{ "kmem:kmalloc_node",		perf_evsel__process_alloc_node_event, },
    		{ "kmem:kmem_cache_alloc_node", perf_evsel__process_alloc_node_event, },
		{ "kmem:kfree",			perf_evsel__process_free_event, },
    		{ "kmem:kmem_cache_free",	perf_evsel__process_free_event, },
	};

	session = perf_session__new(input_name, O_RDONLY, 0, false, &perf_kmem);
	if (session == NULL)
		return -ENOMEM;

	if (perf_session__create_kernel_maps(session) < 0)
		goto out_delete;

	if (!perf_session__has_traces(session, "kmem record"))
		goto out_delete;

	if (perf_session__set_tracepoints_handlers(session, kmem_tracepoints)) {
		pr_err("Initializing perf session tracepoint handlers failed\n");
		return -1;
	}

	setup_pager();
	err = perf_session__process_events(session, &perf_kmem);
	if (err != 0)
		goto out_delete;
	sort_result();
	print_result(session);
out_delete:
	perf_session__delete(session);
	return err;
}