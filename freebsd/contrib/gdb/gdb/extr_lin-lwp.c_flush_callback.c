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
struct lwp_info {int status; scalar_t__ stopped; int /*<<< orphan*/  ptid; int /*<<< orphan*/ * next; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  GET_LWP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTRACE_CONT ; 
 scalar_t__ WIFSTOPPED (int) ; 
 int /*<<< orphan*/  WSTOPSIG (int) ; 
 scalar_t__ debug_lin_lwp ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 scalar_t__ lin_lwp_has_pending (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lin_lwp_thread_alive (int /*<<< orphan*/ ) ; 
 struct lwp_info* lwp_list ; 
 int /*<<< orphan*/  printf_unfiltered (char*,int) ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sigismember (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_wait_callback (struct lwp_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
flush_callback (struct lwp_info *lp, void *data)
{
  sigset_t *flush_mask = data;
  sigset_t pending, intersection, blocked, ignored;
  int pid, status;

  /* Normally, when an LWP exits, it is removed from the LWP list.  The
     last LWP isn't removed till later, however.  So if there is only
     one LWP on the list, make sure it's alive.  */
  if (lwp_list == lp && lp->next == NULL)
    if (!lin_lwp_thread_alive (lp->ptid))
      return 0;

  /* Just because the LWP is stopped doesn't mean that new signals
     can't arrive from outside, so this function must be careful of
     race conditions.  However, because all threads are stopped, we
     can assume that the pending mask will not shrink unless we resume
     the LWP, and that it will then get another signal.  We can't
     control which one, however.  */

  if (lp->status)
    {
      if (debug_lin_lwp)
	printf_unfiltered ("FC: LP has pending status %06x\n", lp->status);
      if (WIFSTOPPED (lp->status) && sigismember (flush_mask, WSTOPSIG (lp->status)))
	lp->status = 0;
    }

  while (lin_lwp_has_pending (GET_LWP (lp->ptid), &pending, flush_mask))
    {
      int ret;
      
      errno = 0;
      ret = ptrace (PTRACE_CONT, GET_LWP (lp->ptid), 0, 0);
      if (debug_lin_lwp)
	fprintf_unfiltered (gdb_stderr,
			    "FC: Sent PTRACE_CONT, ret %d %d\n", ret, errno);

      lp->stopped = 0;
      stop_wait_callback (lp, flush_mask);
      if (debug_lin_lwp)
	fprintf_unfiltered (gdb_stderr,
			    "FC: Wait finished; saved status is %d\n",
			    lp->status);
    }

  return 0;
}