#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  rip; } ;
struct TYPE_12__ {TYPE_1__ isf; scalar_t__ rbp; } ;
struct TYPE_13__ {TYPE_2__ ss_64; } ;
typedef  TYPE_3__ x86_saved_state_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  scalar_t__ uint64_t ;
typedef  TYPE_4__* thread_t ;
typedef  TYPE_5__* task_t ;
typedef  int /*<<< orphan*/  pmap_t ;
struct TYPE_15__ {int thread_count; int /*<<< orphan*/  threads; } ;
struct TYPE_14__ {int /*<<< orphan*/  task_threads; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 TYPE_4__* current_thread () ; 
 int /*<<< orphan*/  get_task_pmap (TYPE_5__*) ; 
 TYPE_3__* get_user_regs (TYPE_4__*) ; 
 int /*<<< orphan*/  paniclog_append_noflush (char*,...) ; 
 int /*<<< orphan*/  print_one_backtrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ queue_first (int /*<<< orphan*/ *) ; 
 scalar_t__ queue_next (int /*<<< orphan*/ *) ; 

void
print_tasks_user_threads(task_t task)
{
	thread_t		thread = current_thread();
	x86_saved_state_t *savestate;
	pmap_t			pmap = 0;
	uint64_t		rbp;
	const char		*cur_marker = 0;
	int             j;
	
	for (j = 0, thread = (thread_t) queue_first(&task->threads); j < task->thread_count;
			++j, thread = (thread_t) queue_next(&thread->task_threads)) {

		paniclog_append_noflush("Thread %d: %p\n", j, thread);
		pmap = get_task_pmap(task);
		savestate = get_user_regs(thread);
		rbp = savestate->ss_64.rbp;
		paniclog_append_noflush("\t0x%016llx\n", savestate->ss_64.isf.rip);
		print_one_backtrace(pmap, (vm_offset_t)rbp, cur_marker, TRUE);
		paniclog_append_noflush("\n");
	}
}