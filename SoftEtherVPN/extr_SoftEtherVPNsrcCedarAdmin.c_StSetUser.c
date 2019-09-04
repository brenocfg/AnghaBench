#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USERGROUP ;
struct TYPE_18__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  UpdatedTime; int /*<<< orphan*/  ExpireTime; void* Note; void* RealName; } ;
typedef  TYPE_2__ USER ;
typedef  scalar_t__ UINT ;
struct TYPE_22__ {int ServerAdmin; TYPE_3__* Server; } ;
struct TYPE_21__ {TYPE_1__* UserX; } ;
struct TYPE_20__ {scalar_t__ AuthType; int /*<<< orphan*/  Name; int /*<<< orphan*/  Policy; int /*<<< orphan*/  ExpireTime; TYPE_5__* AuthData; int /*<<< orphan*/  Note; int /*<<< orphan*/  Realname; int /*<<< orphan*/  GroupName; int /*<<< orphan*/  HubName; } ;
struct TYPE_19__ {scalar_t__ ServerType; int /*<<< orphan*/ * Cedar; } ;
struct TYPE_17__ {int is_compatible_bit; } ;
typedef  TYPE_3__ SERVER ;
typedef  TYPE_4__ RPC_SET_USER ;
typedef  int /*<<< orphan*/  HUB ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_5__ AUTHUSERCERT ;
typedef  TYPE_6__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ALog (TYPE_6__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ AUTHTYPE_NT ; 
 scalar_t__ AUTHTYPE_RADIUS ; 
 scalar_t__ AUTHTYPE_ROOTCERT ; 
 scalar_t__ AUTHTYPE_USERCERT ; 
 int /*<<< orphan*/ * AcGetGroup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* AcGetUser (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcUnlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CHECK_RIGHT ; 
 int /*<<< orphan*/  CopyAuthData (TYPE_5__*,scalar_t__) ; 
 scalar_t__ ERR_GROUP_NOT_FOUND ; 
 scalar_t__ ERR_HUB_NOT_FOUND ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NOT_ENOUGH_RIGHT ; 
 scalar_t__ ERR_NOT_RSA_1024 ; 
 scalar_t__ ERR_NOT_SUPPORTED ; 
 scalar_t__ ERR_NOT_SUPPORTED_AUTH_ON_OPENSOURCE ; 
 scalar_t__ ERR_NO_ERROR ; 
 scalar_t__ ERR_OBJECT_NOT_FOUND ; 
 int /*<<< orphan*/  Free (void*) ; 
 int /*<<< orphan*/  GSF_DISABLE_RADIUS_AUTH ; 
 scalar_t__ GetGlobalServerFlag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GetHub (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ GetHubAdminOption (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  IncrementServerConfigRevision (TYPE_3__*) ; 
 scalar_t__ IsEmptyStr (int /*<<< orphan*/ ) ; 
 int IsUserName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JoinUserToGroup (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NO_SUPPORT_FOR_BRIDGE ; 
 int /*<<< orphan*/  ReleaseGroup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseHub (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseUser (TYPE_2__*) ; 
 scalar_t__ SERVER_TYPE_FARM_MEMBER ; 
 int /*<<< orphan*/  SetUserAuthData (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetUserPolicy (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ StrCmpi (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ StrLen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SystemTime64 () ; 
 void* UniCopyStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockHubList (int /*<<< orphan*/ *) ; 

UINT StSetUser(ADMIN *a, RPC_SET_USER *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	HUB *h = NULL;
	UINT ret = ERR_NO_ERROR;
	USER *u = NULL;
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

	if (StrCmpi(t->Name, "*") == 0)
	{
		if (t->AuthType != AUTHTYPE_RADIUS && t->AuthType != AUTHTYPE_NT)
		{
			return ERR_INVALID_PARAMETER;
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

	AcLock(h);
	{
		u = AcGetUser(h, t->Name);
		if (u == NULL)
		{
			ret = ERR_OBJECT_NOT_FOUND;
		}
		else
		{
			Lock(u->lock);
			{
				if (StrLen(t->GroupName) != 0)
				{
					g = AcGetGroup(h, t->GroupName);

					if (g != NULL)
					{
						JoinUserToGroup(u, g);
						ReleaseGroup(g);
					}
					else
					{
						ret = ERR_GROUP_NOT_FOUND;
					}
				}
				else
				{
					JoinUserToGroup(u, NULL);
				}

				if (ret != ERR_GROUP_NOT_FOUND)
				{
					Free(u->RealName);
					Free(u->Note);
					u->RealName = UniCopyStr(t->Realname);
					u->Note = UniCopyStr(t->Note);
					SetUserAuthData(u, t->AuthType, CopyAuthData(t->AuthData, t->AuthType));
					u->ExpireTime = t->ExpireTime;
					u->UpdatedTime = SystemTime64();

					SetUserPolicy(u, t->Policy);
				}
			}
			Unlock(u->lock);

			IncrementServerConfigRevision(s);

			ReleaseUser(u);
		}
	}
	AcUnlock(h);

	if (ret == ERR_NO_ERROR)
	{
		ALog(a, h, "LA_SET_USER", t->Name);
	}

	ReleaseHub(h);

	return ret;
}