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
struct proc {scalar_t__ exc_port; scalar_t__ saved_exc_port; } ;
typedef  scalar_t__ mach_port_t ;
typedef  scalar_t__ error_t ;

/* Variables and functions */
 scalar_t__ _proc_get_exc_port (struct proc*) ; 
 int /*<<< orphan*/  mach_port_deallocate (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mach_task_self () ; 
 int /*<<< orphan*/  proc_debug (struct proc*,char*,scalar_t__) ; 
 scalar_t__ proc_set_exception_port (struct proc*,scalar_t__) ; 
 int /*<<< orphan*/  proc_string (struct proc*) ; 
 int /*<<< orphan*/  safe_strerror (scalar_t__) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
proc_steal_exc_port (struct proc *proc, mach_port_t exc_port)
{
  mach_port_t cur_exc_port = _proc_get_exc_port (proc);

  if (cur_exc_port)
    {
      error_t err = 0;

      proc_debug (proc, "inserting exception port: %d", exc_port);

      if (cur_exc_port != exc_port)
	/* Put in our exception port.  */
	err = proc_set_exception_port (proc, exc_port);

      if (err || cur_exc_port == proc->exc_port)
	/* We previously set the exception port, and it's still set.  So we
	   just keep the old saved port which is what the proc set.  */
	{
	  if (cur_exc_port)
	    mach_port_deallocate (mach_task_self (), cur_exc_port);
	}
      else
	/* Keep a copy of PROC's old exception port so it can be restored. */
	{
	  if (proc->saved_exc_port)
	    mach_port_deallocate (mach_task_self (), proc->saved_exc_port);
	  proc->saved_exc_port = cur_exc_port;
	}

      proc_debug (proc, "saved exception port: %d", proc->saved_exc_port);

      if (!err)
	proc->exc_port = exc_port;
      else
	warning ("Error setting exception port for %s: %s",
		 proc_string (proc), safe_strerror (err));
    }
}