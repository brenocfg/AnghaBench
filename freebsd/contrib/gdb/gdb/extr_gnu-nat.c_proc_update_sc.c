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
typedef  int /*<<< orphan*/  thread_state_t ;
struct proc {int sc; int cur_sc; scalar_t__ fetched_regs; scalar_t__ state_changed; scalar_t__ state_valid; scalar_t__ aborted; int /*<<< orphan*/  port; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  THREAD_STATE_FLAVOR ; 
 int /*<<< orphan*/  THREAD_STATE_SIZE ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_debug (struct proc*,char*,...) ; 
 scalar_t__ proc_is_task (struct proc*) ; 
 int /*<<< orphan*/  proc_is_thread (struct proc*) ; 
 char* safe_strerror (int) ; 
 int task_resume (int /*<<< orphan*/ ) ; 
 int task_suspend (int /*<<< orphan*/ ) ; 
 int thread_resume (int /*<<< orphan*/ ) ; 
 int thread_set_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int thread_suspend (int /*<<< orphan*/ ) ; 

int
proc_update_sc (struct proc *proc)
{
  int running;
  int err = 0;
  int delta = proc->sc - proc->cur_sc;

  if (delta)
    proc_debug (proc, "sc: %d --> %d", proc->cur_sc, proc->sc);

  if (proc->sc == 0 && proc->state_changed)
    /* Since PROC may start running, we must write back any state changes. */
    {
      gdb_assert (proc_is_thread (proc));
      proc_debug (proc, "storing back changed thread state");
      err = thread_set_state (proc->port, THREAD_STATE_FLAVOR,
			 (thread_state_t) &proc->state, THREAD_STATE_SIZE);
      if (!err)
	proc->state_changed = 0;
    }

  if (delta > 0)
    {
      while (delta-- > 0 && !err)
	{
	  if (proc_is_task (proc))
	    err = task_suspend (proc->port);
	  else
	    err = thread_suspend (proc->port);
	}
    }
  else
    {
      while (delta++ < 0 && !err)
	{
	  if (proc_is_task (proc))
	    err = task_resume (proc->port);
	  else
	    err = thread_resume (proc->port);
	}
    }
  if (!err)
    proc->cur_sc = proc->sc;

  /* If we got an error, then the task/thread has disappeared.  */
  running = !err && proc->sc == 0;

  proc_debug (proc, "is %s", err ? "dead" : running ? "running" : "suspended");
  if (err)
    proc_debug (proc, "err = %s", safe_strerror (err));

  if (running)
    {
      proc->aborted = 0;
      proc->state_valid = proc->state_changed = 0;
      proc->fetched_regs = 0;
    }

  return running;
}