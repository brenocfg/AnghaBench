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
struct TYPE_4__ {int skipIfNewValExists; } ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ AlterEnumStmt ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_WORKERS ; 
 scalar_t__ AlterEnumIsAddValue (TYPE_1__*) ; 
 int /*<<< orphan*/  DISABLE_DDL_PROPAGATION ; 
 char* DeparseTreeNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetObjectAddressFromParseTree (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * NIL ; 
 int RESPONSE_OKAY ; 
 int SendBareOptionalCommandListToWorkersAsUser (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ShouldPropagateAlterType (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,char const*) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/ * list_make2 (int /*<<< orphan*/ ,void*) ; 

void
ProcessAlterEnumStmt(AlterEnumStmt *stmt, const char *queryString)
{
	const ObjectAddress *typeAddress = NULL;

	typeAddress = GetObjectAddressFromParseTree((Node *) stmt, false);
	if (!ShouldPropagateAlterType(typeAddress))
	{
		return;
	}

	/*
	 * Before pg12 ALTER ENUM ... ADD VALUE could not be within a xact block. Normally we
	 * would propagate the statements in a xact block to perform 2pc on changes via ddl.
	 * Instead we need to connect directly to the workers here and execute the command.
	 *
	 * From pg12 and up we use the normal infrastructure and create the ddl jobs during
	 * planning.
	 */
#if PG_VERSION_NUM < 120000
	if (AlterEnumIsAddValue(stmt))
	{
		/*
		 * ADD VALUE can't be executed in a transaction, we will execute optimistically
		 * and on an error we will advise to fix the issue with the worker and rerun the
		 * query with the IF NOT EXTISTS modifier. The modifier is needed as the value
		 * might already be added to some nodes, but not all.
		 */

		int result = 0;
		List *commands = NIL;
		const char *alterEnumStmtSql = NULL;

		/* qualification of the stmt happened during planning */
		alterEnumStmtSql = DeparseTreeNode((Node *) stmt);

		commands = list_make2(DISABLE_DDL_PROPAGATION, (void *) alterEnumStmtSql);

		result = SendBareOptionalCommandListToWorkersAsUser(ALL_WORKERS, commands, NULL);

		if (result != RESPONSE_OKAY)
		{
			const char *alterEnumStmtIfNotExistsSql = NULL;
			bool oldSkipIfNewValueExists = stmt->skipIfNewValExists;

			/* deparse the query with IF NOT EXISTS */
			stmt->skipIfNewValExists = true;
			alterEnumStmtIfNotExistsSql = DeparseTreeNode((Node *) stmt);
			stmt->skipIfNewValExists = oldSkipIfNewValueExists;

			ereport(WARNING, (errmsg("not all workers applied change to enum"),
							  errdetail("retry with: %s", alterEnumStmtIfNotExistsSql),
							  errhint("make sure the coordinators can communicate with "
									  "all workers")));
		}
	}
#endif
}