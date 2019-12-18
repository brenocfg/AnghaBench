#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hubname ;
struct TYPE_12__ {char* Name; int /*<<< orphan*/  lock; int /*<<< orphan*/  Traffic; int /*<<< orphan*/  Note; int /*<<< orphan*/  RealName; } ;
typedef  TYPE_1__ USERGROUP ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_15__ {TYPE_2__* Server; } ;
struct TYPE_14__ {char* Name; char* HubName; int /*<<< orphan*/  Policy; int /*<<< orphan*/  Traffic; int /*<<< orphan*/  Note; int /*<<< orphan*/  Realname; } ;
struct TYPE_13__ {scalar_t__ ServerType; int /*<<< orphan*/ * Cedar; } ;
typedef  int /*<<< orphan*/  TRAFFIC ;
typedef  TYPE_2__ SERVER ;
typedef  TYPE_3__ RPC_SET_GROUP ;
typedef  int /*<<< orphan*/  HUB ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_4__ ADMIN ;

/* Variables and functions */
 TYPE_1__* AcGetGroup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  AcLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcUnlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CHECK_RIGHT ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ERR_HUB_NOT_FOUND ; 
 int /*<<< orphan*/  ERR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  ERR_OBJECT_NOT_FOUND ; 
 int /*<<< orphan*/  FreeRpcSetGroup (TYPE_3__*) ; 
 int /*<<< orphan*/  GetGroupPolicy (TYPE_1__*) ; 
 int /*<<< orphan*/ * GetHub (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ IsEmptyStr (char*) ; 
 int IsSafeStr (char*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_HUBNAME_LEN ; 
 int /*<<< orphan*/  NO_SUPPORT_FOR_BRIDGE ; 
 int /*<<< orphan*/  ReleaseGroup (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseHub (int /*<<< orphan*/ *) ; 
 scalar_t__ SERVER_TYPE_FARM_MEMBER ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Zero (TYPE_3__*,int) ; 

UINT StGetGroup(ADMIN *a, RPC_SET_GROUP *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	HUB *h = NULL;
	UINT ret = ERR_NO_ERROR;
	char hubname[MAX_HUBNAME_LEN + 1];

	if (IsEmptyStr(t->Name) || IsSafeStr(t->Name) == false)
	{
		return ERR_INVALID_PARAMETER;
	}

	CHECK_RIGHT;
	NO_SUPPORT_FOR_BRIDGE;
	if (s->ServerType == SERVER_TYPE_FARM_MEMBER)
	{
		return ERR_NOT_SUPPORTED;
	}

	StrCpy(hubname, sizeof(hubname), t->HubName);

	LockHubList(c);
	{
		h = GetHub(c, t->HubName);
	}
	UnlockHubList(c);

	if (h == NULL)
	{
		return ERR_HUB_NOT_FOUND;
	}

	AcLock(h);
	{
		USERGROUP *g = AcGetGroup(h, t->Name);

		if (g == NULL)
		{
			ret = ERR_OBJECT_NOT_FOUND;
		}
		else
		{
			FreeRpcSetGroup(t);
			Zero(t, sizeof(RPC_SET_GROUP));

			StrCpy(t->HubName, sizeof(t->HubName), hubname);

			Lock(g->lock);
			{
				StrCpy(t->Name, sizeof(t->Name), g->Name);
				UniStrCpy(t->Realname, sizeof(t->Realname), g->RealName);
				UniStrCpy(t->Note, sizeof(t->Note), g->Note);
				Copy(&t->Traffic, g->Traffic, sizeof(TRAFFIC));
			}
			Unlock(g->lock);

			t->Policy = GetGroupPolicy(g);

			ReleaseGroup(g);
		}
	}
	AcUnlock(h);

	ReleaseHub(h);

	return ret;
}