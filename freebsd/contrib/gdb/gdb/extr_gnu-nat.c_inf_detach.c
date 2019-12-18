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
struct proc {int /*<<< orphan*/  detach_sc; int /*<<< orphan*/  sc; struct proc* next; } ;
struct inf {struct proc* threads; int /*<<< orphan*/  detach_sc; scalar_t__ nomsg; scalar_t__ stopped; struct proc* task; } ;

/* Variables and functions */
 int /*<<< orphan*/  TARGET_SIGNAL_0 ; 
 int /*<<< orphan*/  inf_cleanup (struct inf*) ; 
 int /*<<< orphan*/  inf_clear_wait (struct inf*) ; 
 int /*<<< orphan*/  inf_continue (struct inf*) ; 
 int /*<<< orphan*/  inf_debug (struct inf*,char*) ; 
 int /*<<< orphan*/  inf_set_step_thread (struct inf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inf_set_traced (struct inf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inf_signal (struct inf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inf_update_suspends (struct inf*) ; 
 int /*<<< orphan*/  inf_validate_procinfo (struct inf*) ; 
 int /*<<< orphan*/  proc_restore_exc_port (struct proc*) ; 

void
inf_detach (struct inf *inf)
{
  struct proc *task = inf->task;

  inf_debug (inf, "detaching...");

  inf_clear_wait (inf);
  inf_set_step_thread (inf, 0);

  if (task)
    {
      struct proc *thread;

      inf_validate_procinfo (inf);

      inf_set_traced (inf, 0);
      if (inf->stopped)
	{
	  if (inf->nomsg)
	    inf_continue (inf);
	  else
	    inf_signal (inf, TARGET_SIGNAL_0);
	}

      proc_restore_exc_port (task);
      task->sc = inf->detach_sc;

      for (thread = inf->threads; thread; thread = thread->next)
	{
	  proc_restore_exc_port (thread);
	  thread->sc = thread->detach_sc;
	}

      inf_update_suspends (inf);
    }

  inf_cleanup (inf);
}