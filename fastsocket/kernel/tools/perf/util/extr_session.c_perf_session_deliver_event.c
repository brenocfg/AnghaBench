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
struct TYPE_6__ {int /*<<< orphan*/  lost; } ;
struct TYPE_5__ {int type; } ;
union perf_event {TYPE_2__ lost; TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  u64 ;
struct perf_tool {int (* sample ) (struct perf_tool*,union perf_event*,struct perf_sample*,struct perf_evsel*,struct machine*) ;int (* mmap ) (struct perf_tool*,union perf_event*,struct perf_sample*,struct machine*) ;int (* comm ) (struct perf_tool*,union perf_event*,struct perf_sample*,struct machine*) ;int (* fork ) (struct perf_tool*,union perf_event*,struct perf_sample*,struct machine*) ;int (* exit ) (struct perf_tool*,union perf_event*,struct perf_sample*,struct machine*) ;int (* lost ) (struct perf_tool*,union perf_event*,struct perf_sample*,struct machine*) ;int (* read ) (struct perf_tool*,union perf_event*,struct perf_sample*,struct perf_evsel*,struct machine*) ;int (* throttle ) (struct perf_tool*,union perf_event*,struct perf_sample*,struct machine*) ;int (* unthrottle ) (struct perf_tool*,union perf_event*,struct perf_sample*,struct machine*) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  nr_unknown_events; int /*<<< orphan*/  total_lost; int /*<<< orphan*/  nr_unprocessable_samples; int /*<<< orphan*/  nr_unknown_id; } ;
struct TYPE_8__ {TYPE_3__ stats; } ;
struct perf_session {TYPE_4__ hists; int /*<<< orphan*/  evlist; } ;
struct perf_sample {int /*<<< orphan*/  id; } ;
struct perf_evsel {int /*<<< orphan*/  hists; } ;
struct machine {int dummy; } ;

/* Variables and functions */
#define  PERF_RECORD_COMM 136 
#define  PERF_RECORD_EXIT 135 
#define  PERF_RECORD_FORK 134 
#define  PERF_RECORD_LOST 133 
#define  PERF_RECORD_MMAP 132 
#define  PERF_RECORD_READ 131 
#define  PERF_RECORD_SAMPLE 130 
#define  PERF_RECORD_THROTTLE 129 
#define  PERF_RECORD_UNTHROTTLE 128 
 int /*<<< orphan*/  dump_event (struct perf_session*,union perf_event*,int /*<<< orphan*/ ,struct perf_sample*) ; 
 int /*<<< orphan*/  dump_sample (struct perf_evsel*,union perf_event*,struct perf_sample*) ; 
 int /*<<< orphan*/  hists__inc_nr_events (int /*<<< orphan*/ *,int) ; 
 int perf_event__process_lost (struct perf_tool*,union perf_event*,struct perf_sample*,struct machine*) ; 
 struct perf_evsel* perf_evlist__id2evsel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct machine* perf_session__find_machine_for_cpumode (struct perf_session*,union perf_event*) ; 
 int stub1 (struct perf_tool*,union perf_event*,struct perf_sample*,struct perf_evsel*,struct machine*) ; 
 int stub2 (struct perf_tool*,union perf_event*,struct perf_sample*,struct machine*) ; 
 int stub3 (struct perf_tool*,union perf_event*,struct perf_sample*,struct machine*) ; 
 int stub4 (struct perf_tool*,union perf_event*,struct perf_sample*,struct machine*) ; 
 int stub5 (struct perf_tool*,union perf_event*,struct perf_sample*,struct machine*) ; 
 int stub6 (struct perf_tool*,union perf_event*,struct perf_sample*,struct machine*) ; 
 int stub7 (struct perf_tool*,union perf_event*,struct perf_sample*,struct perf_evsel*,struct machine*) ; 
 int stub8 (struct perf_tool*,union perf_event*,struct perf_sample*,struct machine*) ; 
 int stub9 (struct perf_tool*,union perf_event*,struct perf_sample*,struct machine*) ; 

__attribute__((used)) static int perf_session_deliver_event(struct perf_session *session,
				      union perf_event *event,
				      struct perf_sample *sample,
				      struct perf_tool *tool,
				      u64 file_offset)
{
	struct perf_evsel *evsel;
	struct machine *machine;

	dump_event(session, event, file_offset, sample);

	evsel = perf_evlist__id2evsel(session->evlist, sample->id);
	if (evsel != NULL && event->header.type != PERF_RECORD_SAMPLE) {
		/*
		 * XXX We're leaving PERF_RECORD_SAMPLE unnacounted here
		 * because the tools right now may apply filters, discarding
		 * some of the samples. For consistency, in the future we
		 * should have something like nr_filtered_samples and remove
		 * the sample->period from total_sample_period, etc, KISS for
		 * now tho.
		 *
		 * Also testing against NULL allows us to handle files without
		 * attr.sample_id_all and/or without PERF_SAMPLE_ID. In the
		 * future probably it'll be a good idea to restrict event
		 * processing via perf_session to files with both set.
		 */
		hists__inc_nr_events(&evsel->hists, event->header.type);
	}

	machine = perf_session__find_machine_for_cpumode(session, event);

	switch (event->header.type) {
	case PERF_RECORD_SAMPLE:
		dump_sample(evsel, event, sample);
		if (evsel == NULL) {
			++session->hists.stats.nr_unknown_id;
			return 0;
		}
		if (machine == NULL) {
			++session->hists.stats.nr_unprocessable_samples;
			return 0;
		}
		return tool->sample(tool, event, sample, evsel, machine);
	case PERF_RECORD_MMAP:
		return tool->mmap(tool, event, sample, machine);
	case PERF_RECORD_COMM:
		return tool->comm(tool, event, sample, machine);
	case PERF_RECORD_FORK:
		return tool->fork(tool, event, sample, machine);
	case PERF_RECORD_EXIT:
		return tool->exit(tool, event, sample, machine);
	case PERF_RECORD_LOST:
		if (tool->lost == perf_event__process_lost)
			session->hists.stats.total_lost += event->lost.lost;
		return tool->lost(tool, event, sample, machine);
	case PERF_RECORD_READ:
		return tool->read(tool, event, sample, evsel, machine);
	case PERF_RECORD_THROTTLE:
		return tool->throttle(tool, event, sample, machine);
	case PERF_RECORD_UNTHROTTLE:
		return tool->unthrottle(tool, event, sample, machine);
	default:
		++session->hists.stats.nr_unknown_events;
		return -1;
	}
}