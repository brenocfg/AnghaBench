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
typedef  union perf_event {int dummy; } perf_event ;
struct perf_sample {int dummy; } ;
struct perf_evsel {int dummy; } ;
struct machine {int dummy; } ;
struct addr_location {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  perl_process_event_generic (union perf_event*,struct perf_sample*,struct perf_evsel*,struct machine*,struct addr_location*) ; 
 int /*<<< orphan*/  perl_process_tracepoint (union perf_event*,struct perf_sample*,struct perf_evsel*,struct machine*,struct addr_location*) ; 

__attribute__((used)) static void perl_process_event(union perf_event *event,
			       struct perf_sample *sample,
			       struct perf_evsel *evsel,
			       struct machine *machine,
			       struct addr_location *al)
{
	perl_process_tracepoint(event, sample, evsel, machine, al);
	perl_process_event_generic(event, sample, evsel, machine, al);
}