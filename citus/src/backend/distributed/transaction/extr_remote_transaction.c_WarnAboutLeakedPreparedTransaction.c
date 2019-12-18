#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  preparedName; } ;
struct TYPE_9__ {int /*<<< orphan*/  port; int /*<<< orphan*/  hostname; TYPE_2__ remoteTransaction; } ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  TYPE_2__ RemoteTransaction ;
typedef  TYPE_3__ MultiConnection ;

/* Variables and functions */
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  quote_literal_cstr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
WarnAboutLeakedPreparedTransaction(MultiConnection *connection, bool commit)
{
	StringInfoData command;
	RemoteTransaction *transaction = &connection->remoteTransaction;

	initStringInfo(&command);

	if (commit)
	{
		appendStringInfo(&command, "COMMIT PREPARED %s",
						 quote_literal_cstr(transaction->preparedName));
	}
	else
	{
		appendStringInfo(&command, "ROLLBACK PREPARED %s",
						 quote_literal_cstr(transaction->preparedName));
	}

	/* log a warning so the user may abort the transaction later */
	ereport(WARNING, (errmsg("failed to roll back prepared transaction '%s'",
							 transaction->preparedName),
					  errhint("Run \"%s\" on %s:%u",
							  command.data, connection->hostname, connection->port)));
}