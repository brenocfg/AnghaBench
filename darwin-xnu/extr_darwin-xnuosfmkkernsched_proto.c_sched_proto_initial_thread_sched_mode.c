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
typedef  scalar_t__ task_t ;
typedef  int /*<<< orphan*/  sched_mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  TH_MODE_FIXED ; 
 int /*<<< orphan*/  TH_MODE_TIMESHARE ; 
 scalar_t__ kernel_task ; 

__attribute__((used)) static sched_mode_t
sched_proto_initial_thread_sched_mode(task_t parent_task)
{
	if (parent_task == kernel_task)
		return TH_MODE_FIXED;
	else
		return TH_MODE_TIMESHARE;	
}