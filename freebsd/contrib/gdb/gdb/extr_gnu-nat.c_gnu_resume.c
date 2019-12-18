#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct proc {int /*<<< orphan*/  tid; } ;
struct TYPE_6__ {int /*<<< orphan*/  sig; } ;
struct TYPE_7__ {TYPE_2__ value; } ;
struct TYPE_5__ {scalar_t__ reply; } ;
struct TYPE_8__ {TYPE_3__ status; int /*<<< orphan*/  thread; TYPE_1__ exc; } ;
struct inf {struct proc* step_thread; int /*<<< orphan*/  pid; int /*<<< orphan*/  event_port; TYPE_4__ wait; scalar_t__ nomsg; scalar_t__ stopped; } ;
typedef  int /*<<< orphan*/  ptid_t ;
typedef  enum target_signal { ____Placeholder_target_signal } target_signal ;

/* Variables and functions */
 scalar_t__ MACH_PORT_NULL ; 
 scalar_t__ PIDGET (int /*<<< orphan*/ ) ; 
 int TARGET_SIGNAL_0 ; 
 struct inf* current_inferior ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  inf_continue (struct inf*) ; 
 int /*<<< orphan*/  inf_debug (struct inf*,char*,...) ; 
 int /*<<< orphan*/  inf_resume (struct inf*) ; 
 int /*<<< orphan*/  inf_set_step_thread (struct inf*,struct proc*) ; 
 int /*<<< orphan*/  inf_set_threads_resume_sc (struct inf*,struct proc*,int) ; 
 int /*<<< orphan*/  inf_signal (struct inf*,int) ; 
 struct proc* inf_tid_to_thread (struct inf*,scalar_t__) ; 
 int /*<<< orphan*/  inf_update_procs (struct inf*) ; 
 int /*<<< orphan*/  inf_validate_procinfo (struct inf*) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 scalar_t__ port_msgs_queued (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_abort (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  proc_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_signal_to_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (char*,scalar_t__,...) ; 

__attribute__((used)) static void
gnu_resume (ptid_t tid, int step, enum target_signal sig)
{
  struct proc *step_thread = 0;
  struct inf *inf = current_inferior;

  inf_debug (inf, "tid = %d, step = %d, sig = %d", PIDGET (tid), step, sig);

  inf_validate_procinfo (inf);

  if (sig != TARGET_SIGNAL_0 || inf->stopped)
    {
      if (sig == TARGET_SIGNAL_0 && inf->nomsg)
	inf_continue (inf);
      else
	inf_signal (inf, sig);
    }
  else if (inf->wait.exc.reply != MACH_PORT_NULL)
    /* We received an exception to which we have chosen not to forward, so
       abort the faulting thread, which will perhaps retake it.  */
    {
      proc_abort (inf->wait.thread, 1);
      warning ("Aborting %s with unforwarded exception %s.",
	       proc_string (inf->wait.thread),
	       target_signal_to_name (inf->wait.status.value.sig));
    }

  if (port_msgs_queued (inf->event_port))
    /* If there are still messages in our event queue, don't bother resuming
       the process, as we're just going to stop it right away anyway. */
    return;

  inf_update_procs (inf);

  if (PIDGET (tid) < 0)
    /* Allow all threads to run, except perhaps single-stepping one.  */
    {
      inf_debug (inf, "running all threads; tid = %d", PIDGET (inferior_ptid));
      tid = inferior_ptid;	/* What to step. */
      inf_set_threads_resume_sc (inf, 0, 1);
    }
  else
    /* Just allow a single thread to run.  */
    {
      struct proc *thread = inf_tid_to_thread (inf, PIDGET (tid));
      if (!thread)
	error ("Can't run single thread id %d: no such thread!");
      inf_debug (inf, "running one thread: %d/%d", inf->pid, thread->tid);
      inf_set_threads_resume_sc (inf, thread, 0);
    }

  if (step)
    {
      step_thread = inf_tid_to_thread (inf, PIDGET (tid));
      if (!step_thread)
	warning ("Can't step thread id %d: no such thread.", PIDGET (tid));
      else
	inf_debug (inf, "stepping thread: %d/%d", inf->pid, step_thread->tid);
    }
  if (step_thread != inf->step_thread)
    inf_set_step_thread (inf, step_thread);

  inf_debug (inf, "here we go...");
  inf_resume (inf);
}