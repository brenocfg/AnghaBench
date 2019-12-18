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
struct TYPE_3__ {scalar_t__ commandType; } ;
typedef  TYPE_1__ Query ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  scalar_t__ CmdType ;

/* Variables and functions */
 scalar_t__ CMD_DELETE ; 
 scalar_t__ CMD_INSERT ; 
 scalar_t__ CMD_SELECT ; 
 scalar_t__ CMD_UPDATE ; 
 int /*<<< orphan*/  CitusHasBeenLoaded () ; 
 int /*<<< orphan*/  ExtractRangeTableEntryWalker (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int ListContainsDistributedTableRTE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NIL ; 

bool
NeedsDistributedPlanning(Query *query)
{
	List *allRTEs = NIL;
	CmdType commandType = query->commandType;

	if (!CitusHasBeenLoaded())
	{
		return false;
	}

	if (commandType != CMD_SELECT && commandType != CMD_INSERT &&
		commandType != CMD_UPDATE && commandType != CMD_DELETE)
	{
		return false;
	}

	ExtractRangeTableEntryWalker((Node *) query, &allRTEs);

	return ListContainsDistributedTableRTE(allRTEs);
}