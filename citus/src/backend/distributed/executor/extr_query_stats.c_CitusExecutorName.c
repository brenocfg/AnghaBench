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
typedef  int MultiExecutorType ;

/* Variables and functions */
#define  MULTI_EXECUTOR_ADAPTIVE 130 
#define  MULTI_EXECUTOR_COORDINATOR_INSERT_SELECT 129 
#define  MULTI_EXECUTOR_TASK_TRACKER 128 

__attribute__((used)) static char *
CitusExecutorName(MultiExecutorType executorType)
{
	switch (executorType)
	{
		case MULTI_EXECUTOR_ADAPTIVE:
		{
			return "adaptive";
		}

		case MULTI_EXECUTOR_TASK_TRACKER:
		{
			return "task-tracker";
		}

		case MULTI_EXECUTOR_COORDINATOR_INSERT_SELECT:
		{
			return "insert-select";
		}

		default:
		{
			return "unknown";
		}
	}
}