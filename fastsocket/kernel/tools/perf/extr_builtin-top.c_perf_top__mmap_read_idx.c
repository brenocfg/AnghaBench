#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int misc; scalar_t__ type; } ;
struct TYPE_5__ {int /*<<< orphan*/  pid; } ;
union perf_event {TYPE_2__ header; TYPE_1__ ip; } ;
typedef  int u8 ;
struct perf_top {int /*<<< orphan*/  tool; int /*<<< orphan*/  guest_us_samples; int /*<<< orphan*/  guest_kernel_samples; int /*<<< orphan*/  hide_kernel_symbols; int /*<<< orphan*/  kernel_samples; int /*<<< orphan*/  hide_user_symbols; int /*<<< orphan*/  us_samples; int /*<<< orphan*/  samples; int /*<<< orphan*/  evlist; struct perf_session* session; } ;
struct TYPE_7__ {int /*<<< orphan*/  nr_unknown_events; } ;
struct TYPE_8__ {TYPE_3__ stats; } ;
struct perf_session {TYPE_4__ hists; int /*<<< orphan*/  evlist; } ;
struct perf_sample {int /*<<< orphan*/  id; } ;
struct perf_evsel {int /*<<< orphan*/  hists; } ;
struct machine {int dummy; } ;

/* Variables and functions */
 scalar_t__ PERF_RECORD_MAX ; 
 int PERF_RECORD_MISC_CPUMODE_MASK ; 
#define  PERF_RECORD_MISC_GUEST_KERNEL 131 
#define  PERF_RECORD_MISC_GUEST_USER 130 
#define  PERF_RECORD_MISC_KERNEL 129 
#define  PERF_RECORD_MISC_USER 128 
 scalar_t__ PERF_RECORD_SAMPLE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hists__inc_nr_events (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  machine__process_event (struct machine*,union perf_event*) ; 
 int /*<<< orphan*/  perf_event__process_sample (int /*<<< orphan*/ *,union perf_event*,struct perf_evsel*,struct perf_sample*,struct machine*) ; 
 struct perf_evsel* perf_evlist__id2evsel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 union perf_event* perf_evlist__mmap_read (int /*<<< orphan*/ ,int) ; 
 int perf_evlist__parse_sample (int /*<<< orphan*/ ,union perf_event*,struct perf_sample*) ; 
 struct machine* perf_session__find_host_machine (struct perf_session*) ; 
 struct machine* perf_session__find_machine (struct perf_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static void perf_top__mmap_read_idx(struct perf_top *top, int idx)
{
	struct perf_sample sample;
	struct perf_evsel *evsel;
	struct perf_session *session = top->session;
	union perf_event *event;
	struct machine *machine;
	u8 origin;
	int ret;

	while ((event = perf_evlist__mmap_read(top->evlist, idx)) != NULL) {
		ret = perf_evlist__parse_sample(top->evlist, event, &sample);
		if (ret) {
			pr_err("Can't parse sample, err = %d\n", ret);
			continue;
		}

		evsel = perf_evlist__id2evsel(session->evlist, sample.id);
		assert(evsel != NULL);

		origin = event->header.misc & PERF_RECORD_MISC_CPUMODE_MASK;

		if (event->header.type == PERF_RECORD_SAMPLE)
			++top->samples;

		switch (origin) {
		case PERF_RECORD_MISC_USER:
			++top->us_samples;
			if (top->hide_user_symbols)
				continue;
			machine = perf_session__find_host_machine(session);
			break;
		case PERF_RECORD_MISC_KERNEL:
			++top->kernel_samples;
			if (top->hide_kernel_symbols)
				continue;
			machine = perf_session__find_host_machine(session);
			break;
		case PERF_RECORD_MISC_GUEST_KERNEL:
			++top->guest_kernel_samples;
			machine = perf_session__find_machine(session, event->ip.pid);
			break;
		case PERF_RECORD_MISC_GUEST_USER:
			++top->guest_us_samples;
			/*
			 * TODO: we don't process guest user from host side
			 * except simple counting.
			 */
			/* Fall thru */
		default:
			continue;
		}


		if (event->header.type == PERF_RECORD_SAMPLE) {
			perf_event__process_sample(&top->tool, event, evsel,
						   &sample, machine);
		} else if (event->header.type < PERF_RECORD_MAX) {
			hists__inc_nr_events(&evsel->hists, event->header.type);
			machine__process_event(machine, event);
		} else
			++session->hists.stats.nr_unknown_events;
	}
}