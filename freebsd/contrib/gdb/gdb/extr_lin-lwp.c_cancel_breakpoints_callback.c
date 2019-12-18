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
struct lwp_info {scalar_t__ status; int /*<<< orphan*/  ptid; } ;

/* Variables and functions */
 scalar_t__ DECR_PC_AFTER_BREAK ; 
 scalar_t__ SIGTRAP ; 
 scalar_t__ WIFSTOPPED (scalar_t__) ; 
 scalar_t__ WSTOPSIG (scalar_t__) ; 
 scalar_t__ breakpoint_inserted_here_p (scalar_t__) ; 
 scalar_t__ debug_lin_lwp ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 scalar_t__ read_pc_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_pid_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_pc_pid (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cancel_breakpoints_callback (struct lwp_info *lp, void *data)
{
  struct lwp_info *event_lp = data;

  /* Leave the LWP that has been elected to receive a SIGTRAP alone.  */
  if (lp == event_lp)
    return 0;

  /* If a LWP other than the LWP that we're reporting an event for has
     hit a GDB breakpoint (as opposed to some random trap signal),
     then just arrange for it to hit it again later.  We don't keep
     the SIGTRAP status and don't forward the SIGTRAP signal to the
     LWP.  We will handle the current event, eventually we will resume
     all LWPs, and this one will get its breakpoint trap again.

     If we do not do this, then we run the risk that the user will
     delete or disable the breakpoint, but the LWP will have already
     tripped on it.  */

  if (lp->status != 0
      && WIFSTOPPED (lp->status) && WSTOPSIG (lp->status) == SIGTRAP
      && breakpoint_inserted_here_p (read_pc_pid (lp->ptid) -
				     DECR_PC_AFTER_BREAK))
    {
      if (debug_lin_lwp)
	fprintf_unfiltered (gdb_stdlog,
			    "CBC: Push back breakpoint for %s\n",
			    target_pid_to_str (lp->ptid));

      /* Back up the PC if necessary.  */
      if (DECR_PC_AFTER_BREAK)
	write_pc_pid (read_pc_pid (lp->ptid) - DECR_PC_AFTER_BREAK, lp->ptid);

      /* Throw away the SIGTRAP.  */
      lp->status = 0;
    }

  return 0;
}