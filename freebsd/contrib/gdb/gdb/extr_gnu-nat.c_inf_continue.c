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
struct proc {int /*<<< orphan*/  port; struct proc* next; } ;
struct inf {scalar_t__ stopped; struct proc* threads; int /*<<< orphan*/  pid; } ;
typedef  int /*<<< orphan*/  process_t ;
typedef  scalar_t__ error_t ;

/* Variables and functions */
 int /*<<< orphan*/  inf_debug (struct inf*,char*) ; 
 scalar_t__ proc_mark_cont (int /*<<< orphan*/ ) ; 
 scalar_t__ proc_pid2proc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_server ; 
 int /*<<< orphan*/  safe_strerror (scalar_t__) ; 
 int /*<<< orphan*/  thread_resume (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 

void
inf_continue (struct inf *inf)
{
  process_t proc;
  error_t err = proc_pid2proc (proc_server, inf->pid, &proc);

  if (!err)
    {
      inf_debug (inf, "continuing process");

      err = proc_mark_cont (proc);
      if (!err)
	{
	  struct proc *thread;

	  for (thread = inf->threads; thread; thread = thread->next)
	    thread_resume (thread->port);

	  inf->stopped = 0;
	}
    }

  if (err)
    warning ("Can't continue process: %s", safe_strerror (err));
}