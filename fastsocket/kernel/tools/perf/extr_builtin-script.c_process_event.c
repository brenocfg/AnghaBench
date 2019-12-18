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
typedef  union perf_event {int dummy; } perf_event ;
struct thread {int dummy; } ;
struct perf_sample {int /*<<< orphan*/  raw_size; int /*<<< orphan*/  raw_data; int /*<<< orphan*/  cpu; } ;
struct perf_event_attr {size_t type; } ;
struct perf_evsel {int /*<<< orphan*/  tp_format; struct perf_event_attr attr; } ;
struct machine {int dummy; } ;
struct addr_location {struct thread* thread; } ;
struct TYPE_4__ {scalar_t__ fields; } ;
struct TYPE_3__ {int /*<<< orphan*/  use_callchain; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR ; 
 int /*<<< orphan*/  DSO ; 
 int /*<<< orphan*/  IP ; 
 scalar_t__ PRINT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYM ; 
 int /*<<< orphan*/  SYMOFFSET ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  event_format__print (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_bts_event (struct perf_event_attr*) ; 
 TYPE_2__* output ; 
 int /*<<< orphan*/  perf_evsel__print_ip (struct perf_evsel*,union perf_event*,struct perf_sample*,struct machine*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  print_sample_addr (union perf_event*,struct perf_sample*,struct machine*,struct thread*,struct perf_event_attr*) ; 
 int /*<<< orphan*/  print_sample_bts (union perf_event*,struct perf_sample*,struct perf_evsel*,struct machine*,struct thread*) ; 
 int /*<<< orphan*/  print_sample_start (struct perf_sample*,struct thread*,struct perf_evsel*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 TYPE_1__ symbol_conf ; 

__attribute__((used)) static void process_event(union perf_event *event, struct perf_sample *sample,
			  struct perf_evsel *evsel, struct machine *machine,
			  struct addr_location *al)
{
	struct perf_event_attr *attr = &evsel->attr;
	struct thread *thread = al->thread;

	if (output[attr->type].fields == 0)
		return;

	print_sample_start(sample, thread, evsel);

	if (is_bts_event(attr)) {
		print_sample_bts(event, sample, evsel, machine, thread);
		return;
	}

	if (PRINT_FIELD(TRACE))
		event_format__print(evsel->tp_format, sample->cpu,
				    sample->raw_data, sample->raw_size);
	if (PRINT_FIELD(ADDR))
		print_sample_addr(event, sample, machine, thread, attr);

	if (PRINT_FIELD(IP)) {
		if (!symbol_conf.use_callchain)
			printf(" ");
		else
			printf("\n");
		perf_evsel__print_ip(evsel, event, sample, machine,
				     PRINT_FIELD(SYM), PRINT_FIELD(DSO),
				     PRINT_FIELD(SYMOFFSET));
	}

	printf("\n");
}