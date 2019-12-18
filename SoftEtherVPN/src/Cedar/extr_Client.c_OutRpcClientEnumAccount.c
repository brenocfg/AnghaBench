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
struct TYPE_5__ {size_t NumItem; TYPE_1__** Items; } ;
struct TYPE_4__ {int /*<<< orphan*/  LastConnectDateTime; int /*<<< orphan*/  UpdateDateTime; int /*<<< orphan*/  CreateDateTime; int /*<<< orphan*/  HubName; int /*<<< orphan*/  Port; int /*<<< orphan*/  Connected; int /*<<< orphan*/  StartupAccount; int /*<<< orphan*/  Active; int /*<<< orphan*/  ProxyType; int /*<<< orphan*/  DeviceName; int /*<<< orphan*/  ProxyName; int /*<<< orphan*/  ServerName; int /*<<< orphan*/  UserName; int /*<<< orphan*/  AccountName; } ;
typedef  TYPE_1__ RPC_CLIENT_ENUM_ACCOUNT_ITEM ;
typedef  TYPE_2__ RPC_CLIENT_ENUM_ACCOUNT ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddBoolEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddIntEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddNum (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackAddStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddTime64Ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddUniStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackSetCurrentJsonGroupName (int /*<<< orphan*/ *,char*) ; 

void OutRpcClientEnumAccount(PACK *p, RPC_CLIENT_ENUM_ACCOUNT *e)
{
	UINT i;
	// Validate arguments
	if (e == NULL || p == NULL)
	{
		return;
	}

	PackAddNum(p, "NumItem", e->NumItem);

	PackSetCurrentJsonGroupName(p, "AccountList");
	for (i = 0;i < e->NumItem;i++)
	{
		RPC_CLIENT_ENUM_ACCOUNT_ITEM *item = e->Items[i];

		PackAddUniStrEx(p, "AccountName", item->AccountName, i, e->NumItem);
		PackAddStrEx(p, "UserName", item->UserName, i, e->NumItem);
		PackAddStrEx(p, "ServerName", item->ServerName, i, e->NumItem);
		PackAddStrEx(p, "ProxyName", item->ProxyName, i, e->NumItem);
		PackAddStrEx(p, "DeviceName", item->DeviceName, i, e->NumItem);
		PackAddIntEx(p, "ProxyType", item->ProxyType, i, e->NumItem);
		PackAddIntEx(p, "Active", item->Active, i, e->NumItem);
		PackAddIntEx(p, "StartupAccount", item->StartupAccount, i, e->NumItem);
		PackAddBoolEx(p, "Connected", item->Connected, i, e->NumItem);
		PackAddIntEx(p, "Port", item->Port, i, e->NumItem);
		PackAddStrEx(p, "HubName", item->HubName, i, e->NumItem);
		PackAddTime64Ex(p, "CreateDateTime", item->CreateDateTime, i, e->NumItem);
		PackAddTime64Ex(p, "UpdateDateTime", item->UpdateDateTime, i, e->NumItem);
		PackAddTime64Ex(p, "LastConnectDateTime", item->LastConnectDateTime, i, e->NumItem);
	}
	PackSetCurrentJsonGroupName(p, NULL);
}