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
struct proc {struct proc* next; } ;
struct inf {struct proc* threads; struct proc* task; } ;

/* Variables and functions */
 int /*<<< orphan*/  inf_debug (struct inf*,char*) ; 
 int /*<<< orphan*/  inf_set_step_thread (struct inf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_restore_exc_port (struct proc*) ; 

void
inf_restore_exc_ports (struct inf *inf)
{
  struct proc *thread;

  inf_debug (inf, "restoring exception ports");

  inf_set_step_thread (inf, 0);	/* The step thread is special. */

  proc_restore_exc_port (inf->task);
  for (thread = inf->threads; thread; thread = thread->next)
    proc_restore_exc_port (thread);
}