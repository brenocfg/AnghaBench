#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  hubname ;
typedef  int /*<<< orphan*/  USERGROUP ;
struct TYPE_11__ {char* GroupName; int /*<<< orphan*/  lock; int /*<<< orphan*/ * Policy; int /*<<< orphan*/  Traffic; int /*<<< orphan*/  NumLogin; int /*<<< orphan*/  AuthData; int /*<<< orphan*/  AuthType; int /*<<< orphan*/  ExpireTime; int /*<<< orphan*/  UpdatedTime; int /*<<< orphan*/  CreatedTime; int /*<<< orphan*/  Note; int /*<<< orphan*/  RealName; } ;
typedef  TYPE_1__ USER ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_14__ {TYPE_2__* Server; } ;
struct TYPE_13__ {char* Name; char* HubName; char* GroupName; int /*<<< orphan*/  Policy; int /*<<< orphan*/  Traffic; int /*<<< orphan*/  NumLogin; int /*<<< orphan*/  AuthType; int /*<<< orphan*/  AuthData; int /*<<< orphan*/  ExpireTime; int /*<<< orphan*/  UpdatedTime; int /*<<< orphan*/  CreatedTime; int /*<<< orphan*/  Note; int /*<<< orphan*/  Realname; } ;
struct TYPE_12__ {scalar_t__ ServerType; int /*<<< orphan*/ * Cedar; } ;
typedef  int /*<<< orphan*/  TRAFFIC ;
typedef  TYPE_2__ SERVER ;
typedef  TYPE_3__ RPC_SET_USER ;
typedef  int /*<<< orphan*/  HUB ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_4__ ADMIN ;

/* Variables and functions */
 TYPE_1__* AcGetUser (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  AcLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcUnlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CHECK_RIGHT ; 
 int /*<<< orphan*/  ClonePolicy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CopyAuthData (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_HUB_NOT_FOUND ; 
 int /*<<< orphan*/  ERR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  ERR_OBJECT_NOT_FOUND ; 
 int /*<<< orphan*/  FreeRpcSetUser (TYPE_3__*) ; 
 int /*<<< orphan*/ * GetHub (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ IsEmptyStr (char*) ; 
 int IsUserName (char*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_HUBNAME_LEN ; 
 int /*<<< orphan*/  MAX_USERNAME_LEN ; 
 int /*<<< orphan*/  NO_SUPPORT_FOR_BRIDGE ; 
 int /*<<< orphan*/  ReleaseHub (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseUser (TYPE_1__*) ; 
 scalar_t__ SERVER_TYPE_FARM_MEMBER ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Zero (TYPE_3__*,int) ; 

UINT StGetUser(ADMIN *a, RPC_SET_USER *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	HUB *h = NULL;
	UINT ret = ERR_NO_ERROR;
	USER *u = NULL;
	USERGROUP *g = NULL;
	char name[MAX_USERNAME_LEN + 1];
	char hubname[MAX_HUBNAME_LEN + 1];
	StrCpy(name, sizeof(name), t->Name);
	StrCpy(hubname, sizeof(hubname), t->HubName);

	if (IsEmptyStr(t->Name) || IsUserName(t->Name) == false)
	{
		return ERR_INVALID_PARAMETER;
	}

	CHECK_RIGHT;
	NO_SUPPORT_FOR_BRIDGE;
	if (s->ServerType == SERVER_TYPE_FARM_MEMBER)
	{
		return ERR_NOT_SUPPORTED;
	}

	FreeRpcSetUser(t);
	Zero(t, sizeof(RPC_SET_USER));
	StrCpy(t->HubName, sizeof(t->HubName), hubname);
	StrCpy(t->Name, sizeof(t->Name), name);

	LockHubList(c);
	{
		h = GetHub(c, hubname);
	}
	UnlockHubList(c);

	if (h == NULL)
	{
		return ERR_HUB_NOT_FOUND;
	}

	AcLock(h);
	{
		u = AcGetUser(h, name);
		if (u == NULL)
		{
			ret = ERR_OBJECT_NOT_FOUND;
		}
		else
		{
			Lock(u->lock);
			{
				StrCpy(t->GroupName, sizeof(t->GroupName), u->GroupName);
				UniStrCpy(t->Realname, sizeof(t->Realname), u->RealName);
				UniStrCpy(t->Note, sizeof(t->Note), u->Note);
				t->CreatedTime = u->CreatedTime;
				t->UpdatedTime = u->UpdatedTime;
				t->ExpireTime = u->ExpireTime;

				t->AuthType = u->AuthType;
				t->AuthData = CopyAuthData(u->AuthData, t->AuthType);
				t->NumLogin = u->NumLogin;
				Copy(&t->Traffic, u->Traffic, sizeof(TRAFFIC));
				if (u->Policy != NULL)
				{
					t->Policy = ClonePolicy(u->Policy);
				}
			}
			Unlock(u->lock);

			ReleaseUser(u);
		}
	}
	AcUnlock(h);

	ReleaseHub(h);

	return ret;
}