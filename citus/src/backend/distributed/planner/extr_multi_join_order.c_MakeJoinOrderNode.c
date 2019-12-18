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
typedef  int /*<<< orphan*/  TableEntry ;
struct TYPE_4__ {char partitionMethod; int /*<<< orphan*/ * anchorTable; int /*<<< orphan*/  joinClauseList; int /*<<< orphan*/ * partitionColumn; int /*<<< orphan*/  joinType; int /*<<< orphan*/  joinRuleType; int /*<<< orphan*/ * tableEntry; } ;
typedef  int /*<<< orphan*/  JoinRuleType ;
typedef  TYPE_1__ JoinOrderNode ;

/* Variables and functions */
 int /*<<< orphan*/  JOIN_INNER ; 
 int /*<<< orphan*/  NIL ; 
 TYPE_1__* palloc0 (int) ; 

JoinOrderNode *
MakeJoinOrderNode(TableEntry *tableEntry, JoinRuleType joinRuleType,
				  Var *partitionColumn, char partitionMethod, TableEntry *anchorTable)
{
	JoinOrderNode *joinOrderNode = palloc0(sizeof(JoinOrderNode));
	joinOrderNode->tableEntry = tableEntry;
	joinOrderNode->joinRuleType = joinRuleType;
	joinOrderNode->joinType = JOIN_INNER;
	joinOrderNode->partitionColumn = partitionColumn;
	joinOrderNode->partitionMethod = partitionMethod;
	joinOrderNode->joinClauseList = NIL;
	joinOrderNode->anchorTable = anchorTable;

	return joinOrderNode;
}