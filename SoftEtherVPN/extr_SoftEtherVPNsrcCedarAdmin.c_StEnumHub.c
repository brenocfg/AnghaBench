#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_25__ {int ServerAdmin; int /*<<< orphan*/  HubName; TYPE_2__* Server; } ;
struct TYPE_24__ {int /*<<< orphan*/  HubList; } ;
struct TYPE_23__ {int Me; int /*<<< orphan*/  HubList; } ;
struct TYPE_22__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  TrafficLock; int /*<<< orphan*/  Traffic; int /*<<< orphan*/  CreatedTime; int /*<<< orphan*/  NumLogin; int /*<<< orphan*/  LastLoginTime; int /*<<< orphan*/  LastCommTime; TYPE_1__* HubDb; int /*<<< orphan*/  IpTable; int /*<<< orphan*/  MacHashTable; int /*<<< orphan*/  SessionList; int /*<<< orphan*/  Type; scalar_t__ Offline; int /*<<< orphan*/  Name; int /*<<< orphan*/ * Option; } ;
struct TYPE_21__ {scalar_t__ NumSessions; scalar_t__ NumMacTables; scalar_t__ NumIpTables; int /*<<< orphan*/  Name; } ;
struct TYPE_20__ {scalar_t__ NumHub; TYPE_3__* Hubs; } ;
struct TYPE_19__ {int Online; int IsTrafficFilled; scalar_t__ NumSessions; int /*<<< orphan*/  NumMacTables; scalar_t__ NumIpTables; int /*<<< orphan*/  HubName; int /*<<< orphan*/  Traffic; int /*<<< orphan*/  CreatedTime; int /*<<< orphan*/  NumLogin; int /*<<< orphan*/  LastLoginTime; int /*<<< orphan*/  LastCommTime; scalar_t__ NumGroups; scalar_t__ NumUsers; int /*<<< orphan*/  HubType; } ;
struct TYPE_18__ {scalar_t__ ServerType; int /*<<< orphan*/  FarmMemberList; TYPE_8__* Cedar; } ;
struct TYPE_17__ {int /*<<< orphan*/  GroupList; int /*<<< orphan*/  UserList; } ;
typedef  int /*<<< orphan*/  TRAFFIC ;
typedef  TYPE_2__ SERVER ;
typedef  TYPE_3__ RPC_ENUM_HUB_ITEM ;
typedef  TYPE_4__ RPC_ENUM_HUB ;
typedef  TYPE_5__ HUB_LIST ;
typedef  TYPE_6__ HUB ;
typedef  TYPE_7__ FARM_MEMBER ;
typedef  TYPE_8__ CEDAR ;
typedef  TYPE_9__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeRpcEnumHub (TYPE_4__*) ; 
 int /*<<< orphan*/  HASH_LIST_NUM (int /*<<< orphan*/ ) ; 
 void* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHashList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHubList (TYPE_8__*) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 scalar_t__ SERVER_TYPE_FARM_CONTROLLER ; 
 scalar_t__ StrCmpi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockHashList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockHubList (TYPE_8__*) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_4__*,int) ; 
 TYPE_3__* ZeroMalloc (int) ; 

UINT StEnumHub(ADMIN *a, RPC_ENUM_HUB *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	HUB *h = NULL;

	FreeRpcEnumHub(t);

	Zero(t, sizeof(RPC_ENUM_HUB));

	LockHubList(c);
	{
		UINT i, num, j;

		num = 0;

		for (i = 0;i < LIST_NUM(c->HubList);i++)
		{
			HUB *h = LIST_DATA(c->HubList, i);

			Lock(h->lock);

			if (a->ServerAdmin == false &&
				h->Option != NULL &&
				StrCmpi(h->Name, a->HubName) != 0)
			{
				// This hub is not listed
			}
			else
			{
				// This hub is listed
				num++;
			}
		}

		t->NumHub = num;

		t->Hubs = ZeroMalloc(sizeof(RPC_ENUM_HUB_ITEM) * num);

		i = 0;
		for (j = 0;j < LIST_NUM(c->HubList);j++)
		{
			HUB *h = LIST_DATA(c->HubList, j);

			if (a->ServerAdmin == false &&
				h->Option != NULL &&
				StrCmpi(h->Name, a->HubName) != 0)
			{
				// This hub is not listed
			}
			else
			{
				// This hub is listed
				RPC_ENUM_HUB_ITEM *e = &t->Hubs[i++];

				StrCpy(e->HubName, sizeof(e->HubName), h->Name);
				e->Online = h->Offline ? false : true;
				e->HubType = h->Type;

				e->NumSessions = LIST_NUM(h->SessionList);

				LockHashList(h->MacHashTable);
				{
					e->NumMacTables = HASH_LIST_NUM(h->MacHashTable);
				}
				UnlockHashList(h->MacHashTable);

				LockList(h->IpTable);
				{
					e->NumIpTables = LIST_NUM(h->IpTable);
				}
				UnlockList(h->IpTable);

				if (h->HubDb != NULL)
				{
					LockList(h->HubDb->UserList);
					{
						e->NumUsers = LIST_NUM(h->HubDb->UserList);
					}
					UnlockList(h->HubDb->UserList);

					LockList(h->HubDb->GroupList);
					{
						e->NumGroups = LIST_NUM(h->HubDb->GroupList);
					}
					UnlockList(h->HubDb->GroupList);
				}

				e->LastCommTime = h->LastCommTime;
				e->LastLoginTime = h->LastLoginTime;
				e->NumLogin = h->NumLogin;
				e->CreatedTime = h->CreatedTime;

				Lock(h->TrafficLock);
				{
					Copy(&e->Traffic, h->Traffic, sizeof(TRAFFIC));
				}
				Unlock(h->TrafficLock);

				e->IsTrafficFilled = true;
			}

			Unlock(h->lock);
		}
	}
	UnlockHubList(c);

	if (s->ServerType == SERVER_TYPE_FARM_CONTROLLER)
	{
		UINT i, j, k;
		LockList(s->FarmMemberList);
		{
			for (i = 0;i < LIST_NUM(s->FarmMemberList);i++)
			{
				FARM_MEMBER *f = LIST_DATA(s->FarmMemberList, i);

				LockList(f->HubList);
				{
					if (f->Me == false)
					{
						for (j = 0;j < LIST_NUM(f->HubList);j++)
						{
							HUB_LIST *o = LIST_DATA(f->HubList, j);

							for (k = 0;k < t->NumHub;k++)
							{
								RPC_ENUM_HUB_ITEM *e = &t->Hubs[k];

								if (StrCmpi(e->HubName, o->Name) == 0)
								{
									e->NumIpTables += o->NumIpTables;
									e->NumMacTables += o->NumMacTables;
									e->NumSessions += o->NumSessions;
								}
							}
						}
					}
				}
				UnlockList(f->HubList);
			}
		}
		UnlockList(s->FarmMemberList);
	}

	return ERR_NO_ERROR;
}