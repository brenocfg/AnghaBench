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
struct lwp_info {int stopped; int status; scalar_t__ signalled; int /*<<< orphan*/  ptid; } ;
typedef  void sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  GET_LWP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTRACE_CONT ; 
 scalar_t__ SIGSTOP ; 
 scalar_t__ SIGTRAP ; 
 scalar_t__ WSTOPSIG (int) ; 
 scalar_t__ debug_lin_lwp ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int /*<<< orphan*/  kill_lwp (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* safe_strerror (scalar_t__) ; 
 scalar_t__ sigismember (void*,scalar_t__) ; 
 char* status_to_str (int) ; 
 char* target_pid_to_str (int /*<<< orphan*/ ) ; 
 int wait_lwp (struct lwp_info*) ; 

__attribute__((used)) static int
stop_wait_callback (struct lwp_info *lp, void *data)
{
  sigset_t *flush_mask = data;

  if (!lp->stopped)
    {
      int status;

      status = wait_lwp (lp);
      if (status == 0)
	return 0;

      /* Ignore any signals in FLUSH_MASK.  */
      if (flush_mask && sigismember (flush_mask, WSTOPSIG (status)))
	{
	  if (!lp->signalled)
	    {
	      lp->stopped = 1;
	      return 0;
	    }

	  errno = 0;
	  ptrace (PTRACE_CONT, GET_LWP (lp->ptid), 0, 0);
	  if (debug_lin_lwp)
	    fprintf_unfiltered (gdb_stdlog,
				"PTRACE_CONT %s, 0, 0 (%s)\n",
				target_pid_to_str (lp->ptid),
				errno ? safe_strerror (errno) : "OK");

	  return stop_wait_callback (lp, flush_mask);
	}

      if (WSTOPSIG (status) != SIGSTOP)
	{
	  if (WSTOPSIG (status) == SIGTRAP)
	    {
	      /* If a LWP other than the LWP that we're reporting an
	         event for has hit a GDB breakpoint (as opposed to
	         some random trap signal), then just arrange for it to
	         hit it again later.  We don't keep the SIGTRAP status
	         and don't forward the SIGTRAP signal to the LWP.  We
	         will handle the current event, eventually we will
	         resume all LWPs, and this one will get its breakpoint
	         trap again.

	         If we do not do this, then we run the risk that the
	         user will delete or disable the breakpoint, but the
	         thread will have already tripped on it.  */

	      /* Now resume this LWP and get the SIGSTOP event. */
	      errno = 0;
	      ptrace (PTRACE_CONT, GET_LWP (lp->ptid), 0, 0);
	      if (debug_lin_lwp)
		{
		  fprintf_unfiltered (gdb_stdlog,
				      "PTRACE_CONT %s, 0, 0 (%s)\n",
				      target_pid_to_str (lp->ptid),
				      errno ? safe_strerror (errno) : "OK");

		  fprintf_unfiltered (gdb_stdlog,
				      "SWC: Candidate SIGTRAP event in %s\n",
				      target_pid_to_str (lp->ptid));
		}
	      /* Hold the SIGTRAP for handling by lin_lwp_wait. */
	      stop_wait_callback (lp, data);
	      /* If there's another event, throw it back into the queue. */
	      if (lp->status)
		{
		  if (debug_lin_lwp)
		    {
		      fprintf_unfiltered (gdb_stdlog,
					  "SWC: kill %s, %s\n",
					  target_pid_to_str (lp->ptid),
					  status_to_str ((int) status));
		    }
		  kill_lwp (GET_LWP (lp->ptid), WSTOPSIG (lp->status));
		}
	      /* Save the sigtrap event. */
	      lp->status = status;
	      return 0;
	    }
	  else
	    {
	      /* The thread was stopped with a signal other than
	         SIGSTOP, and didn't accidentally trip a breakpoint. */

	      if (debug_lin_lwp)
		{
		  fprintf_unfiltered (gdb_stdlog,
				      "SWC: Pending event %s in %s\n",
				      status_to_str ((int) status),
				      target_pid_to_str (lp->ptid));
		}
	      /* Now resume this LWP and get the SIGSTOP event. */
	      errno = 0;
	      ptrace (PTRACE_CONT, GET_LWP (lp->ptid), 0, 0);
	      if (debug_lin_lwp)
		fprintf_unfiltered (gdb_stdlog,
				    "SWC: PTRACE_CONT %s, 0, 0 (%s)\n",
				    target_pid_to_str (lp->ptid),
				    errno ? safe_strerror (errno) : "OK");

	      /* Hold this event/waitstatus while we check to see if
	         there are any more (we still want to get that SIGSTOP). */
	      stop_wait_callback (lp, data);
	      /* If the lp->status field is still empty, use it to hold
	         this event.  If not, then this event must be returned
	         to the event queue of the LWP.  */
	      if (lp->status == 0)
		lp->status = status;
	      else
		{
		  if (debug_lin_lwp)
		    {
		      fprintf_unfiltered (gdb_stdlog,
					  "SWC: kill %s, %s\n",
					  target_pid_to_str (lp->ptid),
					  status_to_str ((int) status));
		    }
		  kill_lwp (GET_LWP (lp->ptid), WSTOPSIG (status));
		}
	      return 0;
	    }
	}
      else
	{
	  /* We caught the SIGSTOP that we intended to catch, so
	     there's no SIGSTOP pending.  */
	  lp->stopped = 1;
	  lp->signalled = 0;
	}
    }

  return 0;
}