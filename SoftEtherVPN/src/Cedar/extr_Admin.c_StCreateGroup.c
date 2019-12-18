#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USERGROUP ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_23__ {int ServerAdmin; TYPE_2__* Server; } ;
struct TYPE_22__ {TYPE_1__* HubDb; } ;
struct TYPE_21__ {int /*<<< orphan*/  Name; int /*<<< orphan*/  Policy; int /*<<< orphan*/  Note; int /*<<< orphan*/  Realname; int /*<<< orphan*/  HubName; } ;
struct TYPE_20__ {scalar_t__ ServerType; int /*<<< orphan*/ * Cedar; } ;
struct TYPE_19__ {int /*<<< orphan*/  GroupList; } ;
typedef  TYPE_2__ SERVER ;
typedef  TYPE_3__ RPC_SET_GROUP ;
typedef  TYPE_4__ HUB ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_5__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ALog (TYPE_5__*,TYPE_4__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcAddGroup (TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ AcIsGroup (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcLock (TYPE_4__*) ; 
 int /*<<< orphan*/  AcUnlock (TYPE_4__*) ; 
 int /*<<< orphan*/  CHECK_RIGHT ; 
 int /*<<< orphan*/  ERR_GROUP_ALREADY_EXISTS ; 
 int /*<<< orphan*/  ERR_HUB_NOT_FOUND ; 
 int /*<<< orphan*/  ERR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERR_NOT_ENOUGH_RIGHT ; 
 int /*<<< orphan*/  ERR_NOT_FARM_CONTROLLER ; 
 int /*<<< orphan*/  ERR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  ERR_TOO_MANY_GROUP ; 
 TYPE_4__* GetHub (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ GetHubAdminOption (TYPE_4__*,char*) ; 
 scalar_t__ GetServerCapsInt (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  IncrementServerConfigRevision (TYPE_2__*) ; 
 scalar_t__ IsEmptyStr (int /*<<< orphan*/ ) ; 
 int IsSafeStr (int /*<<< orphan*/ ) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NO_SUPPORT_FOR_BRIDGE ; 
 int /*<<< orphan*/ * NewGroup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseGroup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_4__*) ; 
 scalar_t__ SERVER_TYPE_FARM_MEMBER ; 
 int /*<<< orphan*/  SetGroupPolicy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockHubList (int /*<<< orphan*/ *) ; 

UINT StCreateGroup(ADMIN *a, RPC_SET_GROUP *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	HUB *h = NULL;
	UINT ret = ERR_NO_ERROR;

	if (IsEmptyStr(t->Name) || IsSafeStr(t->Name) == false)
	{
		return ERR_INVALID_PARAMETER;
	}

	if (s->ServerType == SERVER_TYPE_FARM_MEMBER)
	{
		return ERR_NOT_FARM_CONTROLLER;
	}

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

	if (a->ServerAdmin == false && GetHubAdminOption(h, "no_change_groups") != 0)
	{
		ReleaseHub(h);
		return ERR_NOT_ENOUGH_RIGHT;
	}

	AcLock(h);
	{
		if (AcIsGroup(h, t->Name))
		{
			ret = ERR_GROUP_ALREADY_EXISTS;
		}
		else
		{
			USERGROUP *g = NewGroup(t->Name, t->Realname, t->Note);
			SetGroupPolicy(g, t->Policy);

			if ((LIST_NUM(h->HubDb->GroupList) >= GetServerCapsInt(a->Server, "i_max_users_per_hub")) ||
				((GetHubAdminOption(h, "max_groups") != 0) && (LIST_NUM(h->HubDb->GroupList) >= GetHubAdminOption(h, "max_groups"))))
			{
				ret = ERR_TOO_MANY_GROUP;
			}
			else
			{
				AcAddGroup(h, g);
			}

			ReleaseGroup(g);

			ALog(a, h, "LA_CREATE_GROUP", t->Name);
		}
	}
	AcUnlock(h);

	ReleaseHub(h);

	IncrementServerConfigRevision(s);

	return ret;
}