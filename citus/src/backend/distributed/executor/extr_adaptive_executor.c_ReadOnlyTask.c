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
typedef  scalar_t__ TaskType ;

/* Variables and functions */
 scalar_t__ ROUTER_TASK ; 
 scalar_t__ SQL_TASK ; 

bool
ReadOnlyTask(TaskType taskType)
{
	if (taskType == ROUTER_TASK || taskType == SQL_TASK)
	{
		/*
		 * TODO: We currently do not execute modifying CTEs via ROUTER_TASK/SQL_TASK.
		 * When we implement it, we should either not use the mentioned task types for
		 * modifying CTEs detect them here.
		 */
		return true;
	}

	return false;
}