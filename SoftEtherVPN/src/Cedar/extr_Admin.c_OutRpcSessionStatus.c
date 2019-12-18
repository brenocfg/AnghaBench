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
struct TYPE_3__ {int /*<<< orphan*/  NodeInfo; int /*<<< orphan*/  Status; int /*<<< orphan*/  ClientIpAddress; int /*<<< orphan*/  ClientHostName; int /*<<< orphan*/  ClientIp6; int /*<<< orphan*/  ClientIp; int /*<<< orphan*/  RealUsername; int /*<<< orphan*/  GroupName; int /*<<< orphan*/  Username; int /*<<< orphan*/  Name; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ RPC_SESSION_STATUS ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  OutRpcClientGetConnectionStatus (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OutRpcNodeInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackAddData (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PackAddIp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackAddIp32 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void OutRpcSessionStatus(PACK *p, RPC_SESSION_STATUS *t)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackAddStr(p, "HubName", t->HubName);
	PackAddStr(p, "Name", t->Name);
	PackAddStr(p, "Username", t->Username);
	PackAddStr(p, "GroupName", t->GroupName);
	PackAddStr(p, "RealUsername", t->RealUsername);
	PackAddIp32(p, "SessionStatus_ClientIp", t->ClientIp);
	PackAddData(p, "SessionStatus_ClientIp6", t->ClientIp6, sizeof(t->ClientIp6));
	PackAddStr(p, "SessionStatus_ClientHostName", t->ClientHostName);
	PackAddIp(p, "Client_Ip_Address", &t->ClientIpAddress);

	OutRpcClientGetConnectionStatus(p, &t->Status);
	OutRpcNodeInfo(p, &t->NodeInfo);
}