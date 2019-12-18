#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * taskPlacementList; } ;
typedef  TYPE_1__ Task ;
struct TYPE_10__ {scalar_t__ format; int indent; int /*<<< orphan*/  str; } ;
typedef  int /*<<< orphan*/  ShardPlacement ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_2__ ExplainState ;

/* Variables and functions */
 scalar_t__ EXPLAIN_FORMAT_TEXT ; 
 int /*<<< orphan*/  ExplainCloseGroup (char*,int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 int /*<<< orphan*/  ExplainOpenGroup (char*,int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 int /*<<< orphan*/  ExplainPropertyText (char*,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  ExplainTaskPlacement (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  appendStringInfoSpaces (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * list_nth (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
ExplainTask(Task *task, int placementIndex, List *explainOutputList, ExplainState *es)
{
	ExplainOpenGroup("Task", NULL, true, es);

	if (es->format == EXPLAIN_FORMAT_TEXT)
	{
		appendStringInfoSpaces(es->str, es->indent * 2);
		appendStringInfo(es->str, "->  Task\n");
		es->indent += 3;
	}

	if (explainOutputList != NIL)
	{
		List *taskPlacementList = task->taskPlacementList;
		ShardPlacement *taskPlacement = list_nth(taskPlacementList, placementIndex);

		ExplainTaskPlacement(taskPlacement, explainOutputList, es);
	}
	else
	{
		ExplainPropertyText("Error", "Could not get remote plan.", es);
	}

	ExplainCloseGroup("Task", NULL, true, es);

	if (es->format == EXPLAIN_FORMAT_TEXT)
	{
		es->indent -= 3;
	}
}