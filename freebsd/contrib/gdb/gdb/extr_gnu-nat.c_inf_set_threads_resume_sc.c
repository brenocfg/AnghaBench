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
struct proc {scalar_t__ pause_sc; scalar_t__ resume_sc; scalar_t__ run_sc; struct proc* next; } ;
struct inf {struct proc* threads; } ;

/* Variables and functions */
 int /*<<< orphan*/  inf_update_procs (struct inf*) ; 

void
inf_set_threads_resume_sc (struct inf *inf,
			   struct proc *run_thread, int run_others)
{
  struct proc *thread;
  inf_update_procs (inf);
  for (thread = inf->threads; thread; thread = thread->next)
    if (thread == run_thread)
      thread->resume_sc = 0;
    else if (run_others)
      thread->resume_sc = thread->run_sc;
    else
      thread->resume_sc = thread->pause_sc;
}