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
struct TYPE_3__ {char* hostname; int port; int /*<<< orphan*/  pgConn; } ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_1__ MultiConnection ;

/* Variables and functions */
 int /*<<< orphan*/  ApplyLogRedaction (char*) ; 
 int ERRCODE_INTERNAL_ERROR ; 
 int MAKE_SQLSTATE (char,char,char,char,char) ; 
 int /*<<< orphan*/  PG_CATCH () ; 
 int /*<<< orphan*/  PG_DIAG_CONTEXT ; 
 int /*<<< orphan*/  PG_DIAG_MESSAGE_DETAIL ; 
 int /*<<< orphan*/  PG_DIAG_MESSAGE_HINT ; 
 int /*<<< orphan*/  PG_DIAG_MESSAGE_PRIMARY ; 
 int /*<<< orphan*/  PG_DIAG_SQLSTATE ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_RE_THROW () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ ) ; 
 char* PQresultErrorField (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int) ; 
 int /*<<< orphan*/  errcontext (char*,char*,...) ; 
 int /*<<< orphan*/  errdetail (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*,char*) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 char* pchomp (int /*<<< orphan*/ ) ; 

void
ReportResultError(MultiConnection *connection, PGresult *result, int elevel)
{
	/* we release PQresult when throwing an error because the caller can't */
	PG_TRY();
	{
		char *sqlStateString = PQresultErrorField(result, PG_DIAG_SQLSTATE);
		char *messagePrimary = PQresultErrorField(result, PG_DIAG_MESSAGE_PRIMARY);
		char *messageDetail = PQresultErrorField(result, PG_DIAG_MESSAGE_DETAIL);
		char *messageHint = PQresultErrorField(result, PG_DIAG_MESSAGE_HINT);
		char *messageContext = PQresultErrorField(result, PG_DIAG_CONTEXT);

		char *nodeName = connection->hostname;
		int nodePort = connection->port;
		int sqlState = ERRCODE_INTERNAL_ERROR;

		if (sqlStateString != NULL)
		{
			sqlState = MAKE_SQLSTATE(sqlStateString[0],
									 sqlStateString[1],
									 sqlStateString[2],
									 sqlStateString[3],
									 sqlStateString[4]);
		}

		/*
		 * If the PGresult did not contain a message, the connection may provide a
		 * suitable top level one. At worst, this is an empty string.
		 */
		if (messagePrimary == NULL)
		{
			messagePrimary = pchomp(PQerrorMessage(connection->pgConn));
		}

		ereport(elevel, (errcode(sqlState), errmsg("%s", messagePrimary),
						 messageDetail ?
						 errdetail("%s", ApplyLogRedaction(messageDetail)) : 0,
						 messageHint ? errhint("%s", messageHint) : 0,
						 messageContext ? errcontext("%s", messageContext) : 0,
						 errcontext("while executing command on %s:%d",
									nodeName, nodePort)));
	}
	PG_CATCH();
	{
		PQclear(result);
		PG_RE_THROW();
	}
	PG_END_TRY();
}