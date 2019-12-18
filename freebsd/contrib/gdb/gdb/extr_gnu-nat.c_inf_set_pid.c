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
typedef  scalar_t__ task_t ;
struct proc {scalar_t__ port; int sc; int cur_sc; } ;
struct inf {int pid; struct proc* task; scalar_t__ pause_sc; scalar_t__ threads_up_to_date; } ;
typedef  scalar_t__ pid_t ;
typedef  scalar_t__ error_t ;

/* Variables and functions */
 scalar_t__ MACH_PORT_NULL ; 
 int /*<<< orphan*/  PROC_TID_TASK ; 
 int /*<<< orphan*/  _proc_free (struct proc*) ; 
 int /*<<< orphan*/  error (char*,scalar_t__,char*) ; 
 int /*<<< orphan*/  inf_debug (struct inf*,char*,scalar_t__) ; 
 int /*<<< orphan*/  inf_validate_procs (struct inf*) ; 
 struct proc* make_proc (struct inf*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ proc_pid2task (int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  proc_server ; 
 char* safe_strerror (scalar_t__) ; 
 int /*<<< orphan*/  task_suspend (scalar_t__) ; 

void
inf_set_pid (struct inf *inf, pid_t pid)
{
  task_t task_port;
  struct proc *task = inf->task;

  inf_debug (inf, "setting pid: %d", pid);

  if (pid < 0)
    task_port = MACH_PORT_NULL;
  else
    {
      error_t err = proc_pid2task (proc_server, pid, &task_port);
      if (err)
	error ("Error getting task for pid %d: %s", pid, safe_strerror (err));
    }

  inf_debug (inf, "setting task: %d", task_port);

  if (inf->pause_sc)
    task_suspend (task_port);

  if (task && task->port != task_port)
    {
      inf->task = 0;
      inf_validate_procs (inf);	/* Trash all the threads. */
      _proc_free (task);	/* And the task. */
    }

  if (task_port != MACH_PORT_NULL)
    {
      inf->task = make_proc (inf, task_port, PROC_TID_TASK);
      inf->threads_up_to_date = 0;
    }

  if (inf->task)
    {
      inf->pid = pid;
      if (inf->pause_sc)
	/* Reflect task_suspend above.  */
	inf->task->sc = inf->task->cur_sc = 1;
    }
  else
    inf->pid = -1;
}