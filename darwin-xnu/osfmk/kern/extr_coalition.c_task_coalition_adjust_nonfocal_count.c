#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  TYPE_1__* task_t ;
typedef  TYPE_2__* coalition_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_6__ {int /*<<< orphan*/  nonfocal_task_count; } ;
struct TYPE_5__ {TYPE_2__** coalition; } ;

/* Variables and functions */
 size_t COALITION_FOCAL_TASKS_ACCOUNTING ; 
 TYPE_2__* COALITION_NULL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  hw_atomic_add (int /*<<< orphan*/ *,int) ; 

boolean_t task_coalition_adjust_nonfocal_count(task_t task, int count, uint32_t *new_count)
{
	coalition_t coal = task->coalition[COALITION_FOCAL_TASKS_ACCOUNTING];
	if (coal == COALITION_NULL)
	    return FALSE;

	*new_count = hw_atomic_add(&coal->nonfocal_task_count, count);
	assert(*new_count != UINT32_MAX);
	return TRUE;
}