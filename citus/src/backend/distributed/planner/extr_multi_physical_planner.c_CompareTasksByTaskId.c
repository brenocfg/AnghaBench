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
typedef  int uint32 ;
struct TYPE_2__ {int taskId; } ;
typedef  TYPE_1__ Task ;

/* Variables and functions */

int
CompareTasksByTaskId(const void *leftElement, const void *rightElement)
{
	const Task *leftTask = *((const Task **) leftElement);
	const Task *rightTask = *((const Task **) rightElement);

	uint32 leftTaskId = leftTask->taskId;
	uint32 rightTaskId = rightTask->taskId;

	int taskIdDiff = leftTaskId - rightTaskId;
	return taskIdDiff;
}