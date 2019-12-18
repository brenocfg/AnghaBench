#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_14__ {int /*<<< orphan*/  pgConn; } ;
struct TYPE_13__ {scalar_t__ partitionMethod; } ;
typedef  int /*<<< orphan*/  ShardPlacementAccess ;
typedef  TYPE_1__ ShardPlacement ;
typedef  TYPE_2__ MultiConnection ;

/* Variables and functions */
 scalar_t__ CONNECTION_OK ; 
 int /*<<< orphan*/  CONNECTION_PER_PLACEMENT ; 
 int /*<<< orphan*/  ClaimConnectionExclusively (TYPE_2__*) ; 
 int /*<<< orphan*/ * CreatePlacementAccess (TYPE_1__*,int /*<<< orphan*/ ) ; 
 char* CurrentUserName () ; 
 scalar_t__ DISTRIBUTE_BY_HASH ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FOR_DML ; 
 TYPE_2__* GetConnectionIfPlacementAccessedInXact (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* GetPlacementConnection (int /*<<< orphan*/ ,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  HandleRemoteTransactionConnectionError (TYPE_2__*,int const) ; 
 int /*<<< orphan*/  MarkRemoteTransactionCritical (TYPE_2__*) ; 
 scalar_t__ MultiShardConnectionType ; 
 int /*<<< orphan*/  PLACEMENT_ACCESS_DML ; 
 scalar_t__ PQstatus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReportConnectionError (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ SEQUENTIAL_CONNECTION ; 
 int /*<<< orphan*/  list_make1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static MultiConnection *
CopyGetPlacementConnection(ShardPlacement *placement, bool stopOnFailure)
{
	MultiConnection *connection = NULL;
	uint32 connectionFlags = FOR_DML;
	char *nodeUser = CurrentUserName();
	ShardPlacementAccess *placementAccess = NULL;

	/*
	 * Determine whether the task has to be assigned to a particular connection
	 * due to a preceding access to the placement in the same transaction.
	 */
	placementAccess = CreatePlacementAccess(placement, PLACEMENT_ACCESS_DML);
	connection = GetConnectionIfPlacementAccessedInXact(connectionFlags,
														list_make1(placementAccess),
														NULL);
	if (connection != NULL)
	{
		return connection;
	}

	/*
	 * For placements that haven't been assigned a connection by a previous command
	 * in the current transaction, we use a separate connection per placement for
	 * hash-distributed tables in order to get the maximum performance.
	 */
	if (placement->partitionMethod == DISTRIBUTE_BY_HASH &&
		MultiShardConnectionType != SEQUENTIAL_CONNECTION)
	{
		connectionFlags |= CONNECTION_PER_PLACEMENT;
	}

	connection = GetPlacementConnection(connectionFlags, placement, nodeUser);

	if (PQstatus(connection->pgConn) != CONNECTION_OK)
	{
		if (stopOnFailure)
		{
			ReportConnectionError(connection, ERROR);
		}
		else
		{
			const bool raiseErrors = true;

			HandleRemoteTransactionConnectionError(connection, raiseErrors);

			return NULL;
		}
	}

	/*
	 * Errors are supposed to cause immediate aborts (i.e. we don't
	 * want to/can't invalidate placements), mark the connection as
	 * critical so later errors cause failures.
	 */
	MarkRemoteTransactionCritical(connection);

	if (MultiShardConnectionType != SEQUENTIAL_CONNECTION)
	{
		ClaimConnectionExclusively(connection);
	}

	return connection;
}