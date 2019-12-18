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
struct lwp_info {scalar_t__ status; int /*<<< orphan*/  ptid; scalar_t__ signalled; scalar_t__ stopped; } ;

/* Variables and functions */
 scalar_t__ GET_LWP (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_PID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTRACE_CONT ; 
 int /*<<< orphan*/  PTRACE_DETACH ; 
 scalar_t__ WIFSTOPPED (scalar_t__) ; 
 int /*<<< orphan*/  WSTOPSIG (scalar_t__) ; 
 scalar_t__ debug_lin_lwp ; 
 int /*<<< orphan*/  delete_lwp (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 scalar_t__ ptrace (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* safe_strerror (scalar_t__) ; 
 int /*<<< orphan*/  status_to_str (scalar_t__) ; 
 int /*<<< orphan*/  strsignal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_pid_to_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
detach_callback (struct lwp_info *lp, void *data)
{
  gdb_assert (lp->status == 0 || WIFSTOPPED (lp->status));

  if (debug_lin_lwp && lp->status)
    fprintf_unfiltered (gdb_stdlog, "DC:  Pending %s for %s on detach.\n",
			strsignal (WSTOPSIG (lp->status)),
			target_pid_to_str (lp->ptid));

  while (lp->signalled && lp->stopped)
    {
      errno = 0;
      if (ptrace (PTRACE_CONT, GET_LWP (lp->ptid), 0,
		  WSTOPSIG (lp->status)) < 0)
	error ("Can't continue %s: %s", target_pid_to_str (lp->ptid),
	       safe_strerror (errno));

      if (debug_lin_lwp)
	fprintf_unfiltered (gdb_stdlog,
			    "DC:  PTRACE_CONTINUE (%s, 0, %s) (OK)\n",
			    target_pid_to_str (lp->ptid),
			    status_to_str (lp->status));

      lp->stopped = 0;
      lp->signalled = 0;
      lp->status = 0;
      /* FIXME drow/2003-08-26: There was a call to stop_wait_callback
	 here.  But since lp->signalled was cleared above,
	 stop_wait_callback didn't do anything; the process was left
	 running.  Shouldn't we be waiting for it to stop?
	 I've removed the call, since stop_wait_callback now does do
	 something when called with lp->signalled == 0.  */

      gdb_assert (lp->status == 0 || WIFSTOPPED (lp->status));
    }

  /* We don't actually detach from the LWP that has an id equal to the
     overall process id just yet.  */
  if (GET_LWP (lp->ptid) != GET_PID (lp->ptid))
    {
      errno = 0;
      if (ptrace (PTRACE_DETACH, GET_LWP (lp->ptid), 0,
		  WSTOPSIG (lp->status)) < 0)
	error ("Can't detach %s: %s", target_pid_to_str (lp->ptid),
	       safe_strerror (errno));

      if (debug_lin_lwp)
	fprintf_unfiltered (gdb_stdlog,
			    "PTRACE_DETACH (%s, %s, 0) (OK)\n",
			    target_pid_to_str (lp->ptid),
			    strsignal (WSTOPSIG (lp->status)));

      delete_lwp (lp->ptid);
    }

  return 0;
}