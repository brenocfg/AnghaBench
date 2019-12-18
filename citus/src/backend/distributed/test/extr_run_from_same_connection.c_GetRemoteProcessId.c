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
typedef  int int64 ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* StringInfo ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  ClearResults (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ExecuteOptionalRemoteCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GET_PROCESS_ID ; 
 int /*<<< orphan*/  PG_RETURN_VOID () ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int ParseIntField (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* makeStringInfo () ; 
 int /*<<< orphan*/  singleConnection ; 

__attribute__((used)) static int64
GetRemoteProcessId()
{
	StringInfo queryStringInfo = makeStringInfo();
	PGresult *result = NULL;
	int64 rowCount = 0;
	int64 resultValue = 0;

	appendStringInfo(queryStringInfo, GET_PROCESS_ID);

	ExecuteOptionalRemoteCommand(singleConnection, queryStringInfo->data, &result);

	rowCount = PQntuples(result);

	if (rowCount != 1)
	{
		PG_RETURN_VOID();
	}

	resultValue = ParseIntField(result, 0, 0);

	PQclear(result);
	ClearResults(singleConnection, false);

	return resultValue;
}