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
typedef  int /*<<< orphan*/  task_t ;
typedef  TYPE_1__* proc_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_5__ {int p_lflag; scalar_t__ sigwait; int /*<<< orphan*/  p_stat; int /*<<< orphan*/  task; } ;

/* Variables and functions */
 int P_LSIGEXC ; 
 int P_LTRACED ; 
 int /*<<< orphan*/  SRUN ; 
 int /*<<< orphan*/  proc_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  task_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

void
pt_setrunnable(proc_t p)
{
	task_t task;

	task = p->task;

	if (p->p_lflag & P_LTRACED) {
		proc_lock(p);
		p->p_stat = SRUN;
		proc_unlock(p);
		if (p->sigwait) {
			wakeup((caddr_t)&(p->sigwait));
			if ((p->p_lflag & P_LSIGEXC) == 0) {	// 5878479
				task_release(task);
			}
		}
	}
}