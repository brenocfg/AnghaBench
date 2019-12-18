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
struct thread {int dummy; } ;
struct perf_sample {int dummy; } ;
struct perf_event_attr {int dummy; } ;
struct perf_evsel {struct perf_event_attr attr; } ;
struct machine {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  use_callchain; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR ; 
 int /*<<< orphan*/  DSO ; 
 int /*<<< orphan*/  IP ; 
 scalar_t__ PRINT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYM ; 
 int /*<<< orphan*/  SYMOFFSET ; 
 int /*<<< orphan*/  perf_evsel__print_ip (struct perf_evsel*,union perf_event*,struct perf_sample*,struct machine*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  print_sample_addr (union perf_event*,struct perf_sample*,struct machine*,struct thread*,struct perf_event_attr*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 TYPE_1__ symbol_conf ; 

__attribute__((used)) static void print_sample_bts(union perf_event *event,
			     struct perf_sample *sample,
			     struct perf_evsel *evsel,
			     struct machine *machine,
			     struct thread *thread)
{
	struct perf_event_attr *attr = &evsel->attr;

	/* print branch_from information */
	if (PRINT_FIELD(IP)) {
		if (!symbol_conf.use_callchain)
			printf(" ");
		else
			printf("\n");
		perf_evsel__print_ip(evsel, event, sample, machine,
				     PRINT_FIELD(SYM), PRINT_FIELD(DSO),
				     PRINT_FIELD(SYMOFFSET));
	}

	printf(" => ");

	/* print branch_to information */
	if (PRINT_FIELD(ADDR))
		print_sample_addr(event, sample, machine, thread, attr);

	printf("\n");
}