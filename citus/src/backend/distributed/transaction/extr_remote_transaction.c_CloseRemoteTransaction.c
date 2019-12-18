#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ transactionState; } ;
struct MultiConnection {int /*<<< orphan*/  transactionNode; TYPE_1__ remoteTransaction; } ;
typedef  TYPE_1__ RemoteTransaction ;

/* Variables and functions */
 scalar_t__ REMOTE_TRANS_INVALID ; 
 int /*<<< orphan*/  dlist_delete (int /*<<< orphan*/ *) ; 

void
CloseRemoteTransaction(struct MultiConnection *connection)
{
	RemoteTransaction *transaction = &connection->remoteTransaction;

	/* unlink from list of open transactions, if necessary */
	if (transaction->transactionState != REMOTE_TRANS_INVALID)
	{
		/* XXX: Should we error out for a critical transaction? */

		dlist_delete(&connection->transactionNode);
	}
}