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
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int HasForeignKeyToReferenceTable (int /*<<< orphan*/ ) ; 
 scalar_t__ IsMultiStatementTransaction () ; 
 scalar_t__ MultiShardConnectionType ; 
 scalar_t__ ParallelQueryExecutedInTransaction () ; 
 scalar_t__ SEQUENTIAL_CONNECTION ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 char* get_rel_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
CanUseExclusiveConnections(Oid relationId, bool localTableEmpty)
{
	bool hasForeignKeyToReferenceTable = HasForeignKeyToReferenceTable(relationId);
	bool shouldRunSequential = MultiShardConnectionType == SEQUENTIAL_CONNECTION ||
							   hasForeignKeyToReferenceTable;

	if (!localTableEmpty && shouldRunSequential)
	{
		char *relationName = get_rel_name(relationId);

		ereport(ERROR, (errmsg("cannot distribute \"%s\" in sequential mode "
							   "because it is not empty", relationName),
						errhint("If you have manually set "
								"citus.multi_shard_modify_mode to 'sequential', "
								"try with 'parallel' option. If that is not the "
								"case, try distributing local tables when they "
								"are empty.")));
	}
	else if (shouldRunSequential && ParallelQueryExecutedInTransaction())
	{
		char *relationName = get_rel_name(relationId);

		/*
		 * If there has already been a parallel query executed, the sequential mode
		 * would still use the already opened parallel connections to the workers,
		 * thus contradicting our purpose of using sequential mode.
		 */
		ereport(ERROR, (errmsg("cannot distribute relation \"%s\" in this "
							   "transaction because it has a foreign key to "
							   "a reference table", relationName),
						errdetail("If a hash distributed table has a foreign key "
								  "to a reference table, it has to be created "
								  "in sequential mode before any parallel commands "
								  "have been executed in the same transaction"),
						errhint("Try re-running the transaction with "
								"\"SET LOCAL citus.multi_shard_modify_mode TO "
								"\'sequential\';\"")));
	}
	else if (shouldRunSequential)
	{
		return false;
	}
	else if (!localTableEmpty || IsMultiStatementTransaction())
	{
		return true;
	}

	return false;
}