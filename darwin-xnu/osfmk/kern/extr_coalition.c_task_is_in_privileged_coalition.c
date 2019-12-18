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
typedef  TYPE_2__* task_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_5__ {TYPE_1__** coalition; } ;
struct TYPE_4__ {int /*<<< orphan*/  privileged; } ;

/* Variables and functions */
 int COALITION_TYPE_MAX ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ unrestrict_coalition_syscalls ; 

boolean_t
task_is_in_privileged_coalition(task_t task, int type)
{
	if (type < 0 || type > COALITION_TYPE_MAX)
		return FALSE;
	if (unrestrict_coalition_syscalls)
		return TRUE;
	if (!task->coalition[type])
		return FALSE;
	return task->coalition[type]->privileged;
}