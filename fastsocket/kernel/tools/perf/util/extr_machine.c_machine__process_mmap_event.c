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
struct TYPE_4__ {int /*<<< orphan*/  filename; int /*<<< orphan*/  pid; int /*<<< orphan*/  pgoff; int /*<<< orphan*/  len; int /*<<< orphan*/  start; } ;
struct TYPE_3__ {scalar_t__ misc; } ;
union perf_event {TYPE_2__ mmap; TYPE_1__ header; } ;
typedef  scalar_t__ u8 ;
struct thread {int dummy; } ;
struct map {int dummy; } ;
struct machine {int /*<<< orphan*/  user_dsos; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAP__FUNCTION ; 
 scalar_t__ PERF_RECORD_MISC_CPUMODE_MASK ; 
 scalar_t__ PERF_RECORD_MISC_GUEST_KERNEL ; 
 scalar_t__ PERF_RECORD_MISC_KERNEL ; 
 int /*<<< orphan*/  dump_printf (char*) ; 
 scalar_t__ dump_trace ; 
 struct thread* machine__findnew_thread (struct machine*,int /*<<< orphan*/ ) ; 
 int machine__process_kernel_mmap_event (struct machine*,union perf_event*) ; 
 struct map* map__new (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_event__fprintf_mmap (union perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  thread__insert_map (struct thread*,struct map*) ; 

int machine__process_mmap_event(struct machine *machine, union perf_event *event)
{
	u8 cpumode = event->header.misc & PERF_RECORD_MISC_CPUMODE_MASK;
	struct thread *thread;
	struct map *map;
	int ret = 0;

	if (dump_trace)
		perf_event__fprintf_mmap(event, stdout);

	if (cpumode == PERF_RECORD_MISC_GUEST_KERNEL ||
	    cpumode == PERF_RECORD_MISC_KERNEL) {
		ret = machine__process_kernel_mmap_event(machine, event);
		if (ret < 0)
			goto out_problem;
		return 0;
	}

	thread = machine__findnew_thread(machine, event->mmap.pid);
	if (thread == NULL)
		goto out_problem;
	map = map__new(&machine->user_dsos, event->mmap.start,
			event->mmap.len, event->mmap.pgoff,
			event->mmap.pid, event->mmap.filename,
			MAP__FUNCTION);
	if (map == NULL)
		goto out_problem;

	thread__insert_map(thread, map);
	return 0;

out_problem:
	dump_printf("problem processing PERF_RECORD_MMAP, skipping event.\n");
	return 0;
}