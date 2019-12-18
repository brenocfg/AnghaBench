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
struct TYPE_5__ {size_t NumItem; TYPE_1__* Items; int /*<<< orphan*/  HubName; } ;
struct TYPE_4__ {int /*<<< orphan*/  Hostname; int /*<<< orphan*/  Mask; int /*<<< orphan*/  IpAddress; int /*<<< orphan*/  MacAddress; int /*<<< orphan*/  ExpireTime; int /*<<< orphan*/  LeasedTime; int /*<<< orphan*/  Id; } ;
typedef  TYPE_1__ RPC_ENUM_DHCP_ITEM ;
typedef  TYPE_2__ RPC_ENUM_DHCP ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddDataEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackAddIntEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddIp32Ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddTime64Ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackSetCurrentJsonGroupName (int /*<<< orphan*/ *,char*) ; 

void OutRpcEnumDhcp(PACK *p, RPC_ENUM_DHCP *t)
{
	UINT i;
	// Validate arguments
	if (p == NULL || t == NULL)
	{
		return;
	}

	PackAddInt(p, "NumItem", t->NumItem);
	PackAddStr(p, "HubName", t->HubName);

	PackSetCurrentJsonGroupName(p, "DhcpTable");
	for (i = 0;i < t->NumItem;i++)
	{
		RPC_ENUM_DHCP_ITEM *e = &t->Items[i];

		PackAddIntEx(p, "Id", e->Id, i, t->NumItem);
		PackAddTime64Ex(p, "LeasedTime", e->LeasedTime, i, t->NumItem);
		PackAddTime64Ex(p, "ExpireTime", e->ExpireTime, i, t->NumItem);
		PackAddDataEx(p, "MacAddress", e->MacAddress, 6, i, t->NumItem);
		PackAddIp32Ex(p, "IpAddress", e->IpAddress, i, t->NumItem);
		PackAddIntEx(p, "Mask", e->Mask, i, t->NumItem);
		PackAddStrEx(p, "Hostname", e->Hostname, i, t->NumItem);
	}
	PackSetCurrentJsonGroupName(p, NULL);
}