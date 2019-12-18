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
struct TYPE_2__ {scalar_t__ rowValuesLists; } ;
typedef  TYPE_1__ Task ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 scalar_t__ NIL ; 
 scalar_t__ linitial (int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
ShouldRunTasksSequentially(List *taskList)
{
	Task *initialTask = NULL;

	if (list_length(taskList) < 2)
	{
		/* single task plans are already qualified as sequential by definition */
		return false;
	}

	/* all the tasks are the same, so we only look one */
	initialTask = (Task *) linitial(taskList);
	if (initialTask->rowValuesLists != NIL)
	{
		/* found a multi-row INSERT */
		return true;
	}

	return false;
}