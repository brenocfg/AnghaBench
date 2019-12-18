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
struct TYPE_3__ {scalar_t__ failureCount; } ;
typedef  TYPE_1__ TaskExecution ;

/* Variables and functions */
 scalar_t__ MAX_TASK_EXECUTION_FAILURES ; 

bool
TaskExecutionFailed(TaskExecution *taskExecution)
{
	if (taskExecution->failureCount >= MAX_TASK_EXECUTION_FAILURES)
	{
		return true;
	}

	return false;
}