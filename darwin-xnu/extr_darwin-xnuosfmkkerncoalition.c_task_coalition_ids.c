#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  TYPE_2__* task_t ;
struct TYPE_5__ {TYPE_1__** coalition; } ;
struct TYPE_4__ {scalar_t__ id; } ;

/* Variables and functions */
 int COALITION_NUM_TYPES ; 

void
task_coalition_ids(task_t task, uint64_t ids[COALITION_NUM_TYPES])
{
	int i;
	for (i = 0; i < COALITION_NUM_TYPES; i++) {
		if (task->coalition[i])
			ids[i] = task->coalition[i]->id;
		else
			ids[i] = 0;
	}
}