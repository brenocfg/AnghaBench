#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64 ;
typedef  int /*<<< orphan*/  Tuplestorestate ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_6__ {int /*<<< orphan*/  rowsProcessed; } ;
typedef  int /*<<< orphan*/  RowModifyLevel ;
typedef  int /*<<< orphan*/ * ParamListInfo ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ DistributedExecution ;

/* Variables and functions */
 TYPE_1__* CreateDistributedExecution (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ErrorIfLocalExecutionHappened () ; 
 int /*<<< orphan*/  FinishDistributedExecution (TYPE_1__*) ; 
 scalar_t__ MultiShardConnectionType ; 
 int /*<<< orphan*/  RunDistributedExecution (TYPE_1__*) ; 
 scalar_t__ SEQUENTIAL_CONNECTION ; 
 int /*<<< orphan*/  StartDistributedExecution (TYPE_1__*) ; 

uint64
ExecuteTaskListExtended(RowModifyLevel modLevel, List *taskList,
						TupleDesc tupleDescriptor, Tuplestorestate *tupleStore,
						bool hasReturning, int targetPoolSize)
{
	DistributedExecution *execution = NULL;
	ParamListInfo paramListInfo = NULL;

	/*
	 * The code-paths that rely on this function do not know how execute
	 * commands locally.
	 */
	ErrorIfLocalExecutionHappened();

	if (MultiShardConnectionType == SEQUENTIAL_CONNECTION)
	{
		targetPoolSize = 1;
	}

	execution =
		CreateDistributedExecution(modLevel, taskList, hasReturning, paramListInfo,
								   tupleDescriptor, tupleStore, targetPoolSize);

	StartDistributedExecution(execution);
	RunDistributedExecution(execution);
	FinishDistributedExecution(execution);

	return execution->rowsProcessed;
}