#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
union wait {int w_tid; int /*<<< orphan*/  w_status; } ;
struct TYPE_2__ {void* sig; int /*<<< orphan*/  integer; } ;
struct target_waitstatus {TYPE_1__ value; void* kind; } ;
typedef  int ptid_t ;
typedef  int /*<<< orphan*/  PTRACE_ARG3_TYPE ;

/* Variables and functions */
 int BUILDPID (int,int) ; 
 int EINTR ; 
 int MERGEPID (int,int) ; 
 int PIDGET (int) ; 
 int /*<<< orphan*/  PTRACE_CONT ; 
 int /*<<< orphan*/  PTRACE_GETTRACESIG ; 
 int SIGNEWTHREAD ; 
 int SIGTHREADEXIT ; 
 scalar_t__ SIGTRAP ; 
 void* TARGET_SIGNAL_0 ; 
 void* TARGET_SIGNAL_UNKNOWN ; 
 void* TARGET_WAITKIND_EXITED ; 
 void* TARGET_WAITKIND_SIGNALLED ; 
 void* TARGET_WAITKIND_SPURIOUS ; 
 void* TARGET_WAITKIND_STOPPED ; 
 scalar_t__ TIDGET (int) ; 
 int /*<<< orphan*/  WEXITSTATUS (union wait) ; 
 scalar_t__ WIFEXITED (union wait) ; 
 scalar_t__ WIFSTOPPED (union wait) ; 
 scalar_t__ WSTOPSIG (union wait) ; 
 scalar_t__ WTERMSIG (union wait) ; 
 int /*<<< orphan*/  add_thread (int) ; 
 int /*<<< orphan*/  clear_sigint_trap () ; 
 int errno ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 scalar_t__ in_thread_list (int) ; 
 int inferior_ptid ; 
 int ptrace (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_strerror (int) ; 
 int /*<<< orphan*/  set_sigint_trap () ; 
 int /*<<< orphan*/  store_waitstatus (struct target_waitstatus*,int /*<<< orphan*/ ) ; 
 void* target_signal_from_host (scalar_t__) ; 
 int wait (union wait*) ; 

ptid_t
child_wait (ptid_t ptid, struct target_waitstatus *ourstatus)
{
  int save_errno;
  int thread;
  union wait status;
  int pid;

  while (1)
    {
      int sig;

      set_sigint_trap ();	/* Causes SIGINT to be passed on to the
				   attached process. */
      pid = wait (&status);

      save_errno = errno;

      clear_sigint_trap ();

      if (pid == -1)
	{
	  if (save_errno == EINTR)
	    continue;
	  fprintf_unfiltered (gdb_stderr, "Child process unexpectedly missing: %s.\n",
			      safe_strerror (save_errno));
	  /* Claim it exited with unknown signal.  */
	  ourstatus->kind = TARGET_WAITKIND_SIGNALLED;
	  ourstatus->value.sig = TARGET_SIGNAL_UNKNOWN;
	  return -1;
	}

      if (pid != PIDGET (inferior_ptid))	/* Some other process?!? */
	continue;

      thread = status.w_tid;	/* Get thread id from status */

      /* Initial thread value can only be acquired via wait, so we have to
         resort to this hack.  */

      if (TIDGET (inferior_ptid) == 0 && thread != 0)
	{
	  inferior_ptid = MERGEPID (PIDGET (inferior_ptid), thread);
	  add_thread (inferior_ptid);
	}

      ptid = BUILDPID (pid, thread);

      /* We've become a single threaded process again.  */
      if (thread == 0)
	inferior_ptid = ptid;

      /* Check for thread creation.  */
      if (WIFSTOPPED (status)
	  && WSTOPSIG (status) == SIGTRAP
	  && !in_thread_list (ptid))
	{
	  int realsig;

	  realsig = ptrace (PTRACE_GETTRACESIG, PIDGET (ptid),
	                    (PTRACE_ARG3_TYPE) 0, 0);

	  if (realsig == SIGNEWTHREAD)
	    {
	      /* It's a new thread notification.  We don't want to much with
	         realsig -- the code in wait_for_inferior expects SIGTRAP. */
	      ourstatus->kind = TARGET_WAITKIND_SPURIOUS;
	      ourstatus->value.sig = TARGET_SIGNAL_0;
	      return ptid;
	    }
	  else
	    error ("Signal for unknown thread was not SIGNEWTHREAD");
	}

      /* Check for thread termination.  */
      else if (WIFSTOPPED (status)
	       && WSTOPSIG (status) == SIGTRAP
	       && in_thread_list (ptid))
	{
	  int realsig;

	  realsig = ptrace (PTRACE_GETTRACESIG, PIDGET (ptid),
	                    (PTRACE_ARG3_TYPE) 0, 0);

	  if (realsig == SIGTHREADEXIT)
	    {
	      ptrace (PTRACE_CONT, PIDGET (ptid), (PTRACE_ARG3_TYPE) 0, 0);
	      continue;
	    }
	}

#ifdef SPARC
      /* SPARC Lynx uses an byte reversed wait status; we must use the
         host macros to access it.  These lines just a copy of
         store_waitstatus.  We can't use CHILD_SPECIAL_WAITSTATUS
         because target.c can't include the Lynx <sys/wait.h>.  */
      if (WIFEXITED (status))
	{
	  ourstatus->kind = TARGET_WAITKIND_EXITED;
	  ourstatus->value.integer = WEXITSTATUS (status);
	}
      else if (!WIFSTOPPED (status))
	{
	  ourstatus->kind = TARGET_WAITKIND_SIGNALLED;
	  ourstatus->value.sig =
	    target_signal_from_host (WTERMSIG (status));
	}
      else
	{
	  ourstatus->kind = TARGET_WAITKIND_STOPPED;
	  ourstatus->value.sig =
	    target_signal_from_host (WSTOPSIG (status));
	}
#else
      store_waitstatus (ourstatus, status.w_status);
#endif

      return ptid;
    }
}