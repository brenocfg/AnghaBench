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
struct TYPE_4__ {int /*<<< orphan*/  HubName; void* IsRawIpMode; void* IsKernelMode; void* NumDhcpClients; void* NumDnsSessions; void* NumIcmpSessions; void* NumUdpSessions; void* NumTcpSessions; } ;
typedef  TYPE_1__ RPC_NAT_STATUS ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 void* PackGetBool (int /*<<< orphan*/ *,char*) ; 
 void* PackGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void InRpcNatStatus(RPC_NAT_STATUS *t, PACK *p)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_NAT_STATUS));
	t->NumTcpSessions = PackGetInt(p, "NumTcpSessions");
	t->NumUdpSessions = PackGetInt(p, "NumUdpSessions");
	t->NumIcmpSessions = PackGetInt(p, "NumIcmpSessions");
	t->NumDnsSessions = PackGetInt(p, "NumDnsSessions");
	t->NumDhcpClients = PackGetInt(p, "NumDhcpClients");
	t->IsKernelMode = PackGetBool(p, "IsKernelMode");
	t->IsRawIpMode = PackGetBool(p, "IsRawIpMode");
	PackGetStr(p, "HubName", t->HubName, sizeof(t->HubName));
}