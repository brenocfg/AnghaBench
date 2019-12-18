#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int transactionFailed; scalar_t__ transactionCritical; } ;
struct TYPE_5__ {int /*<<< orphan*/  port; int /*<<< orphan*/  hostname; TYPE_1__ remoteTransaction; } ;
typedef  TYPE_1__ RemoteTransaction ;
typedef  TYPE_2__ MultiConnection ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
MarkRemoteTransactionFailed(MultiConnection *connection, bool allowErrorPromotion)
{
	RemoteTransaction *transaction = &connection->remoteTransaction;

	transaction->transactionFailed = true;

	/*
	 * If the connection is marked as critical, fail the entire coordinated
	 * transaction. If allowed.
	 */
	if (transaction->transactionCritical && allowErrorPromotion)
	{
		ereport(ERROR, (errmsg("failure on connection marked as essential: %s:%d",
							   connection->hostname, connection->port)));
	}
}