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
struct proc {scalar_t__ sc; scalar_t__ cur_sc; struct proc* next; } ;
struct inf {int running; scalar_t__ threads_up_to_date; struct proc* threads; scalar_t__ pending_execs; struct proc* task; } ;

/* Variables and functions */
 int /*<<< orphan*/  inf_debug (struct inf*,char*,...) ; 
 int proc_update_sc (struct proc*) ; 

int
inf_update_suspends (struct inf *inf)
{
  struct proc *task = inf->task;
  /* We don't have to update INF->threads even though we're iterating over it
     because we'll change a thread only if it already has an existing proc
     entry.  */

  inf_debug (inf, "updating suspend counts");

  if (task)
    {
      struct proc *thread;
      int task_running = (task->sc == 0), thread_running = 0;

      if (task->sc > task->cur_sc)
	/* The task is becoming _more_ suspended; do before any threads.  */
	task_running = proc_update_sc (task);

      if (inf->pending_execs)
	/* When we're waiting for an exec, things may be happening behind our
	   back, so be conservative.  */
	thread_running = 1;

      /* Do all the thread suspend counts.  */
      for (thread = inf->threads; thread; thread = thread->next)
	thread_running |= proc_update_sc (thread);

      if (task->sc != task->cur_sc)
	/* We didn't do the task first, because we wanted to wait for the
	   threads; do it now.  */
	task_running = proc_update_sc (task);

      inf_debug (inf, "%srunning...",
		 (thread_running && task_running) ? "" : "not ");

      inf->running = thread_running && task_running;

      /* Once any thread has executed some code, we can't depend on the
         threads list any more.  */
      if (inf->running)
	inf->threads_up_to_date = 0;

      return inf->running;
    }

  return 0;
}