#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_7__ {int NumIpTable; TYPE_1__* IpTables; int /*<<< orphan*/  HubName; } ;
struct TYPE_6__ {int /*<<< orphan*/  RemoteHostname; void* RemoteItem; void* UpdatedTime; void* CreatedTime; void* DhcpAllocated; int /*<<< orphan*/  IpAddress; int /*<<< orphan*/  Ip; int /*<<< orphan*/  IpV6; int /*<<< orphan*/  SessionName; int /*<<< orphan*/  Key; } ;
typedef  TYPE_1__ RPC_ENUM_IP_TABLE_ITEM ;
typedef  TYPE_2__ RPC_ENUM_IP_TABLE ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 void* PackGetBoolEx (int /*<<< orphan*/ *,char*,size_t) ; 
 int PackGetIndexCount (int /*<<< orphan*/ *,char*) ; 
 void* PackGetInt64Ex (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackGetIntEx (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackGetIp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackGetIp32Ex (int /*<<< orphan*/ *,char*,size_t) ; 
 int PackGetIpEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PackGetStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,size_t) ; 
 int /*<<< orphan*/  UINTToIP (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 TYPE_1__* ZeroMalloc (int) ; 

void InRpcEnumIpTable(RPC_ENUM_IP_TABLE *t, PACK *p)
{
	UINT i;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_ENUM_IP_TABLE));
	PackGetStr(p, "HubName", t->HubName, sizeof(t->HubName));
	t->NumIpTable = PackGetIndexCount(p, "SessionName");
	t->IpTables = ZeroMalloc(sizeof(RPC_ENUM_IP_TABLE_ITEM) * t->NumIpTable);

	for (i = 0;i < t->NumIpTable;i++)
	{
		RPC_ENUM_IP_TABLE_ITEM *e = &t->IpTables[i];

		e->Key = PackGetIntEx(p, "Key", i);
		PackGetStrEx(p, "SessionName", e->SessionName, sizeof(e->SessionName), i);
		e->Ip = PackGetIp32Ex(p, "Ip", i);
		if (PackGetIpEx(p, "IpV6", &e->IpV6, i) == false)
		{
			UINTToIP(&e->IpV6, e->Ip);
		}
		PackGetIp(p, "IpAddress", &e->IpAddress);
		e->DhcpAllocated = PackGetBoolEx(p, "DhcpAllocated", i);
		e->CreatedTime = PackGetInt64Ex(p, "CreatedTime", i);
		e->UpdatedTime = PackGetInt64Ex(p, "UpdatedTime", i);
		e->RemoteItem = PackGetBoolEx(p, "RemoteItem", i);
		PackGetStrEx(p, "RemoteHostname", e->RemoteHostname, sizeof(e->RemoteHostname), i);
	}
}