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
typedef  int /*<<< orphan*/  Task ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 scalar_t__ TaskListMember (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

List *
TaskListAppendUnique(List *list, Task *task)
{
	if (TaskListMember(list, task))
	{
		return list;
	}

	return lappend(list, task);
}