#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ partitionId; } ;
typedef  TYPE_1__ Task ;
struct TYPE_10__ {scalar_t__ fragmentType; scalar_t__ fragmentReference; } ;
struct TYPE_9__ {scalar_t__ data; } ;
typedef  TYPE_2__* StringInfo ;
typedef  int /*<<< orphan*/  ShardInterval ;
typedef  TYPE_3__ RangeTableFragment ;

/* Variables and functions */
 scalar_t__ CITUS_RTE_REMOTE_QUERY ; 
 int /*<<< orphan*/  DEBUG2 ; 
 int /*<<< orphan*/ * FragmentInterval (TYPE_3__*) ; 
 TYPE_2__* FragmentIntervalString (int /*<<< orphan*/ *) ; 
 scalar_t__ IsLoggableLevel (int /*<<< orphan*/ ) ; 
 int ShardIntervalsOverlap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool
JoinPrunable(RangeTableFragment *leftFragment, RangeTableFragment *rightFragment)
{
	bool joinPrunable = false;
	bool overlap = false;
	ShardInterval *leftFragmentInterval = NULL;
	ShardInterval *rightFragmentInterval = NULL;

	/*
	 * If both range tables are remote queries, we then have a hash repartition
	 * join. In that case, we can just prune away this join if left and right
	 * hand side fragments have the same partitionId.
	 */
	if (leftFragment->fragmentType == CITUS_RTE_REMOTE_QUERY &&
		rightFragment->fragmentType == CITUS_RTE_REMOTE_QUERY)
	{
		Task *leftMergeTask = (Task *) leftFragment->fragmentReference;
		Task *rightMergeTask = (Task *) rightFragment->fragmentReference;


		if (leftMergeTask->partitionId != rightMergeTask->partitionId)
		{
			ereport(DEBUG2, (errmsg("join prunable for task partitionId %u and %u",
									leftMergeTask->partitionId,
									rightMergeTask->partitionId)));
			return true;
		}
		else
		{
			return false;
		}
	}


	/*
	 * We have a single (re)partition join. We now get shard intervals for both
	 * fragments, and then check if these intervals overlap.
	 */
	leftFragmentInterval = FragmentInterval(leftFragment);
	rightFragmentInterval = FragmentInterval(rightFragment);

	overlap = ShardIntervalsOverlap(leftFragmentInterval, rightFragmentInterval);
	if (!overlap)
	{
		if (IsLoggableLevel(DEBUG2))
		{
			StringInfo leftString = FragmentIntervalString(leftFragmentInterval);
			StringInfo rightString = FragmentIntervalString(rightFragmentInterval);

			ereport(DEBUG2, (errmsg("join prunable for intervals %s and %s",
									leftString->data, rightString->data)));
		}

		joinPrunable = true;
	}

	return joinPrunable;
}