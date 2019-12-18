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
struct breakpoint {scalar_t__ type; int thread; } ;
typedef  TYPE_1__* bpstat ;
struct TYPE_3__ {struct breakpoint* breakpoint_at; struct TYPE_3__* next; } ;

/* Variables and functions */
 scalar_t__ bp_step_resume ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int pid_to_thread_id (int /*<<< orphan*/ ) ; 

struct breakpoint *
bpstat_find_step_resume_breakpoint (bpstat bsp)
{
  int current_thread;

  if (bsp == NULL)
    error ("Internal error (bpstat_find_step_resume_breakpoint)");

  current_thread = pid_to_thread_id (inferior_ptid);

  for (; bsp != NULL; bsp = bsp->next)
    {
      if ((bsp->breakpoint_at != NULL) &&
	  (bsp->breakpoint_at->type == bp_step_resume) &&
	  (bsp->breakpoint_at->thread == current_thread || 
	   bsp->breakpoint_at->thread == -1))
	return bsp->breakpoint_at;
    }

  error ("Internal error (no step_resume breakpoint found)");
}