#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  target; } ;
struct trace {int /*<<< orphan*/  host; TYPE_1__ opts; } ;
struct perf_evlist {int /*<<< orphan*/  threads; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_KERNEL_ID ; 
 int /*<<< orphan*/  machine__create_kernel_maps (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  machine__init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int perf_event__synthesize_thread_map (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int perf_event__synthesize_threads (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ perf_target__has_task (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symbol__exit () ; 
 int symbol__init () ; 
 int /*<<< orphan*/  trace__tool_process ; 

__attribute__((used)) static int trace__symbols_init(struct trace *trace, struct perf_evlist *evlist)
{
	int err = symbol__init();

	if (err)
		return err;

	machine__init(&trace->host, "", HOST_KERNEL_ID);
	machine__create_kernel_maps(&trace->host);

	if (perf_target__has_task(&trace->opts.target)) {
		err = perf_event__synthesize_thread_map(NULL, evlist->threads,
							trace__tool_process,
							&trace->host);
	} else {
		err = perf_event__synthesize_threads(NULL, trace__tool_process,
						     &trace->host);
	}

	if (err)
		symbol__exit();

	return err;
}