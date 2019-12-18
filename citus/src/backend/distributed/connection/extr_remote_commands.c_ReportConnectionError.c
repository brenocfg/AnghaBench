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
struct TYPE_3__ {char* hostname; int port; int /*<<< orphan*/ * pgConn; } ;
typedef  int /*<<< orphan*/  PGconn ;
typedef  TYPE_1__ MultiConnection ;

/* Variables and functions */
 int /*<<< orphan*/  ApplyLogRedaction (char*) ; 
 int /*<<< orphan*/  ERRCODE_CONNECTION_FAILURE ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*,int) ; 
 char* pchomp (int /*<<< orphan*/ ) ; 

void
ReportConnectionError(MultiConnection *connection, int elevel)
{
	char *nodeName = connection->hostname;
	int nodePort = connection->port;
	PGconn *pgConn = connection->pgConn;
	char *messageDetail = NULL;

	if (pgConn != NULL)
	{
		messageDetail = pchomp(PQerrorMessage(pgConn));
	}

	ereport(elevel, (errcode(ERRCODE_CONNECTION_FAILURE),
					 errmsg("connection error: %s:%d", nodeName, nodePort),
					 messageDetail != NULL ?
					 errdetail("%s", ApplyLogRedaction(messageDetail)) : 0));
}