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
struct TYPE_2__ {int /*<<< orphan*/  sig; } ;
struct target_waitstatus {int /*<<< orphan*/  kind; TYPE_1__ value; } ;
typedef  int /*<<< orphan*/  ptid_t ;
typedef  enum target_waitkind { ____Placeholder_target_waitkind } target_waitkind ;

/* Variables and functions */
 int EINTR ; 
 int PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TARGET_SIGNAL_UNKNOWN ; 
 int /*<<< orphan*/  TARGET_WAITKIND_SIGNALLED ; 
 int /*<<< orphan*/  TARGET_WAITKIND_SPURIOUS ; 
 int /*<<< orphan*/  clear_sigint_trap () ; 
 int /*<<< orphan*/  clear_sigio_trap () ; 
 int errno ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  pid_to_ptid (int) ; 
 int ptrace_wait (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  safe_strerror (int) ; 
 int /*<<< orphan*/  set_sigint_trap () ; 
 int /*<<< orphan*/  set_sigio_trap () ; 
 int /*<<< orphan*/  store_waitstatus (struct target_waitstatus*,int) ; 
 scalar_t__ target_has_exited (int,int,int*) ; 
 int /*<<< orphan*/  target_thread_alive (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ptid_t
child_wait (ptid_t ptid, struct target_waitstatus *ourstatus)
{
  int save_errno;
  int status;
  char *execd_pathname = NULL;
  int exit_status;
  int related_pid;
  int syscall_id;
  enum target_waitkind kind;
  int pid;

  do
    {
      set_sigint_trap ();	/* Causes SIGINT to be passed on to the
				   attached process. */
      set_sigio_trap ();

      pid = ptrace_wait (inferior_ptid, &status);

      save_errno = errno;

      clear_sigio_trap ();

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
	  return pid_to_ptid (-1);
	}

      /* Did it exit?
       */
      if (target_has_exited (pid, status, &exit_status))
	{
	  /* ??rehrauer: For now, ignore this. */
	  continue;
	}

      if (!target_thread_alive (pid_to_ptid (pid)))
	{
	  ourstatus->kind = TARGET_WAITKIND_SPURIOUS;
	  return pid_to_ptid (pid);
	}
      } while (pid != PIDGET (inferior_ptid)); /* Some other child died or stopped */

  store_waitstatus (ourstatus, status);
  return pid_to_ptid (pid);
}