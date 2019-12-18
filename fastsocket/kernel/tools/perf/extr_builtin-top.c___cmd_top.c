#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct sched_param {scalar_t__ sched_priority; } ;
struct perf_top {scalar_t__ samples; TYPE_2__* session; TYPE_1__* evlist; scalar_t__ realtime_prio; int /*<<< orphan*/  tool; int /*<<< orphan*/  target; } ;
typedef  int /*<<< orphan*/  pthread_t ;
struct TYPE_6__ {TYPE_1__* evlist; int /*<<< orphan*/  host_machine; } ;
struct TYPE_5__ {int /*<<< orphan*/  nr_fds; int /*<<< orphan*/  pollfd; int /*<<< orphan*/  threads; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  O_WRONLY ; 
 int /*<<< orphan*/  SCHED_FIFO ; 
 int /*<<< orphan*/  display_thread ; 
 int /*<<< orphan*/  display_thread_tui ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  perf_event__process ; 
 int /*<<< orphan*/  perf_event__synthesize_thread_map (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_event__synthesize_threads (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_session__delete (TYPE_2__*) ; 
 TYPE_2__* perf_session__new (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_session__set_id_hdr_size (TYPE_2__*) ; 
 scalar_t__ perf_target__has_task (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_top__mmap_read (struct perf_top*) ; 
 int perf_top__setup_sample_type (struct perf_top*) ; 
 int /*<<< orphan*/  perf_top__start_counters (struct perf_top*) ; 
 int poll (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct perf_top*) ; 
 scalar_t__ sched_setscheduler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sched_param*) ; 
 int /*<<< orphan*/  ui__error (char*) ; 
 scalar_t__ use_browser ; 

__attribute__((used)) static int __cmd_top(struct perf_top *top)
{
	pthread_t thread;
	int ret;
	/*
	 * FIXME: perf_session__new should allow passing a O_MMAP, so that all this
	 * mmap reading, etc is encapsulated in it. Use O_WRONLY for now.
	 */
	top->session = perf_session__new(NULL, O_WRONLY, false, false, NULL);
	if (top->session == NULL)
		return -ENOMEM;

	ret = perf_top__setup_sample_type(top);
	if (ret)
		goto out_delete;

	if (perf_target__has_task(&top->target))
		perf_event__synthesize_thread_map(&top->tool, top->evlist->threads,
						  perf_event__process,
						  &top->session->host_machine);
	else
		perf_event__synthesize_threads(&top->tool, perf_event__process,
					       &top->session->host_machine);
	perf_top__start_counters(top);
	top->session->evlist = top->evlist;
	perf_session__set_id_hdr_size(top->session);

	/* Wait for a minimal set of events before starting the snapshot */
	poll(top->evlist->pollfd, top->evlist->nr_fds, 100);

	perf_top__mmap_read(top);

	if (pthread_create(&thread, NULL, (use_browser > 0 ? display_thread_tui :
							    display_thread), top)) {
		ui__error("Could not create display thread.\n");
		exit(-1);
	}

	if (top->realtime_prio) {
		struct sched_param param;

		param.sched_priority = top->realtime_prio;
		if (sched_setscheduler(0, SCHED_FIFO, &param)) {
			ui__error("Could not set realtime priority.\n");
			exit(-1);
		}
	}

	while (1) {
		u64 hits = top->samples;

		perf_top__mmap_read(top);

		if (hits == top->samples)
			ret = poll(top->evlist->pollfd, top->evlist->nr_fds, 100);
	}

out_delete:
	perf_session__delete(top->session);
	top->session = NULL;

	return 0;
}