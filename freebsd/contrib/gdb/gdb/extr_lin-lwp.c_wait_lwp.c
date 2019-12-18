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
struct lwp_info {int /*<<< orphan*/  ptid; int /*<<< orphan*/  status; int /*<<< orphan*/  stopped; } ;
typedef  int pid_t ;

/* Variables and functions */
 scalar_t__ ECHILD ; 
 int GET_LWP (int /*<<< orphan*/ ) ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 int WIFSTOPPED (int) ; 
 int /*<<< orphan*/  __WCLONE ; 
 scalar_t__ debug_lin_lwp ; 
 int /*<<< orphan*/  delete_lwp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_thread (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 scalar_t__ in_thread_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  printf_unfiltered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptid_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  status_to_str (int) ; 
 int /*<<< orphan*/  target_pid_to_str (int /*<<< orphan*/ ) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
wait_lwp (struct lwp_info *lp)
{
  pid_t pid;
  int status;
  int thread_dead = 0;

  gdb_assert (!lp->stopped);
  gdb_assert (lp->status == 0);

  pid = waitpid (GET_LWP (lp->ptid), &status, 0);
  if (pid == -1 && errno == ECHILD)
    {
      pid = waitpid (GET_LWP (lp->ptid), &status, __WCLONE);
      if (pid == -1 && errno == ECHILD)
	{
	  /* The thread has previously exited.  We need to delete it now
	     because in the case of NPTL threads, there won't be an
	     exit event unless it is the main thread.  */
	  thread_dead = 1;
	  if (debug_lin_lwp)
	    fprintf_unfiltered (gdb_stdlog, "WL: %s vanished.\n",
				target_pid_to_str (lp->ptid));
	}
    }

  if (!thread_dead)
    {
      gdb_assert (pid == GET_LWP (lp->ptid));

      if (debug_lin_lwp)
	{
	  fprintf_unfiltered (gdb_stdlog,
			      "WL: waitpid %s received %s\n",
			      target_pid_to_str (lp->ptid),
			      status_to_str (status));
	}
    }

  /* Check if the thread has exited.  */
  if (WIFEXITED (status) || WIFSIGNALED (status))
    {
      thread_dead = 1;
      if (debug_lin_lwp)
	fprintf_unfiltered (gdb_stdlog, "WL: %s exited.\n",
			    target_pid_to_str (lp->ptid));
    }

  if (thread_dead)
    {
      if (in_thread_list (lp->ptid))
	{
	  /* Core GDB cannot deal with us deleting the current thread.  */
	  if (!ptid_equal (lp->ptid, inferior_ptid))
	    delete_thread (lp->ptid);
	  printf_unfiltered ("[%s exited]\n",
			     target_pid_to_str (lp->ptid));
	}

      delete_lwp (lp->ptid);
      return 0;
    }

  gdb_assert (WIFSTOPPED (status));

  return status;
}