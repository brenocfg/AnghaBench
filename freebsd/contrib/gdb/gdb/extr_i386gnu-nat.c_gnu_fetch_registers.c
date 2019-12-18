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
struct proc {int fetched_regs; } ;

/* Variables and functions */
 int I386_NUM_GREGS ; 
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGISTER_NAME (int) ; 
 int /*<<< orphan*/  REG_ADDR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  current_inferior ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fetch_fpregs (struct proc*) ; 
 struct proc* inf_tid_to_thread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inf_update_procs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  proc_debug (struct proc*,char*,...) ; 
 int /*<<< orphan*/  proc_get_state (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_string (struct proc*) ; 
 int /*<<< orphan*/  supply_register (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 

void
gnu_fetch_registers (int regno)
{
  struct proc *thread;

  /* Make sure we know about new threads.  */
  inf_update_procs (current_inferior);

  thread = inf_tid_to_thread (current_inferior, PIDGET (inferior_ptid));
  if (!thread)
    error ("Can't fetch registers from thread %d: No such thread",
	   PIDGET (inferior_ptid));

  if (regno < I386_NUM_GREGS || regno == -1)
    {
      thread_state_t state;

      /* This does the dirty work for us.  */
      state = proc_get_state (thread, 0);
      if (!state)
	{
	  warning ("Couldn't fetch registers from %s",
		   proc_string (thread));
	  return;
	}

      if (regno == -1)
	{
	  int i;

	  proc_debug (thread, "fetching all register");

	  for (i = 0; i < I386_NUM_GREGS; i++)
	    supply_register (i, REG_ADDR (state, i));
	  thread->fetched_regs = ~0;
	}
      else
	{
	  proc_debug (thread, "fetching register %s", REGISTER_NAME (regno));

	  supply_register (regno, REG_ADDR (state, regno));
	  thread->fetched_regs |= (1 << regno);
	}
    }

  if (regno >= I386_NUM_GREGS || regno == -1)
    {
      proc_debug (thread, "fetching floating-point registers");

      fetch_fpregs (thread);
    }
}