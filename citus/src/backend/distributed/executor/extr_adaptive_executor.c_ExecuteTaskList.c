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
typedef  int /*<<< orphan*/  uint64 ;
typedef  int /*<<< orphan*/  Tuplestorestate ;
typedef  int /*<<< orphan*/ * TupleDesc ;
typedef  int /*<<< orphan*/  RowModifyLevel ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  ExecuteTaskListExtended (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

uint64
ExecuteTaskList(RowModifyLevel modLevel, List *taskList, int targetPoolSize)
{
	TupleDesc tupleDescriptor = NULL;
	Tuplestorestate *tupleStore = NULL;
	bool hasReturning = false;

	return ExecuteTaskListExtended(modLevel, taskList, tupleDescriptor,
								   tupleStore, hasReturning, targetPoolSize);
}