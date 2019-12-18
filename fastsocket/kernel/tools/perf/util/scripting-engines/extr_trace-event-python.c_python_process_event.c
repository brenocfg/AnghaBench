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
typedef  union perf_event {int dummy; } perf_event ;
struct perf_sample {int dummy; } ;
struct TYPE_2__ {int type; } ;
struct perf_evsel {TYPE_1__ attr; } ;
struct machine {int dummy; } ;
struct addr_location {int dummy; } ;

/* Variables and functions */
#define  PERF_TYPE_TRACEPOINT 128 
 int /*<<< orphan*/  python_process_general_event (union perf_event*,struct perf_sample*,struct perf_evsel*,struct machine*,struct addr_location*) ; 
 int /*<<< orphan*/  python_process_tracepoint (union perf_event*,struct perf_sample*,struct perf_evsel*,struct machine*,struct addr_location*) ; 

__attribute__((used)) static void python_process_event(union perf_event *perf_event,
				 struct perf_sample *sample,
				 struct perf_evsel *evsel,
				 struct machine *machine,
				 struct addr_location *al)
{
	switch (evsel->attr.type) {
	case PERF_TYPE_TRACEPOINT:
		python_process_tracepoint(perf_event, sample, evsel,
					  machine, al);
		break;
	/* Reserve for future process_hw/sw/raw APIs */
	default:
		python_process_general_event(perf_event, sample, evsel,
					     machine, al);
	}
}