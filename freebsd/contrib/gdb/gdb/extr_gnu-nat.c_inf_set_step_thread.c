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
struct proc {scalar_t__ port; int /*<<< orphan*/  tid; } ;
struct inf {struct proc* step_thread; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 scalar_t__ MACH_PORT_NULL ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  inf_debug (struct inf*,char*,...) ; 
 scalar_t__ proc_is_thread (struct proc*) ; 
 scalar_t__ proc_trace (struct proc*,int) ; 

void
inf_set_step_thread (struct inf *inf, struct proc *thread)
{
  gdb_assert (!thread || proc_is_thread (thread));

  if (thread)
    inf_debug (inf, "setting step thread: %d/%d", inf->pid, thread->tid);
  else
    inf_debug (inf, "clearing step thread");

  if (inf->step_thread != thread)
    {
      if (inf->step_thread && inf->step_thread->port != MACH_PORT_NULL)
	if (!proc_trace (inf->step_thread, 0))
	  return;
      if (thread && proc_trace (thread, 1))
	inf->step_thread = thread;
      else
	inf->step_thread = 0;
    }
}