#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thread_t ;
typedef  TYPE_1__* proc_t ;
struct TYPE_5__ {int /*<<< orphan*/  task; int /*<<< orphan*/  exit_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  proc_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  task_hold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
sig_lock_to_exit(proc_t p)
{
	thread_t	self = current_thread();

	p->exit_thread = self;
	proc_unlock(p);

	task_hold(p->task);
	task_wait(p->task, FALSE);

	proc_lock(p);
}