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
struct TYPE_5__ {size_t NumUser; TYPE_1__* Users; int /*<<< orphan*/  HubName; } ;
struct TYPE_4__ {int /*<<< orphan*/  Expires; int /*<<< orphan*/  IsExpiresFilled; int /*<<< orphan*/  Traffic; int /*<<< orphan*/  IsTrafficFilled; int /*<<< orphan*/  DenyAccess; int /*<<< orphan*/  NumLogin; int /*<<< orphan*/  LastLoginTime; int /*<<< orphan*/  AuthType; int /*<<< orphan*/  Note; int /*<<< orphan*/  Realname; int /*<<< orphan*/  GroupName; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ RPC_ENUM_USER_ITEM ;
typedef  TYPE_2__ RPC_ENUM_USER ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  OutRpcTrafficEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddBoolEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddIntEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddTime64Ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddUniStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackSetCurrentJsonGroupName (int /*<<< orphan*/ *,char*) ; 

void OutRpcEnumUser(PACK *p, RPC_ENUM_USER *t)
{
	UINT i;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}
	PackAddStr(p, "HubName", t->HubName);

	PackSetCurrentJsonGroupName(p, "UserList");
	for (i = 0;i < t->NumUser;i++)
	{
		RPC_ENUM_USER_ITEM *e = &t->Users[i];

		PackAddStrEx(p, "Name", e->Name, i, t->NumUser);
		PackAddStrEx(p, "GroupName", e->GroupName, i, t->NumUser);
		PackAddUniStrEx(p, "Realname", e->Realname, i, t->NumUser);
		PackAddUniStrEx(p, "Note", e->Note, i, t->NumUser);
		PackAddIntEx(p, "AuthType", e->AuthType, i, t->NumUser);
		PackAddTime64Ex(p, "LastLoginTime", e->LastLoginTime, i, t->NumUser);
		PackAddIntEx(p, "NumLogin", e->NumLogin, i, t->NumUser);
		PackAddBoolEx(p, "DenyAccess", e->DenyAccess, i, t->NumUser);

		PackAddBoolEx(p, "IsTrafficFilled", e->IsTrafficFilled, i, t->NumUser);
		OutRpcTrafficEx(&e->Traffic, p, i, t->NumUser);

		PackAddBoolEx(p, "IsExpiresFilled", e->IsExpiresFilled, i, t->NumUser);
		PackAddTime64Ex(p, "Expires", e->Expires, i, t->NumUser);
	}
	PackSetCurrentJsonGroupName(p, NULL);
}