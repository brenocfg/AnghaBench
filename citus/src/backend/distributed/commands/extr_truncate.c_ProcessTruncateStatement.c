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
typedef  int /*<<< orphan*/  TruncateStmt ;

/* Variables and functions */
 int /*<<< orphan*/  EnsurePartitionTableNotReplicatedForTruncate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ErrorIfUnsupportedTruncateStmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecuteTruncateStmtSequentialIfNecessary (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockTruncatedRelationMetadataInWorkers (int /*<<< orphan*/ *) ; 

void
ProcessTruncateStatement(TruncateStmt *truncateStatement)
{
	ErrorIfUnsupportedTruncateStmt(truncateStatement);
	EnsurePartitionTableNotReplicatedForTruncate(truncateStatement);
	ExecuteTruncateStmtSequentialIfNecessary(truncateStatement);
	LockTruncatedRelationMetadataInWorkers(truncateStatement);
}