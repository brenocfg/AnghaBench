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
struct TYPE_2__ {int assignedAt; } ;
typedef  TYPE_1__ WorkerTask ;

/* Variables and functions */

__attribute__((used)) static int
CompareTasksByTime(const void *first, const void *second)
{
	WorkerTask *firstTask = (WorkerTask *) first;
	WorkerTask *secondTask = (WorkerTask *) second;

	/* tasks that are assigned earlier have higher priority */
	int timeDiff = firstTask->assignedAt - secondTask->assignedAt;
	return timeDiff;
}