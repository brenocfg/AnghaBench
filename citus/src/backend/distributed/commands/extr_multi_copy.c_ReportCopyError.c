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
struct TYPE_3__ {int /*<<< orphan*/  port; int /*<<< orphan*/  hostname; int /*<<< orphan*/  pgConn; } ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_1__ MultiConnection ;

/* Variables and functions */
 int /*<<< orphan*/  ApplyLogRedaction (char*) ; 
 int /*<<< orphan*/  ERRCODE_IO_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  PG_DIAG_MESSAGE_DETAIL ; 
 int /*<<< orphan*/  PG_DIAG_MESSAGE_PRIMARY ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ ) ; 
 char* PQresultErrorField (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*,...) ; 
 char* pchomp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ReportCopyError(MultiConnection *connection, PGresult *result)
{
	char *remoteMessage = PQresultErrorField(result, PG_DIAG_MESSAGE_PRIMARY);

	if (remoteMessage != NULL)
	{
		/* probably a constraint violation, show remote message and detail */
		char *remoteDetail = PQresultErrorField(result, PG_DIAG_MESSAGE_DETAIL);
		bool haveDetail = remoteDetail != NULL;

		ereport(ERROR, (errmsg("%s", remoteMessage),
						haveDetail ? errdetail("%s", ApplyLogRedaction(remoteDetail)) :
						0));
	}
	else
	{
		/* trim the trailing characters */
		remoteMessage = pchomp(PQerrorMessage(connection->pgConn));

		ereport(ERROR, (errcode(ERRCODE_IO_ERROR),
						errmsg("failed to complete COPY on %s:%d", connection->hostname,
							   connection->port),
						errdetail("%s", ApplyLogRedaction(remoteMessage))));
	}
}