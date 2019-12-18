#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  SubTransactionId ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  MultiConnection ;

/* Variables and functions */
 int /*<<< orphan*/  ForgetResults (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetRemoteCommandResult (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  HandleRemoteTransactionResultError (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  IsResponseOK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
FinishRemoteTransactionSavepointBegin(MultiConnection *connection, SubTransactionId subId)
{
	const bool raiseErrors = true;
	PGresult *result = GetRemoteCommandResult(connection, raiseErrors);
	if (!IsResponseOK(result))
	{
		HandleRemoteTransactionResultError(connection, result, raiseErrors);
	}

	PQclear(result);
	ForgetResults(connection);
}