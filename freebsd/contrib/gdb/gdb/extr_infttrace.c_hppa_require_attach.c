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
typedef  scalar_t__ process_state_t ;
typedef  int /*<<< orphan*/  lwpid_t ;
typedef  int /*<<< orphan*/  TTRACE_ARG_TYPE ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  DONT_ATTACH_CONTINUE ; 
 scalar_t__ STOPPED ; 
 scalar_t__ TT_NIL ; 
 int /*<<< orphan*/  TT_PROC_STOP ; 
 scalar_t__ VFORKING ; 
 int attach (int) ; 
 int call_real_ttrace (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ errno ; 
 scalar_t__ process_state ; 
 int /*<<< orphan*/  update_thread_state_after_attach (int,int /*<<< orphan*/ ) ; 

int
hppa_require_attach (int pid)
{
  int tt_status;
  CORE_ADDR pc;
  CORE_ADDR pc_addr;
  unsigned int regs_offset;
  process_state_t old_process_state = process_state;

  /* Are we already attached?  There appears to be no explicit
   * way to answer this via ttrace, so we try something which
   * should be innocuous if we are attached.  If that fails,
   * then we assume we're not attached, and so attempt to make
   * it so.
   */
  errno = 0;
  tt_status = call_real_ttrace (TT_PROC_STOP,
				pid,
				(lwpid_t) TT_NIL,
				(TTRACE_ARG_TYPE) TT_NIL,
				(TTRACE_ARG_TYPE) TT_NIL,
				TT_NIL);

  if (errno)
    {
      /* No change to process-state!
       */
      errno = 0;
      pid = attach (pid);
    }
  else
    {
      /* If successful, the process is now stopped.  But if
       * we're VFORKING, the parent is still running, so don't
       * change the process state.
       */
      if (process_state != VFORKING)
	process_state = STOPPED;

      /* If we were already attached, you'd think that we
       * would need to start going again--but you'd be wrong,
       * as the fork-following code is actually in the middle
       * of the "resume" routine in in "infrun.c" and so
       * will (almost) immediately do a resume.
       *
       * On the other hand, if we are VFORKING, which means
       * that the child and the parent share a process for a
       * while, we know that "resume" won't be resuming
       * until the child EXEC event is seen.  But we still
       * don't want to continue, as the event is already
       * there waiting.
       */
      update_thread_state_after_attach (pid, DONT_ATTACH_CONTINUE);
    }				/* STOP succeeded */

  return pid;
}