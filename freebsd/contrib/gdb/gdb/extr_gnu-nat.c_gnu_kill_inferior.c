#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct proc {int /*<<< orphan*/  port; } ;
struct TYPE_3__ {struct proc* task; } ;

/* Variables and functions */
 TYPE_1__* current_inferior ; 
 int /*<<< orphan*/  inf_set_pid (TYPE_1__*,int) ; 
 int /*<<< orphan*/  proc_debug (struct proc*,char*) ; 
 int /*<<< orphan*/  target_mourn_inferior () ; 
 int /*<<< orphan*/  task_terminate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gnu_kill_inferior (void)
{
  struct proc *task = current_inferior->task;
  if (task)
    {
      proc_debug (task, "terminating...");
      task_terminate (task->port);
      inf_set_pid (current_inferior, -1);
    }
  target_mourn_inferior ();
}