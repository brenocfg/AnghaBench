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
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  SubTransactionId ;
typedef  TYPE_1__* StringInfo ;
typedef  int /*<<< orphan*/  MultiConnection ;

/* Variables and functions */
 int /*<<< orphan*/  HandleRemoteTransactionConnectionError (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  SendRemoteCommand (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* makeStringInfo () ; 

__attribute__((used)) static void
StartRemoteTransactionSavepointRollback(MultiConnection *connection,
										SubTransactionId subId)
{
	const bool raiseErrors = false;
	StringInfo savepointCommand = makeStringInfo();
	appendStringInfo(savepointCommand, "ROLLBACK TO SAVEPOINT savepoint_%u", subId);

	if (!SendRemoteCommand(connection, savepointCommand->data))
	{
		HandleRemoteTransactionConnectionError(connection, raiseErrors);
	}
}