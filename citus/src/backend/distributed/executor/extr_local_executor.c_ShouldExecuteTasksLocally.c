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
 int /*<<< orphan*/  AnyConnectionAccessedPlacements () ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  EnableLocalExecution ; 
 scalar_t__ InCoordinatedTransaction () ; 
 scalar_t__ IsMultiStatementTransaction () ; 
 scalar_t__ LocalExecutionHappened ; 
 scalar_t__ TaskAccessesLocalNode (int /*<<< orphan*/ *) ; 
 scalar_t__ linitial (int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ *) ; 

bool
ShouldExecuteTasksLocally(List *taskList)
{
	bool singleTask = false;

	if (!EnableLocalExecution)
	{
		return false;
	}

	if (LocalExecutionHappened)
	{
		/*
		 * For various reasons, including the transaction visibility
		 * rules (e.g., read-your-own-writes), we have to use local
		 * execution again if it has already happened within this
		 * transaction block.
		 *
		 * We might error out later in the execution if it is not suitable
		 * to execute the tasks locally.
		 */
		Assert(IsMultiStatementTransaction() || InCoordinatedTransaction());

		/*
		 * TODO: A future improvement could be to keep track of which placements
		 * have been locally executed. At this point, only use local execution for
		 * those placements. That'd help to benefit more from parallelism.
		 */

		return true;
	}

	singleTask = (list_length(taskList) == 1);
	if (singleTask && TaskAccessesLocalNode((Task *) linitial(taskList)))
	{
		/*
		 * This is the valuable time to use the local execution. We are likely
		 * to avoid any network round-trips by simply executing the command within
		 * this session.
		 *
		 * We cannot avoid network round trips if the task is not a read only
		 * task and accesses multiple placements. For example, modifications to
		 * distributed tables (with replication factor == 1) would avoid network
		 * round-trips. However, modifications to reference tables still needs to
		 * go to over the network to do the modification on the other placements.
		 * Still, we'll be avoding the network round trip for this node.
		 *
		 * Note that we shouldn't use local execution if any distributed execution
		 * has happened because that'd break transaction visibility rules and
		 * many other things.
		 */
		return !AnyConnectionAccessedPlacements();
	}

	if (!singleTask)
	{
		/*
		 * For multi-task executions, switching to local execution would likely to
		 * perform poorly, because we'd lose the parallelizm. Note that the local
		 * execution is happening one task at a time (e.g., similar to sequential
		 * distributed execution).
		 */
		Assert(!LocalExecutionHappened);

		return false;
	}

	return false;
}