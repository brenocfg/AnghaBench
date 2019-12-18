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
struct lwp_info {int /*<<< orphan*/  ptid; scalar_t__ cloned; } ;
typedef  int pid_t ;

/* Variables and functions */
 scalar_t__ ECHILD ; 
 int GET_LWP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __WCLONE ; 
 scalar_t__ debug_lin_lwp ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int /*<<< orphan*/  target_pid_to_str (int /*<<< orphan*/ ) ; 
 int waitpid (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kill_wait_callback (struct lwp_info *lp, void *data)
{
  pid_t pid;

  /* We must make sure that there are no pending events (delayed
     SIGSTOPs, pending SIGTRAPs, etc.) to make sure the current
     program doesn't interfere with any following debugging session.  */

  /* For cloned processes we must check both with __WCLONE and
     without, since the exit status of a cloned process isn't reported
     with __WCLONE.  */
  if (lp->cloned)
    {
      do
	{
	  pid = waitpid (GET_LWP (lp->ptid), NULL, __WCLONE);
	  if (pid != (pid_t) -1 && debug_lin_lwp)
	    {
	      fprintf_unfiltered (gdb_stdlog,
				  "KWC: wait %s received unknown.\n",
				  target_pid_to_str (lp->ptid));
	    }
	}
      while (pid == GET_LWP (lp->ptid));

      gdb_assert (pid == -1 && errno == ECHILD);
    }

  do
    {
      pid = waitpid (GET_LWP (lp->ptid), NULL, 0);
      if (pid != (pid_t) -1 && debug_lin_lwp)
	{
	  fprintf_unfiltered (gdb_stdlog,
			      "KWC: wait %s received unk.\n",
			      target_pid_to_str (lp->ptid));
	}
    }
  while (pid == GET_LWP (lp->ptid));

  gdb_assert (pid == -1 && errno == ECHILD);
  return 0;
}