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
typedef  int /*<<< orphan*/  thread_state_t ;
struct proc {int aborted; int state_valid; int state_changed; int /*<<< orphan*/  state; int /*<<< orphan*/  port; } ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  error_t ;

/* Variables and functions */
 int /*<<< orphan*/  THREAD_STATE_FLAVOR ; 
 int /*<<< orphan*/  THREAD_STATE_SIZE ; 
 int /*<<< orphan*/  proc_abort (struct proc*,int) ; 
 int /*<<< orphan*/  proc_debug (struct proc*,char*,...) ; 
 int /*<<< orphan*/  thread_get_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

thread_state_t
proc_get_state (struct proc *proc, int will_modify)
{
  int was_aborted = proc->aborted;

  proc_debug (proc, "updating state info%s",
	      will_modify ? " (with intention to modify)" : "");

  proc_abort (proc, will_modify);

  if (!was_aborted && proc->aborted)
    /* PROC's state may have changed since we last fetched it.  */
    proc->state_valid = 0;

  if (!proc->state_valid)
    {
      mach_msg_type_number_t state_size = THREAD_STATE_SIZE;
      error_t err =
      thread_get_state (proc->port, THREAD_STATE_FLAVOR,
			(thread_state_t) &proc->state, &state_size);
      proc_debug (proc, "getting thread state");
      proc->state_valid = !err;
    }

  if (proc->state_valid)
    {
      if (will_modify)
	proc->state_changed = 1;
      return (thread_state_t) &proc->state;
    }
  else
    return 0;
}