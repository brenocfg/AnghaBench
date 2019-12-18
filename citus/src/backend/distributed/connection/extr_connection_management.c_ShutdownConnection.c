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
struct TYPE_4__ {int /*<<< orphan*/ * pgConn; } ;
typedef  TYPE_1__ MultiConnection ;

/* Variables and functions */
 scalar_t__ CONNECTION_OK ; 
 scalar_t__ PQTRANS_ACTIVE ; 
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ *) ; 
 scalar_t__ PQstatus (int /*<<< orphan*/ *) ; 
 scalar_t__ PQtransactionStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SendCancelationRequest (TYPE_1__*) ; 

void
ShutdownConnection(MultiConnection *connection)
{
	/*
	 * Only cancel statement if there's currently one running, and the
	 * connection is in an OK state.
	 */
	if (PQstatus(connection->pgConn) == CONNECTION_OK &&
		PQtransactionStatus(connection->pgConn) == PQTRANS_ACTIVE)
	{
		SendCancelationRequest(connection);
	}
	PQfinish(connection->pgConn);
	connection->pgConn = NULL;
}