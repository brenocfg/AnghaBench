#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* jointree; } ;
struct TYPE_6__ {int /*<<< orphan*/ * quals; } ;
typedef  TYPE_2__ Query ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Expr ;
typedef  int /*<<< orphan*/  Const ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExtractFirstDistributedTableId (TYPE_2__*) ; 
 int /*<<< orphan*/  FastPathRouterQuery (TYPE_2__*) ; 
 int /*<<< orphan*/ * PruneShards (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int list_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_ands_implicit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static List *
TargetShardIntervalForFastPathQuery(Query *query, Const **partitionValueConst,
									bool *isMultiShardQuery)
{
	Const *queryPartitionValueConst = NULL;

	Oid relationId = ExtractFirstDistributedTableId(query);
	Node *quals = query->jointree->quals;

	int relationIndex = 1;

	List *prunedShardIntervalList =
		PruneShards(relationId, relationIndex, make_ands_implicit((Expr *) quals),
					&queryPartitionValueConst);

	/* we're only expecting single shard from a single table */
	Assert(FastPathRouterQuery(query));

	if (list_length(prunedShardIntervalList) > 1)
	{
		*isMultiShardQuery = true;
	}
	else if (list_length(prunedShardIntervalList) == 1 &&
			 partitionValueConst != NULL)
	{
		/* set the outgoing partition column value if requested */
		*partitionValueConst = queryPartitionValueConst;
	}

	return prunedShardIntervalList;
}