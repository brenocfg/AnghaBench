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
struct proc {void* saved_exc_port; void* exc_port; } ;
typedef  int /*<<< orphan*/  mach_port_t ;
typedef  scalar_t__ error_t ;

/* Variables and functions */
 void* MACH_PORT_NULL ; 
 int /*<<< orphan*/  mach_port_deallocate (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  mach_task_self () ; 
 scalar_t__ proc_get_exception_port (struct proc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static mach_port_t
_proc_get_exc_port (struct proc *proc)
{
  mach_port_t exc_port;
  error_t err = proc_get_exception_port (proc, &exc_port);

  if (err)
    /* PROC must be dead.  */
    {
      if (proc->exc_port)
	mach_port_deallocate (mach_task_self (), proc->exc_port);
      proc->exc_port = MACH_PORT_NULL;
      if (proc->saved_exc_port)
	mach_port_deallocate (mach_task_self (), proc->saved_exc_port);
      proc->saved_exc_port = MACH_PORT_NULL;
    }

  return exc_port;
}