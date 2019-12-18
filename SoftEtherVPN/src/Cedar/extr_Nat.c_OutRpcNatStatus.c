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
struct TYPE_3__ {int /*<<< orphan*/  IsRawIpMode; int /*<<< orphan*/  IsKernelMode; int /*<<< orphan*/  NumDhcpClients; int /*<<< orphan*/  NumDnsSessions; int /*<<< orphan*/  NumIcmpSessions; int /*<<< orphan*/  NumUdpSessions; int /*<<< orphan*/  NumTcpSessions; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ RPC_NAT_STATUS ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddBool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void OutRpcNatStatus(PACK *p, RPC_NAT_STATUS *t)
{
	// Validate arguments
	if (p == NULL || t == NULL)
	{
		return;
	}

	PackAddStr(p, "HubName", t->HubName);
	PackAddInt(p, "NumTcpSessions", t->NumTcpSessions);
	PackAddInt(p, "NumUdpSessions", t->NumUdpSessions);
	PackAddInt(p, "NumIcmpSessions", t->NumIcmpSessions);
	PackAddInt(p, "NumDnsSessions", t->NumDnsSessions);
	PackAddInt(p, "NumDhcpClients", t->NumDhcpClients);
	PackAddBool(p, "IsKernelMode", t->IsKernelMode);
	PackAddBool(p, "IsRawIpMode", t->IsRawIpMode);
}