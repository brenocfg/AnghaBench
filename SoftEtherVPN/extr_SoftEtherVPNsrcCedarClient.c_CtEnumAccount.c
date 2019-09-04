#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_17__ {int /*<<< orphan*/  UpdateDateTime; int /*<<< orphan*/  LastConnectDateTime; int /*<<< orphan*/  CreateDateTime; TYPE_3__* ClientOption; TYPE_2__* ClientSession; int /*<<< orphan*/  StartupAccount; TYPE_1__* ClientAuth; } ;
struct TYPE_16__ {int /*<<< orphan*/  AccountList; } ;
struct TYPE_15__ {int NumItem; TYPE_4__** Items; } ;
struct TYPE_14__ {scalar_t__ ProxyType; int Active; int Connected; int /*<<< orphan*/  UpdateDateTime; int /*<<< orphan*/  LastConnectDateTime; int /*<<< orphan*/  CreateDateTime; int /*<<< orphan*/  HubName; int /*<<< orphan*/  Port; int /*<<< orphan*/  StartupAccount; int /*<<< orphan*/  ProxyName; int /*<<< orphan*/  DeviceName; int /*<<< orphan*/  ServerName; int /*<<< orphan*/  UserName; int /*<<< orphan*/  AccountName; } ;
struct TYPE_13__ {scalar_t__ ProxyType; int /*<<< orphan*/  HubName; int /*<<< orphan*/  Port; int /*<<< orphan*/  ProxyName; int /*<<< orphan*/  DeviceName; int /*<<< orphan*/  Hostname; int /*<<< orphan*/  AccountName; } ;
struct TYPE_12__ {int ConnectSucceed; } ;
struct TYPE_11__ {int /*<<< orphan*/  Username; } ;
typedef  TYPE_4__ RPC_CLIENT_ENUM_ACCOUNT_ITEM ;
typedef  TYPE_5__ RPC_CLIENT_ENUM_ACCOUNT ;
typedef  TYPE_6__ CLIENT ;
typedef  TYPE_7__ ACCOUNT ;

/* Variables and functions */
 TYPE_7__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 int LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 scalar_t__ PROXY_DIRECT ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 void* ZeroMalloc (int) ; 

bool CtEnumAccount(CLIENT *c, RPC_CLIENT_ENUM_ACCOUNT *e)
{
	// Validate arguments
	if (c == NULL || e == NULL)
	{
		return false;
	}

	LockList(c->AccountList);
	{
		UINT i;
		// Number of accounts
		e->NumItem = LIST_NUM(c->AccountList);
		e->Items = ZeroMalloc(sizeof(RPC_CLIENT_ENUM_ACCOUNT_ITEM *) * e->NumItem);

		for (i = 0;i < e->NumItem;i++)
		{
			ACCOUNT *a = LIST_DATA(c->AccountList, i);
			RPC_CLIENT_ENUM_ACCOUNT_ITEM *item = ZeroMalloc(sizeof(RPC_CLIENT_ENUM_ACCOUNT_ITEM));
			e->Items[i] = item;

			// Account name
			UniStrCpy(item->AccountName, sizeof(item->AccountName), a->ClientOption->AccountName);

			// User name
			StrCpy(item->UserName, sizeof(item->UserName), a->ClientAuth->Username);

			// Server name
			StrCpy(item->ServerName, sizeof(item->ServerName), a->ClientOption->Hostname);

			// Proxy type
			item->ProxyType = a->ClientOption->ProxyType;

			// Device name
			StrCpy(item->DeviceName, sizeof(item->DeviceName), a->ClientOption->DeviceName);

			// Proxy information
			if (item->ProxyType != PROXY_DIRECT)
			{
				StrCpy(item->ProxyName, sizeof(item->ProxyName), a->ClientOption->ProxyName);
			}

			// Startup
			item->StartupAccount = a->StartupAccount;

			// Active flag
			item->Active = (a->ClientSession == NULL ? false : true);

			// Connection flag
			item->Connected = (item->Active == false) ? false : a->ClientSession->ConnectSucceed;

			// Port number
			item->Port = a->ClientOption->Port;

			// Virtual HUB name
			StrCpy(item->HubName, sizeof(item->HubName), a->ClientOption->HubName);

			item->CreateDateTime = a->CreateDateTime;
			item->LastConnectDateTime = a->LastConnectDateTime;
			item->UpdateDateTime = a->UpdateDateTime;
		}
	}
	UnlockList(c->AccountList);

	return true;
}