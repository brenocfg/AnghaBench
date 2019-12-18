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
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* StringInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  DeferredErrorMessage ;

/* Variables and functions */
 int /*<<< orphan*/ * DeferredError (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  PartitionParentOid (int /*<<< orphan*/ ) ; 
 scalar_t__ PartitionTableNoLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SingleReplicatedTable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,char*) ; 
 char* get_rel_name (int /*<<< orphan*/ ) ; 
 TYPE_1__* makeStringInfo () ; 

__attribute__((used)) static DeferredErrorMessage *
DeferErrorIfPartitionTableNotSingleReplicated(Oid relationId)
{
	if (PartitionTableNoLock(relationId) && !SingleReplicatedTable(relationId))
	{
		Oid parentOid = PartitionParentOid(relationId);
		char *parentRelationTest = get_rel_name(parentOid);
		StringInfo errorHint = makeStringInfo();

		appendStringInfo(errorHint, "Run the query on the parent table "
									"\"%s\" instead.", parentRelationTest);

		return DeferredError(ERRCODE_FEATURE_NOT_SUPPORTED,
							 "modifications on partitions when replication "
							 "factor is greater than 1 is not supported",
							 NULL, errorHint->data);
	}

	return NULL;
}