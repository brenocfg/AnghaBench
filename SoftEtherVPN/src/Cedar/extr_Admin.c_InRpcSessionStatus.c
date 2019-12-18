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
struct TYPE_4__ {int /*<<< orphan*/  NodeInfo; int /*<<< orphan*/  Status; int /*<<< orphan*/  ClientIpAddress; int /*<<< orphan*/  ClientHostName; int /*<<< orphan*/  ClientIp6; int /*<<< orphan*/  ClientIp; int /*<<< orphan*/  RealUsername; int /*<<< orphan*/  GroupName; int /*<<< orphan*/  Username; int /*<<< orphan*/  Name; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ RPC_SESSION_STATUS ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  InRpcClientGetConnectionStatus (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcNodeInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackGetData2 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PackGetIp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackGetIp32 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void InRpcSessionStatus(RPC_SESSION_STATUS *t, PACK *p)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_SESSION_STATUS));
	PackGetStr(p, "HubName", t->HubName, sizeof(t->HubName));
	PackGetStr(p, "Name", t->Name, sizeof(t->Name));
	PackGetStr(p, "Username", t->Username, sizeof(t->Username));
	PackGetStr(p, "GroupName", t->GroupName, sizeof(t->GroupName));
	PackGetStr(p, "RealUsername", t->RealUsername, sizeof(t->RealUsername));
	t->ClientIp = PackGetIp32(p, "SessionStatus_ClientIp");
	PackGetData2(p, "SessionStatus_ClientIp6", t->ClientIp6, sizeof(t->ClientIp6));
	PackGetStr(p, "SessionStatus_ClientHostName", t->ClientHostName, sizeof(t->ClientHostName));
	PackGetIp(p, "Client_Ip_Address", &t->ClientIpAddress);

	InRpcClientGetConnectionStatus(&t->Status, p);
	InRpcNodeInfo(&t->NodeInfo, p);
}