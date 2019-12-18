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
struct proc {int /*<<< orphan*/  tid; TYPE_1__* inf; } ;
struct TYPE_2__ {int pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  MERGEPID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pid_to_thread_id (int /*<<< orphan*/ ) ; 
 scalar_t__ proc_is_task (struct proc*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 

char *
proc_string (struct proc *proc)
{
  static char tid_str[80];
  if (proc_is_task (proc))
    sprintf (tid_str, "process %d", proc->inf->pid);
  else
    sprintf (tid_str, "thread %d.%d",
	     proc->inf->pid, pid_to_thread_id (MERGEPID (proc->tid, 0)));
  return tid_str;
}