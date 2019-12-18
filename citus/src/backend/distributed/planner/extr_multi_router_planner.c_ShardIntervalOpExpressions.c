#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Var ;
struct TYPE_4__ {scalar_t__ maxValueExists; scalar_t__ minValueExists; int /*<<< orphan*/  relationId; } ;
typedef  TYPE_1__ ShardInterval ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Index ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * BuildBaseConstraint (int /*<<< orphan*/ *) ; 
 char DISTRIBUTE_BY_APPEND ; 
 char DISTRIBUTE_BY_HASH ; 
 char DISTRIBUTE_BY_RANGE ; 
 int /*<<< orphan*/ * MakeInt4Column () ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/ * PartitionColumn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char PartitionMethod (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UpdateConstraint (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * list_make1 (int /*<<< orphan*/ *) ; 

List *
ShardIntervalOpExpressions(ShardInterval *shardInterval, Index rteIndex)
{
	Oid relationId = shardInterval->relationId;
	char partitionMethod = PartitionMethod(shardInterval->relationId);
	Var *partitionColumn = NULL;
	Node *baseConstraint = NULL;

	if (partitionMethod == DISTRIBUTE_BY_HASH)
	{
		partitionColumn = MakeInt4Column();
	}
	else if (partitionMethod == DISTRIBUTE_BY_RANGE || partitionMethod ==
			 DISTRIBUTE_BY_APPEND)
	{
		Assert(rteIndex > 0);
		partitionColumn = PartitionColumn(relationId, rteIndex);
	}
	else
	{
		/* do not add any shard range interval for reference tables */
		return NIL;
	}

	/* build the base expression for constraint */
	baseConstraint = BuildBaseConstraint(partitionColumn);

	/* walk over shard list and check if shards can be pruned */
	if (shardInterval->minValueExists && shardInterval->maxValueExists)
	{
		UpdateConstraint(baseConstraint, shardInterval);
	}

	return list_make1(baseConstraint);
}