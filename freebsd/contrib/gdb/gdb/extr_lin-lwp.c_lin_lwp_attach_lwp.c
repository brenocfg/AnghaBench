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
struct lwp_info {int cloned; int stopped; } ;
typedef  int /*<<< orphan*/  ptid_t ;
typedef  int pid_t ;

/* Variables and functions */
 scalar_t__ ECHILD ; 
 int GET_LWP (int /*<<< orphan*/ ) ; 
 int GET_PID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTRACE_ATTACH ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 scalar_t__ WIFSTOPPED (int) ; 
 scalar_t__ WSTOPSIG (int) ; 
 int /*<<< orphan*/  __WCLONE ; 
 struct lwp_info* add_lwp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blocked_mask ; 
 int /*<<< orphan*/  child_post_attach (int) ; 
 scalar_t__ debug_lin_lwp ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*) ; 
 struct lwp_info* find_lwp_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int is_lwp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_filtered (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ptrace (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* safe_strerror (scalar_t__) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigismember (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  status_to_str (int) ; 
 int /*<<< orphan*/  target_pid_to_str (int /*<<< orphan*/ ) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

void
lin_lwp_attach_lwp (ptid_t ptid, int verbose)
{
  struct lwp_info *lp;

  gdb_assert (is_lwp (ptid));

  /* Make sure SIGCHLD is blocked.  We don't want SIGCHLD events
     to interrupt either the ptrace() or waitpid() calls below.  */
  if (!sigismember (&blocked_mask, SIGCHLD))
    {
      sigaddset (&blocked_mask, SIGCHLD);
      sigprocmask (SIG_BLOCK, &blocked_mask, NULL);
    }

  if (verbose)
    printf_filtered ("[New %s]\n", target_pid_to_str (ptid));

  lp = find_lwp_pid (ptid);
  if (lp == NULL)
    lp = add_lwp (ptid);

  /* We assume that we're already attached to any LWP that has an
     id equal to the overall process id.  */
  if (GET_LWP (ptid) != GET_PID (ptid))
    {
      pid_t pid;
      int status;

      if (ptrace (PTRACE_ATTACH, GET_LWP (ptid), 0, 0) < 0)
	error ("Can't attach %s: %s", target_pid_to_str (ptid),
	       safe_strerror (errno));

      if (debug_lin_lwp)
	fprintf_unfiltered (gdb_stdlog,
			    "LLAL: PTRACE_ATTACH %s, 0, 0 (OK)\n",
			    target_pid_to_str (ptid));

      pid = waitpid (GET_LWP (ptid), &status, 0);
      if (pid == -1 && errno == ECHILD)
	{
	  /* Try again with __WCLONE to check cloned processes.  */
	  pid = waitpid (GET_LWP (ptid), &status, __WCLONE);
	  lp->cloned = 1;
	}

      gdb_assert (pid == GET_LWP (ptid)
		  && WIFSTOPPED (status) && WSTOPSIG (status));

      child_post_attach (pid);

      lp->stopped = 1;

      if (debug_lin_lwp)
	{
	  fprintf_unfiltered (gdb_stdlog,
			      "LLAL: waitpid %s received %s\n",
			      target_pid_to_str (ptid),
			      status_to_str (status));
	}
    }
  else
    {
      /* We assume that the LWP representing the original process
         is already stopped.  Mark it as stopped in the data structure
         that the lin-lwp layer uses to keep track of threads.  Note
         that this won't have already been done since the main thread
         will have, we assume, been stopped by an attach from a
         different layer.  */
      lp->stopped = 1;
    }
}