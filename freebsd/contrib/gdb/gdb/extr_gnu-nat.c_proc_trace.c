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
typedef  int /*<<< orphan*/  thread_state_t ;
struct proc {scalar_t__ exc_port; TYPE_1__* inf; } ;
struct TYPE_2__ {int /*<<< orphan*/  event_port; } ;

/* Variables and functions */
 scalar_t__ MACH_PORT_NULL ; 
 int /*<<< orphan*/  THREAD_STATE_CLEAR_TRACED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THREAD_STATE_SET_TRACED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_debug (struct proc*,char*,char*) ; 
 int /*<<< orphan*/  proc_get_state (struct proc*,int) ; 
 int /*<<< orphan*/  proc_steal_exc_port (struct proc*,int /*<<< orphan*/ ) ; 

int
proc_trace (struct proc *proc, int set)
{
  thread_state_t state = proc_get_state (proc, 1);

  if (!state)
    return 0;			/* the thread must be dead.  */

  proc_debug (proc, "tracing %s", set ? "on" : "off");

  if (set)
    {
      /* XXX We don't get the exception unless the thread has its own
         exception port???? */
      if (proc->exc_port == MACH_PORT_NULL)
	proc_steal_exc_port (proc, proc->inf->event_port);
      THREAD_STATE_SET_TRACED (state);
    }
  else
    THREAD_STATE_CLEAR_TRACED (state);

  return 1;
}