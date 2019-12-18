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
struct TYPE_2__ {int /*<<< orphan*/  kind; } ;

/* Variables and functions */
 int /*<<< orphan*/  TARGET_SIGNAL_0 ; 
 int /*<<< orphan*/  TARGET_WAITKIND_SPURIOUS ; 
 int /*<<< orphan*/  breakpoint_init_inferior (int /*<<< orphan*/ ) ; 
 scalar_t__ breakpoints_inserted ; 
 int /*<<< orphan*/  clear_proceed_status () ; 
 int /*<<< orphan*/  inf_starting ; 
 scalar_t__ number_of_threads_in_syscalls ; 
 TYPE_1__ pending_follow ; 
 scalar_t__ prev_pc ; 
 scalar_t__ stepping_past_singlestep_breakpoint ; 
 int /*<<< orphan*/  stop_signal ; 
 scalar_t__ trap_expected_after_continue ; 

void
init_wait_for_inferior (void)
{
  /* These are meaningless until the first time through wait_for_inferior.  */
  prev_pc = 0;

#ifdef HP_OS_BUG
  trap_expected_after_continue = 0;
#endif
  breakpoints_inserted = 0;
  breakpoint_init_inferior (inf_starting);

  /* Don't confuse first call to proceed(). */
  stop_signal = TARGET_SIGNAL_0;

  /* The first resume is not following a fork/vfork/exec. */
  pending_follow.kind = TARGET_WAITKIND_SPURIOUS;	/* I.e., none. */

  /* See wait_for_inferior's handling of SYSCALL_ENTRY/RETURN events. */
  number_of_threads_in_syscalls = 0;

  clear_proceed_status ();

  stepping_past_singlestep_breakpoint = 0;
}