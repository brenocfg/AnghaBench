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
typedef  int /*<<< orphan*/  Var ;
struct TYPE_3__ {scalar_t__ inhRelations; int /*<<< orphan*/ * relation; int /*<<< orphan*/ * partbound; } ;
typedef  int /*<<< orphan*/  RangeVar ;
typedef  scalar_t__ Oid ;
typedef  TYPE_1__ CreateStmt ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CreateDistributedTable (scalar_t__,int /*<<< orphan*/ *,char,char*,int) ; 
 char DISTRIBUTE_BY_HASH ; 
 int /*<<< orphan*/ * DistPartitionKey (scalar_t__) ; 
 scalar_t__ InvalidOid ; 
 scalar_t__ IsDistributedTable (scalar_t__) ; 
 scalar_t__ NIL ; 
 int /*<<< orphan*/  NoLock ; 
 scalar_t__ RangeVarGetRelid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 char* generate_qualified_relation_name (scalar_t__) ; 
 int /*<<< orphan*/ * linitial (scalar_t__) ; 
 int list_length (scalar_t__) ; 

void
ProcessCreateTableStmtPartitionOf(CreateStmt *createStatement)
{
	if (createStatement->inhRelations != NIL && createStatement->partbound != NULL)
	{
		RangeVar *parentRelation = linitial(createStatement->inhRelations);
		bool parentMissingOk = false;
		Oid parentRelationId = RangeVarGetRelid(parentRelation, NoLock,
												parentMissingOk);

		/* a partition can only inherit from single parent table */
		Assert(list_length(createStatement->inhRelations) == 1);

		Assert(parentRelationId != InvalidOid);

		/*
		 * If a partition is being created and if its parent is a distributed
		 * table, we will distribute this table as well.
		 */
		if (IsDistributedTable(parentRelationId))
		{
			bool missingOk = false;
			Oid relationId = RangeVarGetRelid(createStatement->relation, NoLock,
											  missingOk);
			Var *parentDistributionColumn = DistPartitionKey(parentRelationId);
			char parentDistributionMethod = DISTRIBUTE_BY_HASH;
			char *parentRelationName = generate_qualified_relation_name(parentRelationId);
			bool viaDeprecatedAPI = false;

			CreateDistributedTable(relationId, parentDistributionColumn,
								   parentDistributionMethod, parentRelationName,
								   viaDeprecatedAPI);
		}
	}
}