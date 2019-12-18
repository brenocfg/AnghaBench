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
struct TYPE_7__ {int NumHub; TYPE_1__* Hubs; } ;
struct TYPE_6__ {int /*<<< orphan*/  Traffic; void* IsTrafficFilled; void* NumLogin; void* LastLoginTime; void* CreatedTime; void* LastCommTime; void* NumIpTables; void* NumMacTables; void* NumGroups; void* NumUsers; void* NumSessions; void* HubType; void* Online; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ RPC_ENUM_HUB_ITEM ;
typedef  TYPE_2__ RPC_ENUM_HUB ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  InRpcTrafficEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 void* PackGetBoolEx (int /*<<< orphan*/ *,char*,size_t) ; 
 int PackGetIndexCount (int /*<<< orphan*/ *,char*) ; 
 void* PackGetInt64Ex (int /*<<< orphan*/ *,char*,size_t) ; 
 void* PackGetIntEx (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackGetStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,size_t) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 TYPE_1__* ZeroMalloc (int) ; 

void InRpcEnumHub(RPC_ENUM_HUB *t, PACK *p)
{
	UINT i;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_ENUM_HUB));
	t->NumHub = PackGetIndexCount(p, "HubName");
	t->Hubs = ZeroMalloc(sizeof(RPC_ENUM_HUB_ITEM) * t->NumHub);

	for (i = 0;i < t->NumHub;i++)
	{
		RPC_ENUM_HUB_ITEM *e = &t->Hubs[i];

		PackGetStrEx(p, "HubName", e->HubName, sizeof(e->HubName), i);
		e->Online = PackGetBoolEx(p, "Online", i);
		e->HubType = PackGetIntEx(p, "HubType", i);
		e->NumSessions = PackGetIntEx(p, "NumSessions", i);
		e->NumUsers = PackGetIntEx(p, "NumUsers", i);
		e->NumGroups = PackGetIntEx(p, "NumGroups", i);
		e->NumMacTables = PackGetIntEx(p, "NumMacTables", i);
		e->NumIpTables = PackGetIntEx(p, "NumIpTables", i);
		e->LastCommTime = PackGetInt64Ex(p, "LastCommTime", i);
		e->CreatedTime = PackGetInt64Ex(p, "CreatedTime", i);
		e->LastLoginTime = PackGetInt64Ex(p, "LastLoginTime", i);
		e->NumLogin = PackGetIntEx(p, "NumLogin", i);
		e->IsTrafficFilled = PackGetBoolEx(p, "IsTrafficFilled", i);

		InRpcTrafficEx(&e->Traffic, p, i);
	}
}