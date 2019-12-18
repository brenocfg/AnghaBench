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
struct TYPE_3__ {int taskType; } ;
typedef  TYPE_1__ Task ;
typedef  int /*<<< orphan*/  RowModifyLevel ;
typedef  int /*<<< orphan*/  PlacementExecutionOrder ;

/* Variables and functions */
#define  DDL_TASK 136 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EXECUTION_ORDER_ANY ; 
 int /*<<< orphan*/  EXECUTION_ORDER_PARALLEL ; 
 int /*<<< orphan*/  EXECUTION_ORDER_SEQUENTIAL ; 
#define  MAP_OUTPUT_FETCH_TASK 135 
#define  MAP_TASK 134 
#define  MERGE_FETCH_TASK 133 
#define  MERGE_TASK 132 
#define  MODIFY_TASK 131 
#define  ROUTER_TASK 130 
 int /*<<< orphan*/  ROW_MODIFY_NONCOMMUTATIVE ; 
#define  SQL_TASK 129 
#define  VACUUM_ANALYZE_TASK 128 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int) ; 

__attribute__((used)) static PlacementExecutionOrder
ExecutionOrderForTask(RowModifyLevel modLevel, Task *task)
{
	switch (task->taskType)
	{
		case SQL_TASK:
		case ROUTER_TASK:
		{
			return EXECUTION_ORDER_ANY;
		}

		case MODIFY_TASK:
		{
			/*
			 * For non-commutative modifications we take aggressive locks, so
			 * there is no risk of deadlock and we can run them in parallel.
			 * When the modification is commutative, we take no additional
			 * locks, so we take a conservative approach and execute sequentially
			 * to avoid deadlocks.
			 */
			if (modLevel < ROW_MODIFY_NONCOMMUTATIVE)
			{
				return EXECUTION_ORDER_SEQUENTIAL;
			}
			else
			{
				return EXECUTION_ORDER_PARALLEL;
			}
		}

		case DDL_TASK:
		case VACUUM_ANALYZE_TASK:
		{
			return EXECUTION_ORDER_PARALLEL;
		}

		case MAP_TASK:
		case MERGE_TASK:
		case MAP_OUTPUT_FETCH_TASK:
		case MERGE_FETCH_TASK:
		default:
		{
			ereport(ERROR, (errmsg("unsupported task type %d in adaptive executor",
								   task->taskType)));
		}
	}
}