#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  regs; } ;
struct TYPE_7__ {int (* proc ) (void*) ;void* arg; } ;
struct TYPE_8__ {TYPE_1__ thread; } ;
struct TYPE_9__ {TYPE_2__ u; } ;
struct TYPE_11__ {TYPE_4__ regs; int /*<<< orphan*/  exec_buf; TYPE_3__ request; int /*<<< orphan*/ * prev_sched; } ;
struct TYPE_12__ {TYPE_5__ thread; } ;

/* Variables and functions */
 TYPE_6__* current ; 
 int /*<<< orphan*/  do_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  interrupt_end () ; 
 int run_kernel_thread (int (*) (void*),void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_tail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  userspace (int /*<<< orphan*/ *) ; 

void new_thread_handler(void)
{
	int (*fn)(void *), n;
	void *arg;

	if (current->thread.prev_sched != NULL)
		schedule_tail(current->thread.prev_sched);
	current->thread.prev_sched = NULL;

	fn = current->thread.request.u.thread.proc;
	arg = current->thread.request.u.thread.arg;

	/*
	 * The return value is 1 if the kernel thread execs a process,
	 * 0 if it just exits
	 */
	n = run_kernel_thread(fn, arg, &current->thread.exec_buf);
	if (n == 1) {
		/* Handle any immediate reschedules or signals */
		interrupt_end();
		userspace(&current->thread.regs.regs);
	}
	else do_exit(0);
}