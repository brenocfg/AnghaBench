#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_8__ ;
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USERGROUP ;
struct TYPE_32__ {int /*<<< orphan*/  ExpireTime; } ;
typedef  TYPE_3__ USER ;
typedef  scalar_t__ UINT ;
struct TYPE_37__ {int ServerAdmin; TYPE_4__* Server; } ;
struct TYPE_36__ {TYPE_1__* UserX; } ;
struct TYPE_35__ {TYPE_2__* HubDb; } ;
struct TYPE_34__ {scalar_t__ AuthType; int /*<<< orphan*/  Name; int /*<<< orphan*/  GroupName; int /*<<< orphan*/  Policy; int /*<<< orphan*/  ExpireTime; TYPE_7__* AuthData; int /*<<< orphan*/  Note; int /*<<< orphan*/  Realname; int /*<<< orphan*/  HubName; } ;
struct TYPE_33__ {scalar_t__ ServerType; int /*<<< orphan*/ * Cedar; } ;
struct TYPE_31__ {int /*<<< orphan*/  UserList; } ;
struct TYPE_30__ {int is_compatible_bit; } ;
typedef  TYPE_4__ SERVER ;
typedef  TYPE_5__ RPC_SET_USER ;
typedef  TYPE_6__ HUB ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_7__ AUTHUSERCERT ;
typedef  TYPE_8__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ALog (TYPE_8__*,TYPE_6__*,char*,...) ; 
 scalar_t__ AUTHTYPE_NT ; 
 scalar_t__ AUTHTYPE_RADIUS ; 
 scalar_t__ AUTHTYPE_ROOTCERT ; 
 scalar_t__ AUTHTYPE_USERCERT ; 
 int /*<<< orphan*/  AcAddUser (TYPE_6__*,TYPE_3__*) ; 
 int /*<<< orphan*/ * AcGetGroup (TYPE_6__*,int /*<<< orphan*/ ) ; 
 scalar_t__ AcIsUser (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcLock (TYPE_6__*) ; 
 int /*<<< orphan*/  AcUnlock (TYPE_6__*) ; 
 int /*<<< orphan*/  CHECK_RIGHT ; 
 int /*<<< orphan*/  CopyAuthData (TYPE_7__*,scalar_t__) ; 
 scalar_t__ ERR_GROUP_NOT_FOUND ; 
 scalar_t__ ERR_HUB_NOT_FOUND ; 
 scalar_t__ ERR_INTERNAL_ERROR ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NOT_ENOUGH_RIGHT ; 
 scalar_t__ ERR_NOT_RSA_1024 ; 
 scalar_t__ ERR_NOT_SUPPORTED ; 
 scalar_t__ ERR_NOT_SUPPORTED_AUTH_ON_OPENSOURCE ; 
 scalar_t__ ERR_NO_ERROR ; 
 scalar_t__ ERR_TOO_MANY_USER ; 
 scalar_t__ ERR_TOO_MANY_USERS_CREATED ; 
 scalar_t__ ERR_USER_ALREADY_EXISTS ; 
 int /*<<< orphan*/  GSF_DISABLE_RADIUS_AUTH ; 
 scalar_t__ GetGlobalServerFlag (int /*<<< orphan*/ ) ; 
 TYPE_6__* GetHub (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ GetHubAdminOption (TYPE_6__*,char*) ; 
 scalar_t__ GetServerCapsInt (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  IncrementServerConfigRevision (TYPE_4__*) ; 
 scalar_t__ IsEmptyStr (int /*<<< orphan*/ ) ; 
 int IsUserName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JoinUserToGroup (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NO_SUPPORT_FOR_BRIDGE ; 
 TYPE_3__* NewUser (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseGroup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_6__*) ; 
 int /*<<< orphan*/  ReleaseUser (TYPE_3__*) ; 
 scalar_t__ SERVER_TYPE_FARM_MEMBER ; 
 int /*<<< orphan*/  SetUserPolicy (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ SiTooManyUserObjectsInServer (TYPE_4__*,int) ; 
 scalar_t__ StrCmpi (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ StrLen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockHubList (int /*<<< orphan*/ *) ; 

UINT StCreateUser(ADMIN *a, RPC_SET_USER *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	HUB *h = NULL;
	UINT ret = ERR_NO_ERROR;
	USER *u;
	USERGROUP *g = NULL;


	if (IsEmptyStr(t->Name) || IsUserName(t->Name) == false)
	{
		return ERR_INVALID_PARAMETER;
	}

	NO_SUPPORT_FOR_BRIDGE;
	if (s->ServerType == SERVER_TYPE_FARM_MEMBER)
	{
		return ERR_NOT_SUPPORTED;
	}

	CHECK_RIGHT;

	if (GetGlobalServerFlag(GSF_DISABLE_RADIUS_AUTH) != 0)
	{
		if (t->AuthType == AUTHTYPE_USERCERT || t->AuthType == AUTHTYPE_RADIUS || t->AuthType == AUTHTYPE_ROOTCERT || t->AuthType == AUTHTYPE_NT)
		{
			return ERR_NOT_SUPPORTED_AUTH_ON_OPENSOURCE;
		}
	}

	if (t->AuthType == AUTHTYPE_USERCERT)
	{
		AUTHUSERCERT *c = t->AuthData;
		if (c != NULL && c->UserX != NULL &&
			c->UserX->is_compatible_bit == false)
		{
			return ERR_NOT_RSA_1024;
		}
		if (c == NULL || c->UserX == NULL)
		{
			return ERR_INVALID_PARAMETER;
		}
	}

	if (IsUserName(t->Name) == false)
	{
		return ERR_INVALID_PARAMETER;
	}

	if (StrCmpi(t->Name, "*") == 0)
	{
		if (t->AuthType != AUTHTYPE_RADIUS && t->AuthType != AUTHTYPE_NT)
		{
			return ERR_INVALID_PARAMETER;
		}
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

	if (a->ServerAdmin == false && GetHubAdminOption(h, "no_change_users") != 0)
	{
		ReleaseHub(h);
		return ERR_NOT_ENOUGH_RIGHT;
	}

	u = NewUser(t->Name, t->Realname, t->Note, t->AuthType, CopyAuthData(t->AuthData, t->AuthType));
	if (u == NULL)
	{
		ReleaseHub(h);
		return ERR_INTERNAL_ERROR;
	}

	u->ExpireTime = t->ExpireTime;

	SetUserPolicy(u, t->Policy);

	AcLock(h);
	{
		if ((LIST_NUM(h->HubDb->UserList) >= GetServerCapsInt(a->Server, "i_max_users_per_hub")) ||
			((GetHubAdminOption(h, "max_users") != 0) && (LIST_NUM(h->HubDb->UserList) >= GetHubAdminOption(h, "max_users"))))
		{
			ret = ERR_TOO_MANY_USER;
		}
		else if (SiTooManyUserObjectsInServer(s, false))
		{
			ret = ERR_TOO_MANY_USERS_CREATED;
			ALog(a, h, "ERR_128");
		}
		else if (AcIsUser(h, t->Name))
		{
			ret = ERR_USER_ALREADY_EXISTS;
		}
		else
		{
			if (StrLen(t->GroupName) != 0)
			{
				g = AcGetGroup(h, t->GroupName);
				if (g == NULL)
				{
					ret = ERR_GROUP_NOT_FOUND;
				}
			}

			if (ret != ERR_GROUP_NOT_FOUND)
			{
				if (g != NULL)
				{
					JoinUserToGroup(u, g);
					ReleaseGroup(g);
				}

				AcAddUser(h, u);
				ALog(a, h, "LA_CREATE_USER", t->Name);

				IncrementServerConfigRevision(s);
			}
		}
	}
	AcUnlock(h);

	ReleaseUser(u);

	ReleaseHub(h);

	return ret;
}