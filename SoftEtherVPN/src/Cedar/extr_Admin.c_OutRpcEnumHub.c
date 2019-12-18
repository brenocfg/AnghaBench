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
struct TYPE_5__ {size_t NumHub; TYPE_1__* Hubs; } ;
struct TYPE_4__ {int /*<<< orphan*/  Traffic; int /*<<< orphan*/  IsTrafficFilled; int /*<<< orphan*/  NumLogin; int /*<<< orphan*/  LastLoginTime; int /*<<< orphan*/  CreatedTime; int /*<<< orphan*/  LastCommTime; int /*<<< orphan*/  NumIpTables; int /*<<< orphan*/  NumMacTables; int /*<<< orphan*/  NumGroups; int /*<<< orphan*/  NumUsers; int /*<<< orphan*/  NumSessions; int /*<<< orphan*/  HubType; int /*<<< orphan*/  Online; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ RPC_ENUM_HUB_ITEM ;
typedef  TYPE_2__ RPC_ENUM_HUB ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  OutRpcTrafficEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddBoolEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddIntEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddTime64Ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackSetCurrentJsonGroupName (int /*<<< orphan*/ *,char*) ; 

void OutRpcEnumHub(PACK *p, RPC_ENUM_HUB *t)
{
	UINT i;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackSetCurrentJsonGroupName(p, "HubList");
	for (i = 0;i < t->NumHub;i++)
	{
		RPC_ENUM_HUB_ITEM *e = &t->Hubs[i];

		PackAddStrEx(p, "HubName", e->HubName, i, t->NumHub);
		PackAddBoolEx(p, "Online", e->Online, i, t->NumHub);
		PackAddIntEx(p, "HubType", e->HubType, i, t->NumHub);
		PackAddIntEx(p, "NumSessions", e->NumSessions, i, t->NumHub);
		PackAddIntEx(p, "NumUsers", e->NumUsers, i, t->NumHub);
		PackAddIntEx(p, "NumGroups", e->NumGroups, i, t->NumHub);
		PackAddIntEx(p, "NumMacTables", e->NumMacTables, i, t->NumHub);
		PackAddIntEx(p, "NumIpTables", e->NumIpTables, i, t->NumHub);
		PackAddTime64Ex(p, "LastCommTime", e->LastCommTime, i, t->NumHub);
		PackAddTime64Ex(p, "CreatedTime", e->CreatedTime, i, t->NumHub);
		PackAddTime64Ex(p, "LastLoginTime", e->LastLoginTime, i, t->NumHub);
		PackAddIntEx(p, "NumLogin", e->NumLogin, i, t->NumHub);
		PackAddBoolEx(p, "IsTrafficFilled", e->IsTrafficFilled, i, t->NumHub);

		OutRpcTrafficEx(&e->Traffic, p, i, t->NumHub);
	}
	PackSetCurrentJsonGroupName(p, NULL);
}