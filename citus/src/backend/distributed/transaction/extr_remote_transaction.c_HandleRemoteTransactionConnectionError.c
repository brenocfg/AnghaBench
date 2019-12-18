#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int transactionFailed; scalar_t__ transactionCritical; } ;
struct TYPE_6__ {TYPE_1__ remoteTransaction; } ;
typedef  TYPE_1__ RemoteTransaction ;
typedef  TYPE_2__ MultiConnection ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ReportConnectionError (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARNING ; 

void
HandleRemoteTransactionConnectionError(MultiConnection *connection, bool raiseErrors)
{
	RemoteTransaction *transaction = &connection->remoteTransaction;

	transaction->transactionFailed = true;

	if (transaction->transactionCritical && raiseErrors)
	{
		ReportConnectionError(connection, ERROR);
	}
	else
	{
		ReportConnectionError(connection, WARNING);
	}
}