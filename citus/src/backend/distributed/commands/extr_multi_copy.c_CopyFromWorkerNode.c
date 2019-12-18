#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_12__ {char* schemaname; } ;
struct TYPE_11__ {TYPE_4__* relation; } ;
struct TYPE_10__ {char* nodeName; int /*<<< orphan*/  nodePort; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ NodeAddress ;
typedef  TYPE_2__ CopyStmt ;

/* Variables and functions */
 int /*<<< orphan*/  ClaimConnectionExclusively (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CopyToNewShards (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 char DISTRIBUTE_BY_APPEND ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FOR_DML ; 
 int /*<<< orphan*/ * GetNodeConnection (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  MarkRemoteTransactionCritical (int /*<<< orphan*/ *) ; 
 TYPE_1__* MasterNodeAddress (TYPE_2__*) ; 
 char MasterPartitionMethod (TYPE_4__*) ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  RangeVarGetRelid (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RemoteTransactionBeginIfNecessary (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RemoveMasterOptions (TYPE_2__*) ; 
 int /*<<< orphan*/  UnclaimConnection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/ * masterConnection ; 

__attribute__((used)) static void
CopyFromWorkerNode(CopyStmt *copyStatement, char *completionTag)
{
	NodeAddress *masterNodeAddress = MasterNodeAddress(copyStatement);
	char *nodeName = masterNodeAddress->nodeName;
	int32 nodePort = masterNodeAddress->nodePort;
	Oid relationId = InvalidOid;
	char partitionMethod = 0;
	char *schemaName = NULL;
	uint32 connectionFlags = FOR_DML;

	masterConnection = GetNodeConnection(connectionFlags, nodeName, nodePort);
	MarkRemoteTransactionCritical(masterConnection);
	ClaimConnectionExclusively(masterConnection);

	RemoteTransactionBeginIfNecessary(masterConnection);

	/* strip schema name for local reference */
	schemaName = copyStatement->relation->schemaname;
	copyStatement->relation->schemaname = NULL;

	relationId = RangeVarGetRelid(copyStatement->relation, NoLock, false);

	/* put schema name back */
	copyStatement->relation->schemaname = schemaName;
	partitionMethod = MasterPartitionMethod(copyStatement->relation);
	if (partitionMethod != DISTRIBUTE_BY_APPEND)
	{
		ereport(ERROR, (errmsg("copy from worker nodes is only supported "
							   "for append-partitioned tables")));
	}

	/*
	 * Remove master node options from the copy statement because they are not
	 * recognized by PostgreSQL machinery.
	 */
	RemoveMasterOptions(copyStatement);

	CopyToNewShards(copyStatement, completionTag, relationId);

	UnclaimConnection(masterConnection);
	masterConnection = NULL;
}