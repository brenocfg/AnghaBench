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
struct TYPE_7__ {int NumUser; TYPE_1__* Users; int /*<<< orphan*/  HubName; } ;
struct TYPE_6__ {void* Expires; void* IsExpiresFilled; int /*<<< orphan*/  Traffic; void* IsTrafficFilled; void* DenyAccess; void* NumLogin; void* LastLoginTime; void* AuthType; int /*<<< orphan*/  Note; int /*<<< orphan*/  Realname; int /*<<< orphan*/  GroupName; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ RPC_ENUM_USER_ITEM ;
typedef  TYPE_2__ RPC_ENUM_USER ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  InRpcTrafficEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 void* PackGetBoolEx (int /*<<< orphan*/ *,char*,size_t) ; 
 int PackGetIndexCount (int /*<<< orphan*/ *,char*) ; 
 void* PackGetInt64Ex (int /*<<< orphan*/ *,char*,size_t) ; 
 void* PackGetIntEx (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PackGetStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,size_t) ; 
 int /*<<< orphan*/  PackGetUniStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,size_t) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 TYPE_1__* ZeroMalloc (int) ; 

void InRpcEnumUser(RPC_ENUM_USER *t, PACK *p)
{
	UINT i;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_ENUM_USER));
	PackGetStr(p, "HubName", t->HubName, sizeof(t->HubName));
	t->NumUser = PackGetIndexCount(p, "Name");
	t->Users = ZeroMalloc(sizeof(RPC_ENUM_USER_ITEM) * t->NumUser);

	for (i = 0;i < t->NumUser;i++)
	{
		RPC_ENUM_USER_ITEM *e = &t->Users[i];

		PackGetStrEx(p, "Name", e->Name, sizeof(e->Name), i);
		PackGetStrEx(p, "GroupName", e->GroupName, sizeof(e->GroupName), i);
		PackGetUniStrEx(p, "Realname", e->Realname, sizeof(e->Realname), i);
		PackGetUniStrEx(p, "Note", e->Note, sizeof(e->Note), i);
		e->AuthType = PackGetIntEx(p, "AuthType", i);
		e->LastLoginTime = PackGetInt64Ex(p, "LastLoginTime", i);
		e->NumLogin = PackGetIntEx(p, "NumLogin", i);
		e->DenyAccess = PackGetBoolEx(p, "DenyAccess", i);

		e->IsTrafficFilled = PackGetBoolEx(p, "IsTrafficFilled", i);
		InRpcTrafficEx(&e->Traffic, p, i);

		e->IsExpiresFilled = PackGetBoolEx(p, "IsExpiresFilled", i);
		e->Expires = PackGetInt64Ex(p, "Expires", i);
	}
}