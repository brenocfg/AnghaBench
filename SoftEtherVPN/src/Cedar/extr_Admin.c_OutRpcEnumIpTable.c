#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_5__ {size_t NumIpTable; TYPE_1__* IpTables; int /*<<< orphan*/  HubName; } ;
struct TYPE_4__ {int /*<<< orphan*/  RemoteHostname; int /*<<< orphan*/  RemoteItem; int /*<<< orphan*/  UpdatedTime; int /*<<< orphan*/  CreatedTime; int /*<<< orphan*/  DhcpAllocated; int /*<<< orphan*/  IpAddress; int /*<<< orphan*/  IpV6; int /*<<< orphan*/  Ip; int /*<<< orphan*/  SessionName; int /*<<< orphan*/  Key; } ;
typedef  TYPE_1__ RPC_ENUM_IP_TABLE_ITEM ;
typedef  TYPE_2__ RPC_ENUM_IP_TABLE ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddBoolEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddIntEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddIp32Ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddIpEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddTime64Ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackSetCurrentJsonGroupName (int /*<<< orphan*/ *,char*) ; 

void OutRpcEnumIpTable(PACK *p, RPC_ENUM_IP_TABLE *t)
{
	UINT i;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackAddStr(p, "HubName", t->HubName);

	PackSetCurrentJsonGroupName(p, "IpTable");
	for (i = 0;i < t->NumIpTable;i++)
	{
		RPC_ENUM_IP_TABLE_ITEM *e = &t->IpTables[i];

		PackAddIntEx(p, "Key", e->Key, i, t->NumIpTable);
		PackAddStrEx(p, "SessionName", e->SessionName, i, t->NumIpTable);
		PackAddIp32Ex(p, "Ip", e->Ip, i, t->NumIpTable);
		PackAddIpEx(p, "IpV6", &e->IpV6, i, t->NumIpTable);
		PackAddIpEx(p, "IpAddress", &e->IpAddress, i, t->NumIpTable);
		PackAddBoolEx(p, "DhcpAllocated", e->DhcpAllocated, i, t->NumIpTable);
		PackAddTime64Ex(p, "CreatedTime", e->CreatedTime, i, t->NumIpTable);
		PackAddTime64Ex(p, "UpdatedTime", e->UpdatedTime, i, t->NumIpTable);
		PackAddBoolEx(p, "RemoteItem", e->RemoteItem, i, t->NumIpTable);
		PackAddStrEx(p, "RemoteHostname", e->RemoteHostname, i, t->NumIpTable);
	}
	PackSetCurrentJsonGroupName(p, NULL);
}