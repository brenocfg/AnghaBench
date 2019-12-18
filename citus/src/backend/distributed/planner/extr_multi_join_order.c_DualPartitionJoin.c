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
typedef  int /*<<< orphan*/  TableEntry ;
typedef  int /*<<< orphan*/  OpExpr ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  JoinType ;
typedef  int /*<<< orphan*/  JoinOrderNode ;

/* Variables and functions */
 int /*<<< orphan*/  DUAL_PARTITION_JOIN ; 
 int /*<<< orphan*/ * DualPartitionJoinClause (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * MakeJoinOrderNode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REDISTRIBUTE_BY_HASH ; 

__attribute__((used)) static JoinOrderNode *
DualPartitionJoin(JoinOrderNode *currentJoinNode, TableEntry *candidateTable,
				  List *applicableJoinClauses, JoinType joinType)
{
	OpExpr *joinClause = DualPartitionJoinClause(applicableJoinClauses);
	if (joinClause)
	{
		/* because of the dual partition, anchor table and partition column get lost */
		return MakeJoinOrderNode(candidateTable,
								 DUAL_PARTITION_JOIN,
								 NULL,
								 REDISTRIBUTE_BY_HASH,
								 NULL);
	}

	return NULL;
}