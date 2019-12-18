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
struct TYPE_4__ {int /*<<< orphan*/  MemInfo; int /*<<< orphan*/  Traffic; void* StartTime; void* AssignedClientLicensesTotal; void* AssignedBridgeLicensesTotal; void* AssignedClientLicenses; void* AssignedBridgeLicenses; void* CurrentTick; void* CurrentTime; void* NumGroups; void* NumUsers; void* NumIpTables; void* NumMacTables; void* NumSessionsRemote; void* NumSessionsLocal; void* NumSessionsTotal; void* NumHubDynamic; void* NumHubStatic; void* NumHubStandalone; void* NumHubTotal; void* NumTcpConnectionsRemote; void* NumTcpConnectionsLocal; void* NumTcpConnections; void* ServerType; } ;
typedef  TYPE_1__ RPC_SERVER_STATUS ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  InRpcMemInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcTraffic (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* PackGetInt (int /*<<< orphan*/ *,char*) ; 
 void* PackGetInt64 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void InRpcServerStatus(RPC_SERVER_STATUS *t, PACK *p)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_SERVER_STATUS));
	t->ServerType = PackGetInt(p, "ServerType");
	t->NumTcpConnections = PackGetInt(p, "NumTcpConnections");
	t->NumTcpConnectionsLocal = PackGetInt(p, "NumTcpConnectionsLocal");
	t->NumTcpConnectionsRemote = PackGetInt(p, "NumTcpConnectionsRemote");
	t->NumHubTotal = PackGetInt(p, "NumHubTotal");
	t->NumHubStandalone = PackGetInt(p, "NumHubStandalone");
	t->NumHubStatic = PackGetInt(p, "NumHubStatic");
	t->NumHubDynamic = PackGetInt(p, "NumHubDynamic");
	t->NumSessionsTotal = PackGetInt(p, "NumSessionsTotal");
	t->NumSessionsLocal = PackGetInt(p, "NumSessionsLocal");
	t->NumSessionsRemote = PackGetInt(p, "NumSessionsRemote");
	t->NumMacTables = PackGetInt(p, "NumMacTables");
	t->NumIpTables = PackGetInt(p, "NumIpTables");
	t->NumUsers = PackGetInt(p, "NumUsers");
	t->NumGroups = PackGetInt(p, "NumGroups");
	t->CurrentTime = PackGetInt64(p, "CurrentTime");
	t->CurrentTick = PackGetInt64(p, "CurrentTick");
	t->AssignedBridgeLicenses = PackGetInt(p, "AssignedBridgeLicenses");
	t->AssignedClientLicenses = PackGetInt(p, "AssignedClientLicenses");
	t->AssignedBridgeLicensesTotal = PackGetInt(p, "AssignedBridgeLicensesTotal");
	t->AssignedClientLicensesTotal = PackGetInt(p, "AssignedClientLicensesTotal");
	t->StartTime = PackGetInt64(p, "StartTime");

	InRpcTraffic(&t->Traffic, p);

	InRpcMemInfo(&t->MemInfo, p);
}