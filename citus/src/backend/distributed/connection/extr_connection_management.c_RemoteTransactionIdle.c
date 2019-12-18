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
struct TYPE_3__ {int /*<<< orphan*/  pgConn; } ;
typedef  TYPE_1__ MultiConnection ;

/* Variables and functions */
 scalar_t__ AllowNonIdleTransactionOnXactHandling () ; 
 scalar_t__ PQTRANS_IDLE ; 
 scalar_t__ PQtransactionStatus (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
RemoteTransactionIdle(MultiConnection *connection)
{
	/*
	 * This is a very special case where we're running isolation tests on MX.
	 * We don't care whether the transaction is idle or not when we're
	 * running MX isolation tests. Thus, let the caller act as if the remote
	 * transactions is idle.
	 */
	if (AllowNonIdleTransactionOnXactHandling())
	{
		return true;
	}

	return PQtransactionStatus(connection->pgConn) == PQTRANS_IDLE;
}