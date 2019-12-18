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
struct proc {int /*<<< orphan*/  port; } ;
struct i386_float_state {int /*<<< orphan*/  hw_state; } ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  scalar_t__ error_t ;

/* Variables and functions */
 int /*<<< orphan*/  i386_FLOAT_STATE ; 
 int /*<<< orphan*/  i386_FLOAT_STATE_COUNT ; 
 int /*<<< orphan*/  i387_fill_fsave (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  proc_string (struct proc*) ; 
 scalar_t__ thread_get_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ thread_set_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
store_fpregs (struct proc *thread, int regno)
{
  mach_msg_type_number_t count = i386_FLOAT_STATE_COUNT;
  struct i386_float_state state;
  error_t err;

  err = thread_get_state (thread->port, i386_FLOAT_STATE,
			  (thread_state_t) &state, &count);
  if (err)
    {
      warning ("Couldn't fetch floating-point state from %s",
	       proc_string (thread));
      return;
    }

  /* FIXME: kettenis/2001-07-15: Is this right?  Should we somehow
     take into account DEPRECATED_REGISTER_VALID like the old code did?  */
  i387_fill_fsave (state.hw_state, regno);

  err = thread_set_state (thread->port, i386_FLOAT_STATE,
			  (thread_state_t) &state, i386_FLOAT_STATE_COUNT);
  if (err)
    {
      warning ("Couldn't store floating-point state into %s",
	       proc_string (thread));
      return;
    }
}