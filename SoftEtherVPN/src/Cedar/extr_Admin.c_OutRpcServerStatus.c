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
struct TYPE_3__ {int /*<<< orphan*/  MemInfo; int /*<<< orphan*/  Traffic; int /*<<< orphan*/  StartTime; int /*<<< orphan*/  AssignedClientLicensesTotal; int /*<<< orphan*/  AssignedBridgeLicensesTotal; int /*<<< orphan*/  AssignedClientLicenses; int /*<<< orphan*/  AssignedBridgeLicenses; int /*<<< orphan*/  CurrentTick; int /*<<< orphan*/  CurrentTime; int /*<<< orphan*/  NumGroups; int /*<<< orphan*/  NumUsers; int /*<<< orphan*/  NumIpTables; int /*<<< orphan*/  NumMacTables; int /*<<< orphan*/  NumTcpConnectionsRemote; int /*<<< orphan*/  NumTcpConnectionsLocal; int /*<<< orphan*/  NumTcpConnections; int /*<<< orphan*/  NumSessionsRemote; int /*<<< orphan*/  NumSessionsLocal; int /*<<< orphan*/  NumSessionsTotal; int /*<<< orphan*/  NumHubDynamic; int /*<<< orphan*/  NumHubStatic; int /*<<< orphan*/  NumHubStandalone; int /*<<< orphan*/  NumHubTotal; int /*<<< orphan*/  ServerType; } ;
typedef  TYPE_1__ RPC_SERVER_STATUS ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  OutRpcMemInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OutRpcTraffic (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddInt64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddTime64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void OutRpcServerStatus(PACK *p, RPC_SERVER_STATUS *t)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackAddInt(p, "ServerType", t->ServerType);
	PackAddInt(p, "NumHubTotal", t->NumHubTotal);
	PackAddInt(p, "NumHubStandalone", t->NumHubStandalone);
	PackAddInt(p, "NumHubStatic", t->NumHubStatic);
	PackAddInt(p, "NumHubDynamic", t->NumHubDynamic);
	PackAddInt(p, "NumSessionsTotal", t->NumSessionsTotal);
	PackAddInt(p, "NumSessionsLocal", t->NumSessionsLocal);
	PackAddInt(p, "NumSessionsRemote", t->NumSessionsRemote);
	PackAddInt(p, "NumTcpConnections", t->NumTcpConnections);
	PackAddInt(p, "NumTcpConnectionsLocal", t->NumTcpConnectionsLocal);
	PackAddInt(p, "NumTcpConnectionsRemote", t->NumTcpConnectionsRemote);
	PackAddInt(p, "NumMacTables", t->NumMacTables);
	PackAddInt(p, "NumIpTables", t->NumIpTables);
	PackAddInt(p, "NumUsers", t->NumUsers);
	PackAddInt(p, "NumGroups", t->NumGroups);
	PackAddTime64(p, "CurrentTime", t->CurrentTime);
	PackAddInt64(p, "CurrentTick", t->CurrentTick);
	PackAddInt(p, "AssignedBridgeLicenses", t->AssignedBridgeLicenses);
	PackAddInt(p, "AssignedClientLicenses", t->AssignedClientLicenses);
	PackAddInt(p, "AssignedBridgeLicensesTotal", t->AssignedBridgeLicensesTotal);
	PackAddInt(p, "AssignedClientLicensesTotal", t->AssignedClientLicensesTotal);
	PackAddTime64(p, "StartTime", t->StartTime);

	OutRpcTraffic(p, &t->Traffic);

	OutRpcMemInfo(p, &t->MemInfo);
}