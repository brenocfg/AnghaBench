#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  relation; scalar_t__ is_program; int /*<<< orphan*/ * filename; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ CopyStmt ;

/* Variables and functions */
 int /*<<< orphan*/  BeginOrContinueCoordinatedTransaction () ; 
 int /*<<< orphan*/  CopyFromWorkerNode (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  CopyToExistingShards (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  CopyToNewShards (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 char DISTRIBUTE_BY_APPEND ; 
 char DISTRIBUTE_BY_HASH ; 
 char DISTRIBUTE_BY_NONE ; 
 char DISTRIBUTE_BY_RANGE ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EnsurePartitionTableNotReplicated (int /*<<< orphan*/ ) ; 
 int IsCopyFromWorker (TYPE_1__*) ; 
 int /*<<< orphan*/  NoLock ; 
 char PartitionMethod (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RangeVarGetRelid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XACT_MODIFICATION_DATA ; 
 int /*<<< orphan*/  XactModificationLevel ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/ * masterConnection ; 
 int /*<<< orphan*/  superuser () ; 

__attribute__((used)) static void
CitusCopyFrom(CopyStmt *copyStatement, char *completionTag)
{
	bool isCopyFromWorker = false;

	BeginOrContinueCoordinatedTransaction();

	/* disallow COPY to/from file or program except for superusers */
	if (copyStatement->filename != NULL && !superuser())
	{
		if (copyStatement->is_program)
		{
			ereport(ERROR,
					(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
					 errmsg("must be superuser to COPY to or from an external program"),
					 errhint("Anyone can COPY to stdout or from stdin. "
							 "psql's \\copy command also works for anyone.")));
		}
		else
		{
			ereport(ERROR,
					(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
					 errmsg("must be superuser to COPY to or from a file"),
					 errhint("Anyone can COPY to stdout or from stdin. "
							 "psql's \\copy command also works for anyone.")));
		}
	}

	masterConnection = NULL; /* reset, might still be set after error */
	isCopyFromWorker = IsCopyFromWorker(copyStatement);
	if (isCopyFromWorker)
	{
		CopyFromWorkerNode(copyStatement, completionTag);
	}
	else
	{
		Oid relationId = RangeVarGetRelid(copyStatement->relation, NoLock, false);
		char partitionMethod = PartitionMethod(relationId);

		/* disallow modifications to a partition table which have rep. factor > 1 */
		EnsurePartitionTableNotReplicated(relationId);

		if (partitionMethod == DISTRIBUTE_BY_HASH || partitionMethod ==
			DISTRIBUTE_BY_RANGE || partitionMethod == DISTRIBUTE_BY_NONE)
		{
			CopyToExistingShards(copyStatement, completionTag);
		}
		else if (partitionMethod == DISTRIBUTE_BY_APPEND)
		{
			CopyToNewShards(copyStatement, completionTag, relationId);
		}
		else
		{
			ereport(ERROR, (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
							errmsg("unsupported partition method")));
		}
	}

	XactModificationLevel = XACT_MODIFICATION_DATA;
}