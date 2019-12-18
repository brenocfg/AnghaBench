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
typedef  int /*<<< orphan*/  uint ;
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  MultiConnection ;

/* Variables and functions */
 int /*<<< orphan*/  BeginOrContinueCoordinatedTransaction () ; 
 int /*<<< orphan*/  CoordinatedTransactionUse2PC () ; 
 int /*<<< orphan*/  ExecuteCriticalRemoteCommand (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * GetNodeUserDatabaseConnection (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MarkRemoteTransactionCritical (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RemoteTransactionBeginIfNecessary (int /*<<< orphan*/ *) ; 

void
SendCommandToWorkerAsUser(char *nodeName, int32 nodePort, const char *nodeUser,
						  const char *command)
{
	MultiConnection *transactionConnection = NULL;
	uint connectionFlags = 0;

	BeginOrContinueCoordinatedTransaction();
	CoordinatedTransactionUse2PC();

	transactionConnection = GetNodeUserDatabaseConnection(connectionFlags, nodeName,
														  nodePort, nodeUser, NULL);

	MarkRemoteTransactionCritical(transactionConnection);
	RemoteTransactionBeginIfNecessary(transactionConnection);
	ExecuteCriticalRemoteCommand(transactionConnection, command);
}