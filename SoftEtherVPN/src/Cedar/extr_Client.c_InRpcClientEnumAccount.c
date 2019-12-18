#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_6__ {int NumItem; TYPE_1__** Items; } ;
struct TYPE_5__ {int Active; int StartupAccount; void* LastConnectDateTime; void* UpdateDateTime; void* CreateDateTime; int /*<<< orphan*/  HubName; void* Port; int /*<<< orphan*/  Connected; void* ProxyType; int /*<<< orphan*/  DeviceName; int /*<<< orphan*/  ProxyName; int /*<<< orphan*/  ServerName; int /*<<< orphan*/  UserName; int /*<<< orphan*/  AccountName; } ;
typedef  TYPE_1__ RPC_CLIENT_ENUM_ACCOUNT_ITEM ;
typedef  TYPE_2__ RPC_CLIENT_ENUM_ACCOUNT ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackGetBoolEx (int /*<<< orphan*/ *,char*,size_t) ; 
 void* PackGetInt64Ex (int /*<<< orphan*/ *,char*,size_t) ; 
 void* PackGetIntEx (int /*<<< orphan*/ *,char*,size_t) ; 
 int PackGetNum (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,size_t) ; 
 int /*<<< orphan*/  PackGetUniStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,size_t) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 void* ZeroMalloc (int) ; 

void InRpcClientEnumAccount(RPC_CLIENT_ENUM_ACCOUNT *e, PACK *p)
{
	UINT i;
	// Validate arguments
	if (e == NULL || p == NULL)
	{
		return;
	}

	Zero(e, sizeof(RPC_CLIENT_ENUM_ACCOUNT));

	e->NumItem = PackGetNum(p, "NumItem");
	e->Items = ZeroMalloc(sizeof(RPC_CLIENT_ENUM_ACCOUNT_ITEM *) * e->NumItem);

	for (i = 0;i < e->NumItem;i++)
	{
		RPC_CLIENT_ENUM_ACCOUNT_ITEM *item = e->Items[i] =
			ZeroMalloc(sizeof(RPC_CLIENT_ENUM_ACCOUNT_ITEM));

		PackGetUniStrEx(p, "AccountName", item->AccountName, sizeof(item->AccountName), i);
		PackGetStrEx(p, "UserName", item->UserName, sizeof(item->UserName), i);
		PackGetStrEx(p, "ServerName", item->ServerName, sizeof(item->ServerName), i);
		PackGetStrEx(p, "ProxyName", item->ProxyName, sizeof(item->ProxyName), i);
		PackGetStrEx(p, "DeviceName", item->DeviceName, sizeof(item->DeviceName), i);
		item->ProxyType = PackGetIntEx(p, "ProxyType", i);
		item->Active = PackGetIntEx(p, "Active", i) ? true : false;
		item->StartupAccount = PackGetIntEx(p, "StartupAccount", i) ? true : false;
		item->Connected = PackGetBoolEx(p, "Connected", i);
		item->Port = PackGetIntEx(p, "Port", i);
		PackGetStrEx(p, "HubName", item->HubName, sizeof(item->HubName), i);
		item->CreateDateTime = PackGetInt64Ex(p, "CreateDateTime", i);
		item->UpdateDateTime = PackGetInt64Ex(p, "UpdateDateTime", i);
		item->LastConnectDateTime = PackGetInt64Ex(p, "LastConnectDateTime", i);
	}
}