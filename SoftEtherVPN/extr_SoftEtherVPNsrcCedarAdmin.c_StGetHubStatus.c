#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_19__ {TYPE_2__* Server; } ;
struct TYPE_18__ {int Me; int /*<<< orphan*/  HubList; } ;
struct TYPE_17__ {scalar_t__ Type; int /*<<< orphan*/  EnableSecureNAT; int /*<<< orphan*/  lock; int /*<<< orphan*/  CreatedTime; int /*<<< orphan*/  LastLoginTime; int /*<<< orphan*/  LastCommTime; int /*<<< orphan*/  NumLogin; int /*<<< orphan*/  TrafficLock; int /*<<< orphan*/  Traffic; int /*<<< orphan*/  IpTable; int /*<<< orphan*/  MacHashTable; TYPE_1__* HubDb; int /*<<< orphan*/  AccessList; int /*<<< orphan*/  NumSessionsBridge; int /*<<< orphan*/  NumSessionsClient; int /*<<< orphan*/  SessionList; scalar_t__ Offline; int /*<<< orphan*/  Name; } ;
struct TYPE_16__ {scalar_t__ NumIpTables; scalar_t__ NumMacTables; scalar_t__ NumSessionsBridge; scalar_t__ NumSessionsClient; scalar_t__ NumSessions; int /*<<< orphan*/  Name; } ;
struct TYPE_15__ {scalar_t__ HubType; int Online; int /*<<< orphan*/  SecureNATEnabled; scalar_t__ NumIpTables; int /*<<< orphan*/  NumMacTables; void* NumSessionsBridge; void* NumSessionsClient; scalar_t__ NumSessions; int /*<<< orphan*/  HubName; int /*<<< orphan*/  CreatedTime; int /*<<< orphan*/  LastLoginTime; int /*<<< orphan*/  LastCommTime; int /*<<< orphan*/  NumLogin; int /*<<< orphan*/  Traffic; scalar_t__ NumGroups; scalar_t__ NumUsers; scalar_t__ NumAccessLists; } ;
struct TYPE_14__ {scalar_t__ ServerType; int /*<<< orphan*/  FarmMemberList; int /*<<< orphan*/ * Cedar; } ;
struct TYPE_13__ {int /*<<< orphan*/  GroupList; int /*<<< orphan*/  UserList; } ;
typedef  int /*<<< orphan*/  TRAFFIC ;
typedef  TYPE_2__ SERVER ;
typedef  TYPE_3__ RPC_HUB_STATUS ;
typedef  TYPE_4__ HUB_LIST ;
typedef  TYPE_5__ HUB ;
typedef  TYPE_6__ FARM_MEMBER ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_7__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_RIGHT ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 void* Count (int /*<<< orphan*/ ) ; 
 scalar_t__ ERR_HUB_NOT_FOUND ; 
 scalar_t__ ERR_NO_ERROR ; 
 TYPE_5__* GetHub (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HASH_LIST_NUM (int /*<<< orphan*/ ) ; 
 scalar_t__ HUB_TYPE_FARM_STATIC ; 
 void* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_5__*) ; 
 scalar_t__ SERVER_TYPE_FARM_CONTROLLER ; 
 scalar_t__ StrCmpi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_3__*,int) ; 

UINT StGetHubStatus(ADMIN *a, RPC_HUB_STATUS *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	HUB *h;

	CHECK_RIGHT;

	LockHubList(c);
	{
		h = GetHub(c, t->HubName);
	}
	UnlockHubList(c);

	if (h == NULL)
	{
		return ERR_HUB_NOT_FOUND;
	}

	Zero(t, sizeof(RPC_HUB_STATUS));

	Lock(h->lock);
	{
		StrCpy(t->HubName, sizeof(t->HubName), h->Name);
		t->HubType = h->Type;
		t->Online = h->Offline ? false : true;
		t->NumSessions = LIST_NUM(h->SessionList);
		t->NumSessionsClient = Count(h->NumSessionsClient);
		t->NumSessionsBridge = Count(h->NumSessionsBridge);
		t->NumAccessLists = LIST_NUM(h->AccessList);

		if (h->HubDb != NULL)
		{
			t->NumUsers = LIST_NUM(h->HubDb->UserList);
			t->NumGroups = LIST_NUM(h->HubDb->GroupList);
		}

		t->NumMacTables = HASH_LIST_NUM(h->MacHashTable);
		t->NumIpTables = LIST_NUM(h->IpTable);

		Lock(h->TrafficLock);
		{
			Copy(&t->Traffic, h->Traffic, sizeof(TRAFFIC));
		}
		Unlock(h->TrafficLock);

		t->NumLogin = h->NumLogin;
		t->LastCommTime = h->LastCommTime;
		t->LastLoginTime = h->LastLoginTime;
		t->CreatedTime = h->CreatedTime;
	}
	Unlock(h->lock);

	if (s->ServerType == SERVER_TYPE_FARM_CONTROLLER)
	{
		UINT i;
		LockList(s->FarmMemberList);
		{
			for (i = 0;i < LIST_NUM(s->FarmMemberList);i++)
			{
				UINT k;
				FARM_MEMBER *f = LIST_DATA(s->FarmMemberList, i);

				if (f->Me == false)
				{
					LockList(f->HubList);
					{
						for (k = 0;k < LIST_NUM(f->HubList);k++)
						{
							HUB_LIST *h = LIST_DATA(f->HubList, k);

							if (StrCmpi(h->Name, t->HubName) == 0)
							{
								t->NumSessions += h->NumSessions;
								t->NumSessionsClient += h->NumSessionsClient;
								t->NumSessionsBridge += h->NumSessionsBridge;
								t->NumMacTables += h->NumMacTables;
								t->NumIpTables += h->NumIpTables;
							}
						}
					}
					UnlockList(f->HubList);
				}
			}
		}
		UnlockList(s->FarmMemberList);
	}

	if (h->Type != HUB_TYPE_FARM_STATIC)
	{
		t->SecureNATEnabled = h->EnableSecureNAT;
	}

	ReleaseHub(h);

	return ERR_NO_ERROR;
}