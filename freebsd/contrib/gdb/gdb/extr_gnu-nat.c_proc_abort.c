#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct proc {int aborted; scalar_t__ cur_sc; int sc; int /*<<< orphan*/  port; struct inf* inf; } ;
struct TYPE_5__ {scalar_t__ reply; } ;
struct TYPE_6__ {TYPE_2__ exc; struct proc* thread; } ;
struct inf {TYPE_3__ wait; TYPE_1__* task; } ;
struct TYPE_4__ {scalar_t__ cur_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inf_update_suspends (struct inf*) ; 
 int /*<<< orphan*/  proc_debug (struct proc*,char*) ; 
 int /*<<< orphan*/  proc_is_thread (struct proc*) ; 
 int /*<<< orphan*/  proc_string (struct proc*) ; 
 int /*<<< orphan*/  thread_abort (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 

void
proc_abort (struct proc *proc, int force)
{
  gdb_assert (proc_is_thread (proc));

  if (!proc->aborted)
    {
      struct inf *inf = proc->inf;
      int running = (proc->cur_sc == 0 && inf->task->cur_sc == 0);

      if (running && force)
	{
	  proc->sc = 1;
	  inf_update_suspends (proc->inf);
	  running = 0;
	  warning ("Stopped %s.", proc_string (proc));
	}
      else if (proc == inf->wait.thread && inf->wait.exc.reply && !force)
	/* An exception is pending on PROC, which don't mess with.  */
	running = 1;

      if (!running)
	/* We only abort the thread if it's not actually running.  */
	{
	  thread_abort (proc->port);
	  proc_debug (proc, "aborted");
	  proc->aborted = 1;
	}
      else
	proc_debug (proc, "not aborting");
    }
}