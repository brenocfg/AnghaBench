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
struct TYPE_2__ {int /*<<< orphan*/  comm; int /*<<< orphan*/  tid; } ;
union perf_event {TYPE_1__ comm; } ;
struct thread {int dummy; } ;
struct machine {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_printf (char*) ; 
 scalar_t__ dump_trace ; 
 struct thread* machine__findnew_thread (struct machine*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_event__fprintf_comm (union perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ thread__set_comm (struct thread*,int /*<<< orphan*/ ) ; 

int machine__process_comm_event(struct machine *machine, union perf_event *event)
{
	struct thread *thread = machine__findnew_thread(machine, event->comm.tid);

	if (dump_trace)
		perf_event__fprintf_comm(event, stdout);

	if (thread == NULL || thread__set_comm(thread, event->comm.comm)) {
		dump_printf("problem processing PERF_RECORD_COMM, skipping event.\n");
		return -1;
	}

	return 0;
}