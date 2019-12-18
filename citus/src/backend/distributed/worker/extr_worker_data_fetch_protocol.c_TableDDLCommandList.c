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
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* StringInfo ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  MultiConnection ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  CloseConnection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecuteOptionalRemoteCommand (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  FORCE_NEW_CONNECTION ; 
 int /*<<< orphan*/  ForgetResults (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GET_TABLE_DDL_EVENTS ; 
 int /*<<< orphan*/ * GetNodeConnection (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ReadFirstColumnAsText (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__* makeStringInfo () ; 

List *
TableDDLCommandList(const char *nodeName, uint32 nodePort, const char *tableName)
{
	List *ddlCommandList = NIL;
	StringInfo queryString = NULL;
	MultiConnection *connection = NULL;
	PGresult *result = NULL;
	uint32 connectionFlag = FORCE_NEW_CONNECTION;

	queryString = makeStringInfo();
	appendStringInfo(queryString, GET_TABLE_DDL_EVENTS, tableName);
	connection = GetNodeConnection(connectionFlag, nodeName, nodePort);

	ExecuteOptionalRemoteCommand(connection, queryString->data, &result);
	ddlCommandList = ReadFirstColumnAsText(result);

	PQclear(result);
	ForgetResults(connection);
	CloseConnection(connection);

	return ddlCommandList;
}