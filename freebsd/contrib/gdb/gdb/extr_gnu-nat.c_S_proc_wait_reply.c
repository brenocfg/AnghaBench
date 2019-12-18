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
struct TYPE_6__ {scalar_t__ kind; } ;
struct TYPE_5__ {int suppress; TYPE_3__ status; } ;
struct inf {scalar_t__ pid; int no_wait; int stopped; TYPE_2__ wait; TYPE_1__* task; } ;
typedef  int /*<<< orphan*/  rusage_t ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  mach_port_t ;
typedef  scalar_t__ error_t ;
struct TYPE_4__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ TARGET_WAITKIND_STOPPED ; 
 int /*<<< orphan*/  inf_debug (struct inf*,char*,...) ; 
 int /*<<< orphan*/  inf_set_traced (struct inf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inf_task_died_status (struct inf*) ; 
 scalar_t__ proc_wait_pid ; 
 scalar_t__ proc_waits_pending ; 
 char* safe_strerror (scalar_t__) ; 
 int /*<<< orphan*/  store_waitstatus (TYPE_3__*,int) ; 
 struct inf* waiting_inf ; 
 int /*<<< orphan*/  warning (char*,scalar_t__,char*) ; 

error_t
S_proc_wait_reply (mach_port_t reply, error_t err,
		   int status, int sigcode, rusage_t rusage, pid_t pid)
{
  struct inf *inf = waiting_inf;

  inf_debug (inf, "err = %s, pid = %d, status = 0x%x, sigcode = %d",
	     err ? safe_strerror (err) : "0", pid, status, sigcode);

  if (err && proc_wait_pid && (!inf->task || !inf->task->port))
    /* Ack.  The task has died, but the task-died notification code didn't
       tell anyone because it thought a more detailed reply from the
       procserver was forthcoming.  However, we now learn that won't
       happen...  So we have to act like the task just died, and this time,
       tell the world.  */
    inf_task_died_status (inf);

  if (--proc_waits_pending == 0)
    /* PROC_WAIT_PID represents the most recent wait.  We will always get
       replies in order because the proc server is single threaded.  */
    proc_wait_pid = 0;

  inf_debug (inf, "waits pending now: %d", proc_waits_pending);

  if (err)
    {
      if (err != EINTR)
	{
	  warning ("Can't wait for pid %d: %s", inf->pid, safe_strerror (err));
	  inf->no_wait = 1;

	  /* Since we can't see the inferior's signals, don't trap them.  */
	  inf_set_traced (inf, 0);
	}
    }
  else if (pid == inf->pid)
    {
      store_waitstatus (&inf->wait.status, status);
      if (inf->wait.status.kind == TARGET_WAITKIND_STOPPED)
	/* The process has sent us a signal, and stopped itself in a sane
	   state pending our actions.  */
	{
	  inf_debug (inf, "process has stopped itself");
	  inf->stopped = 1;
	}
    }
  else
    inf->wait.suppress = 1;	/* Something odd happened.  Ignore.  */

  return 0;
}