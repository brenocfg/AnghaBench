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
struct proc {int /*<<< orphan*/  port; } ;
typedef  int /*<<< orphan*/  mach_port_t ;
typedef  int /*<<< orphan*/  error_t ;

/* Variables and functions */
 int /*<<< orphan*/  proc_debug (struct proc*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ proc_is_task (struct proc*) ; 
 int /*<<< orphan*/  task_set_exception_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_set_exception_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

error_t
proc_set_exception_port (struct proc * proc, mach_port_t port)
{
  proc_debug (proc, "setting exception port: %d", port);
  if (proc_is_task (proc))
    return task_set_exception_port (proc->port, port);
  else
    return thread_set_exception_port (proc->port, port);
}