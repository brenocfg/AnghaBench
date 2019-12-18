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

/* Variables and functions */
 int /*<<< orphan*/  START_INFERIOR_TRAPS_EXPECTED ; 
 int /*<<< orphan*/  child_ops ; 
 int /*<<< orphan*/  pid_to_ptid (int) ; 
 int /*<<< orphan*/  push_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  startup_inferior (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_acknowledge_created_inferior (int) ; 
 int /*<<< orphan*/  target_post_startup_inferior (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ptrace_him (int pid)
{
  push_target (&child_ops);

  /* On some targets, there must be some explicit synchronization
     between the parent and child processes after the debugger
     forks, and before the child execs the debuggee program.  This
     call basically gives permission for the child to exec.
   */

  target_acknowledge_created_inferior (pid);

  /* START_INFERIOR_TRAPS_EXPECTED is defined in inferior.h,
   * and will be 1 or 2 depending on whether we're starting
   * without or with a shell.
   */
  startup_inferior (START_INFERIOR_TRAPS_EXPECTED);

  /* On some targets, there must be some explicit actions taken after
     the inferior has been started up.
   */
  target_post_startup_inferior (pid_to_ptid (pid));
}