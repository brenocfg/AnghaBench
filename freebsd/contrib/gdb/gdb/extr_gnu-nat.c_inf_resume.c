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
struct proc {int /*<<< orphan*/  resume_sc; int /*<<< orphan*/  sc; struct proc* next; } ;
struct inf {TYPE_1__* task; int /*<<< orphan*/  pending_execs; struct proc* threads; } ;
struct TYPE_2__ {scalar_t__ sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  inf_update_procs (struct inf*) ; 
 int /*<<< orphan*/  inf_update_suspends (struct inf*) ; 
 int /*<<< orphan*/  inf_validate_task_sc (struct inf*) ; 

void
inf_resume (struct inf *inf)
{
  struct proc *thread;

  inf_update_procs (inf);

  for (thread = inf->threads; thread; thread = thread->next)
    thread->sc = thread->resume_sc;

  if (inf->task)
    {
      if (!inf->pending_execs)
	/* Try to make sure our task count is correct -- in the case where
	   we're waiting for an exec though, things are too volatile, so just
	   assume things will be reasonable (which they usually will be).  */
	inf_validate_task_sc (inf);
      inf->task->sc = 0;
    }

  inf_update_suspends (inf);
}