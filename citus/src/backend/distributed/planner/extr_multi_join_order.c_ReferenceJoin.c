#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  relationId; } ;
typedef  TYPE_2__ TableEntry ;
struct TYPE_11__ {int /*<<< orphan*/  anchorTable; int /*<<< orphan*/  partitionMethod; int /*<<< orphan*/  partitionColumn; TYPE_1__* tableEntry; } ;
struct TYPE_9__ {int /*<<< orphan*/  relationId; } ;
typedef  int /*<<< orphan*/  List ;
typedef  scalar_t__ JoinType ;
typedef  TYPE_3__ JoinOrderNode ;

/* Variables and functions */
 char DISTRIBUTE_BY_NONE ; 
 scalar_t__ JOIN_ANTI ; 
 scalar_t__ JOIN_FULL ; 
 scalar_t__ JOIN_INNER ; 
 scalar_t__ JOIN_LEFT ; 
 scalar_t__ JOIN_RIGHT ; 
 TYPE_3__* MakeJoinOrderNode (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char PartitionMethod (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REFERENCE_JOIN ; 
 int list_length (int /*<<< orphan*/ *) ; 

__attribute__((used)) static JoinOrderNode *
ReferenceJoin(JoinOrderNode *currentJoinNode, TableEntry *candidateTable,
			  List *applicableJoinClauses, JoinType joinType)
{
	JoinOrderNode *nextJoinNode = NULL;
	int applicableJoinCount = list_length(applicableJoinClauses);
	char candidatePartitionMethod = PartitionMethod(candidateTable->relationId);
	char leftPartitionMethod = PartitionMethod(currentJoinNode->tableEntry->relationId);
	bool performReferenceJoin = false;

	if (applicableJoinCount <= 0)
	{
		return NULL;
	}

	/*
	 * If the table is a reference table, then the reference join is feasible.It
	 * is valid only for inner joins.
	 *
	 * Right join requires existing (left) table to be reference table, full outer
	 * join requires both tables to be reference tables.
	 */
	if ((joinType == JOIN_INNER || joinType == JOIN_LEFT || joinType == JOIN_ANTI) &&
		candidatePartitionMethod == DISTRIBUTE_BY_NONE)
	{
		performReferenceJoin = true;
	}
	else if (joinType == JOIN_RIGHT && leftPartitionMethod == DISTRIBUTE_BY_NONE)
	{
		performReferenceJoin = true;
	}
	else if (joinType == JOIN_FULL && leftPartitionMethod == DISTRIBUTE_BY_NONE &&
			 candidatePartitionMethod == DISTRIBUTE_BY_NONE)
	{
		performReferenceJoin = true;
	}

	if (performReferenceJoin)
	{
		nextJoinNode = MakeJoinOrderNode(candidateTable, REFERENCE_JOIN,
										 currentJoinNode->partitionColumn,
										 currentJoinNode->partitionMethod,
										 currentJoinNode->anchorTable);
	}

	return nextJoinNode;
}