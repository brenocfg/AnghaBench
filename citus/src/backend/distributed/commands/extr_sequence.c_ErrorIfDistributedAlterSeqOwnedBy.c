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
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_3__ {int /*<<< orphan*/  options; int /*<<< orphan*/  missing_ok; int /*<<< orphan*/  sequence; } ;
typedef  scalar_t__ Oid ;
typedef  TYPE_1__ AlterSeqStmt ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  DEPENDENCY_AUTO ; 
 int /*<<< orphan*/  DEPENDENCY_INTERNAL ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidOid ; 
 int IsDistributedTable (scalar_t__) ; 
 scalar_t__ OptionsSpecifyOwnedBy (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ RangeVarGetRelid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int sequenceIsOwned (scalar_t__,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 

void
ErrorIfDistributedAlterSeqOwnedBy(AlterSeqStmt *alterSeqStmt)
{
	Oid sequenceId = RangeVarGetRelid(alterSeqStmt->sequence, AccessShareLock,
									  alterSeqStmt->missing_ok);
	bool sequenceOwned = false;
	Oid ownedByTableId = InvalidOid;
	Oid newOwnedByTableId = InvalidOid;
	int32 ownedByColumnId = 0;
	bool hasDistributedOwner = false;

	/* alter statement referenced nonexistent sequence; return */
	if (sequenceId == InvalidOid)
	{
		return;
	}

	sequenceOwned = sequenceIsOwned(sequenceId, DEPENDENCY_AUTO, &ownedByTableId,
									&ownedByColumnId);
	if (!sequenceOwned)
	{
		sequenceOwned = sequenceIsOwned(sequenceId, DEPENDENCY_INTERNAL, &ownedByTableId,
										&ownedByColumnId);
	}

	/* see whether the sequence is already owned by a distributed table */
	if (sequenceOwned)
	{
		hasDistributedOwner = IsDistributedTable(ownedByTableId);
	}

	if (OptionsSpecifyOwnedBy(alterSeqStmt->options, &newOwnedByTableId))
	{
		/* if a distributed sequence tries to change owner, error */
		if (hasDistributedOwner && ownedByTableId != newOwnedByTableId)
		{
			ereport(ERROR, (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
							errmsg("cannot alter OWNED BY option of a sequence "
								   "already owned by a distributed table")));
		}
		else if (!hasDistributedOwner && IsDistributedTable(newOwnedByTableId))
		{
			/* and don't let local sequences get a distributed OWNED BY */
			ereport(ERROR, (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
							errmsg("cannot associate an existing sequence with a "
								   "distributed table"),
							errhint("Use a sequence in a distributed table by specifying "
									"a serial column type before creating any shards.")));
		}
	}
}