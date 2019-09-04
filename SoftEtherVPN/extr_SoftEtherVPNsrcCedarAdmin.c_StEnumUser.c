#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hubname ;
struct TYPE_20__ {char* Name; char* GroupName; int /*<<< orphan*/  lock; int /*<<< orphan*/  ExpireTime; int /*<<< orphan*/  Traffic; TYPE_1__* Policy; int /*<<< orphan*/  NumLogin; int /*<<< orphan*/  LastLoginTime; int /*<<< orphan*/  AuthType; int /*<<< orphan*/  Note; int /*<<< orphan*/  RealName; } ;
typedef  TYPE_3__ USER ;
typedef  int UINT ;
struct TYPE_25__ {TYPE_4__* Server; } ;
struct TYPE_24__ {TYPE_2__* HubDb; } ;
struct TYPE_23__ {char* HubName; int NumUser; TYPE_5__* Users; } ;
struct TYPE_22__ {char* Name; char* GroupName; int DenyAccess; int IsTrafficFilled; int IsExpiresFilled; int /*<<< orphan*/  Expires; int /*<<< orphan*/  Traffic; int /*<<< orphan*/  NumLogin; int /*<<< orphan*/  LastLoginTime; int /*<<< orphan*/  AuthType; int /*<<< orphan*/  Note; int /*<<< orphan*/  Realname; } ;
struct TYPE_21__ {scalar_t__ ServerType; int /*<<< orphan*/ * Cedar; } ;
struct TYPE_19__ {int /*<<< orphan*/  UserList; } ;
struct TYPE_18__ {scalar_t__ Access; } ;
typedef  int /*<<< orphan*/  TRAFFIC ;
typedef  TYPE_4__ SERVER ;
typedef  TYPE_5__ RPC_ENUM_USER_ITEM ;
typedef  TYPE_6__ RPC_ENUM_USER ;
typedef  TYPE_7__ HUB ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_8__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_RIGHT ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int ERR_HUB_NOT_FOUND ; 
 int ERR_NOT_SUPPORTED ; 
 int ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeRpcEnumUser (TYPE_6__*) ; 
 TYPE_7__* GetHub (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  IncrementServerConfigRevision (TYPE_4__*) ; 
 TYPE_3__* LIST_DATA (int /*<<< orphan*/ ,int) ; 
 int LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_HUBNAME_LEN ; 
 int /*<<< orphan*/  NO_SUPPORT_FOR_BRIDGE ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_7__*) ; 
 scalar_t__ SERVER_TYPE_FARM_MEMBER ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_6__*,int) ; 
 TYPE_5__* ZeroMalloc (int) ; 

UINT StEnumUser(ADMIN *a, RPC_ENUM_USER *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	HUB *h = NULL;
	UINT ret = ERR_NO_ERROR;
	char hubname[MAX_HUBNAME_LEN + 1];
	UINT i, num;

	CHECK_RIGHT;
	NO_SUPPORT_FOR_BRIDGE;
	if (s->ServerType == SERVER_TYPE_FARM_MEMBER)
	{
		return ERR_NOT_SUPPORTED;
	}

	LockHubList(c);
	{
		h = GetHub(c, t->HubName);
	}
	UnlockHubList(c);

	if (h == NULL)
	{
		return ERR_HUB_NOT_FOUND;
	}

	FreeRpcEnumUser(t);

	StrCpy(hubname, sizeof(hubname), t->HubName);

	Zero(t, sizeof(RPC_ENUM_USER));
	StrCpy(t->HubName, sizeof(t->HubName), hubname);

	LockList(h->HubDb->UserList);
	{
		num = LIST_NUM(h->HubDb->UserList);

		t->NumUser = num;
		t->Users = ZeroMalloc(sizeof(RPC_ENUM_USER_ITEM) * num);

		for (i = 0;i < num;i++)
		{
			USER *u = LIST_DATA(h->HubDb->UserList, i);

			Lock(u->lock);
			{
				RPC_ENUM_USER_ITEM *e = &t->Users[i];

				StrCpy(e->Name, sizeof(e->Name), u->Name);
				StrCpy(e->GroupName, sizeof(e->GroupName), u->GroupName);
				UniStrCpy(e->Realname, sizeof(e->Realname), u->RealName);
				UniStrCpy(e->Note, sizeof(e->Note), u->Note);
				e->AuthType = u->AuthType;
				e->LastLoginTime = u->LastLoginTime;
				e->NumLogin = u->NumLogin;

				if (u->Policy != NULL)
				{
					e->DenyAccess = u->Policy->Access ? false : true;
				}

				Copy(&e->Traffic, u->Traffic, sizeof(TRAFFIC));
				e->IsTrafficFilled = true;

				e->Expires = u->ExpireTime;
				e->IsExpiresFilled = true;
			}
			Unlock(u->lock);
		}
	}
	UnlockList(h->HubDb->UserList);

	ReleaseHub(h);

	IncrementServerConfigRevision(s);

	return ERR_NO_ERROR;
}