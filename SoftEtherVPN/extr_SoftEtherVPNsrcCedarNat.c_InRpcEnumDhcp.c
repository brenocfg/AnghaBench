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
struct TYPE_7__ {int NumItem; TYPE_1__* Items; int /*<<< orphan*/  HubName; } ;
struct TYPE_6__ {int /*<<< orphan*/  Hostname; void* Mask; int /*<<< orphan*/  IpAddress; int /*<<< orphan*/  MacAddress; void* ExpireTime; void* LeasedTime; void* Id; } ;
typedef  TYPE_1__ RPC_ENUM_DHCP_ITEM ;
typedef  TYPE_2__ RPC_ENUM_DHCP ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackGetDataEx2 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,size_t) ; 
 int PackGetInt (int /*<<< orphan*/ *,char*) ; 
 void* PackGetInt64Ex (int /*<<< orphan*/ *,char*,size_t) ; 
 void* PackGetIntEx (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackGetIp32Ex (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PackGetStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,size_t) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 TYPE_1__* ZeroMalloc (int) ; 

void InRpcEnumDhcp(RPC_ENUM_DHCP *t, PACK *p)
{
	UINT i;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_ENUM_DHCP));
	t->NumItem = PackGetInt(p, "NumItem");
	t->Items = ZeroMalloc(sizeof(RPC_ENUM_DHCP_ITEM) * t->NumItem);
	PackGetStr(p, "HubName", t->HubName, sizeof(t->HubName));

	for (i = 0;i < t->NumItem;i++)
	{
		RPC_ENUM_DHCP_ITEM *e = &t->Items[i];

		e->Id = PackGetIntEx(p, "Id", i);
		e->LeasedTime = PackGetInt64Ex(p, "LeasedTime", i);
		e->ExpireTime = PackGetInt64Ex(p, "ExpireTime", i);
		PackGetDataEx2(p, "MacAddress", e->MacAddress, 6, i);
		e->IpAddress = PackGetIp32Ex(p, "IpAddress", i);
		e->Mask = PackGetIntEx(p, "Mask", i);
		PackGetStrEx(p, "Hostname", e->Hostname, sizeof(e->Hostname), i);
	}
}