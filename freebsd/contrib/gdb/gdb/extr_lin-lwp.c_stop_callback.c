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
struct lwp_info {int signalled; scalar_t__ status; int /*<<< orphan*/  ptid; int /*<<< orphan*/  stopped; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_LWP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGSTOP ; 
 scalar_t__ debug_lin_lwp ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int kill_lwp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* safe_strerror (scalar_t__) ; 
 int /*<<< orphan*/  target_pid_to_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
stop_callback (struct lwp_info *lp, void *data)
{
  if (!lp->stopped && !lp->signalled)
    {
      int ret;

      if (debug_lin_lwp)
	{
	  fprintf_unfiltered (gdb_stdlog,
			      "SC:  kill %s **<SIGSTOP>**\n",
			      target_pid_to_str (lp->ptid));
	}
      errno = 0;
      ret = kill_lwp (GET_LWP (lp->ptid), SIGSTOP);
      if (debug_lin_lwp)
	{
	  fprintf_unfiltered (gdb_stdlog,
			      "SC:  lwp kill %d %s\n",
			      ret,
			      errno ? safe_strerror (errno) : "ERRNO-OK");
	}

      lp->signalled = 1;
      gdb_assert (lp->status == 0);
    }

  return 0;
}