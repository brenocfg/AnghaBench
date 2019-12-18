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
struct lwp_info {int step; int resumed; scalar_t__ stopped; scalar_t__ status; int /*<<< orphan*/  ptid; } ;
typedef  int /*<<< orphan*/  ptid_t ;
typedef  enum target_signal { ____Placeholder_target_signal } target_signal ;

/* Variables and functions */
 int /*<<< orphan*/  GET_LWP (int /*<<< orphan*/ ) ; 
 int PIDGET (int /*<<< orphan*/ ) ; 
 int TARGET_SIGNAL_0 ; 
 int /*<<< orphan*/  child_resume (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ debug_lin_lwp ; 
 struct lwp_info* find_lwp_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  iterate_over_lwps (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pid_to_ptid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resume_callback ; 
 int /*<<< orphan*/  resume_clear_callback ; 
 int /*<<< orphan*/  resume_set_callback ; 
 char* strsignal (int) ; 
 int /*<<< orphan*/  target_pid_to_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lin_lwp_resume (ptid_t ptid, int step, enum target_signal signo)
{
  struct lwp_info *lp;
  int resume_all;

  /* A specific PTID means `step only this process id'.  */
  resume_all = (PIDGET (ptid) == -1);

  if (resume_all)
    iterate_over_lwps (resume_set_callback, NULL);
  else
    iterate_over_lwps (resume_clear_callback, NULL);

  /* If PID is -1, it's the current inferior that should be
     handled specially.  */
  if (PIDGET (ptid) == -1)
    ptid = inferior_ptid;

  lp = find_lwp_pid (ptid);
  if (lp)
    {
      ptid = pid_to_ptid (GET_LWP (lp->ptid));

      /* Remember if we're stepping.  */
      lp->step = step;

      /* Mark this LWP as resumed.  */
      lp->resumed = 1;

      /* If we have a pending wait status for this thread, there is no
         point in resuming the process.  */
      if (lp->status)
	{
	  /* FIXME: What should we do if we are supposed to continue
	     this thread with a signal?  */
	  gdb_assert (signo == TARGET_SIGNAL_0);
	  return;
	}

      /* Mark LWP as not stopped to prevent it from being continued by
         resume_callback.  */
      lp->stopped = 0;
    }

  if (resume_all)
    iterate_over_lwps (resume_callback, NULL);

  child_resume (ptid, step, signo);
  if (debug_lin_lwp)
    fprintf_unfiltered (gdb_stdlog,
			"LLR: %s %s, %s (resume event thread)\n",
			step ? "PTRACE_SINGLESTEP" : "PTRACE_CONT",
			target_pid_to_str (ptid),
			signo ? strsignal (signo) : "0");
}