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
struct TYPE_3__ {scalar_t__ taskType; } ;
typedef  TYPE_1__ Task ;

/* Variables and functions */
 scalar_t__ SQL_TASK ; 

__attribute__((used)) static bool
TopLevelTask(Task *task)
{
	bool topLevelTask = false;

	/*
	 * SQL tasks can only appear at the top level in our query tree. Further, no
	 * other task type can appear at the top level in our tree.
	 */
	if (task->taskType == SQL_TASK)
	{
		topLevelTask = true;
	}

	return topLevelTask;
}