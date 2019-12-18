#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* relname; char* schemaname; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* StringInfo ;
typedef  TYPE_2__ RangeVar ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * GetRemoteCommandResult (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PARTITION_METHOD_QUERY ; 
 scalar_t__ PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReportConnectionError (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReportResultError (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendRemoteCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 TYPE_1__* makeStringInfo () ; 
 int /*<<< orphan*/  masterConnection ; 
 char* quote_qualified_identifier (char*,char*) ; 

__attribute__((used)) static char
MasterPartitionMethod(RangeVar *relation)
{
	char partitionMethod = '\0';
	PGresult *queryResult = NULL;
	bool raiseInterrupts = true;

	char *relationName = relation->relname;
	char *schemaName = relation->schemaname;
	char *qualifiedName = quote_qualified_identifier(schemaName, relationName);

	StringInfo partitionMethodCommand = makeStringInfo();
	appendStringInfo(partitionMethodCommand, PARTITION_METHOD_QUERY, qualifiedName);

	if (!SendRemoteCommand(masterConnection, partitionMethodCommand->data))
	{
		ReportConnectionError(masterConnection, ERROR);
	}
	queryResult = GetRemoteCommandResult(masterConnection, raiseInterrupts);
	if (PQresultStatus(queryResult) == PGRES_TUPLES_OK)
	{
		char *partitionMethodString = PQgetvalue((PGresult *) queryResult, 0, 0);
		if (partitionMethodString == NULL || (*partitionMethodString) == '\0')
		{
			ereport(ERROR, (errmsg("could not find a partition method for the "
								   "table %s", relationName)));
		}

		partitionMethod = partitionMethodString[0];
	}
	else
	{
		ReportResultError(masterConnection, queryResult, WARNING);
		ereport(ERROR, (errmsg("could not get the partition method of the "
							   "distributed table")));
	}

	PQclear(queryResult);

	queryResult = GetRemoteCommandResult(masterConnection, raiseInterrupts);
	Assert(!queryResult);

	return partitionMethod;
}