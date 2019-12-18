#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  hubname ;
typedef  scalar_t__ UINT ;
struct TYPE_19__ {int ServerAdmin; TYPE_2__* Server; } ;
struct TYPE_18__ {int Me; } ;
struct TYPE_17__ {int /*<<< orphan*/  Name; int /*<<< orphan*/  HubName; } ;
struct TYPE_16__ {scalar_t__ ServerType; int /*<<< orphan*/  FarmMemberList; int /*<<< orphan*/ * Cedar; } ;
struct TYPE_15__ {scalar_t__ L3SwitchMode; scalar_t__ BridgeMode; scalar_t__ SecureNATMode; scalar_t__ LinkModeServer; } ;
typedef  TYPE_1__ SESSION ;
typedef  TYPE_2__ SERVER ;
typedef  TYPE_3__ RPC_DELETE_SESSION ;
typedef  int /*<<< orphan*/  HUB ;
typedef  TYPE_4__ FARM_MEMBER ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_5__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ALog (TYPE_5__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_RIGHT ; 
 scalar_t__ ERR_BRIDGE_CANT_DISCONNECT ; 
 scalar_t__ ERR_HUB_NOT_FOUND ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_LAYER3_CANT_DISCONNECT ; 
 scalar_t__ ERR_LINK_CANT_DISCONNECT ; 
 scalar_t__ ERR_NOT_ENOUGH_RIGHT ; 
 scalar_t__ ERR_NO_ERROR ; 
 scalar_t__ ERR_OBJECT_NOT_FOUND ; 
 scalar_t__ ERR_SNAT_CANT_DISCONNECT ; 
 int /*<<< orphan*/ * GetHub (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ GetHubAdminOption (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* GetSessionByName (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ IsEmptyStr (int /*<<< orphan*/ ) ; 
 TYPE_4__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_HUBNAME_LEN ; 
 int /*<<< orphan*/  MAX_SESSION_NAME_LEN ; 
 int /*<<< orphan*/  ReleaseHub (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseSession (TYPE_1__*) ; 
 scalar_t__ SERVER_TYPE_FARM_CONTROLLER ; 
 int /*<<< orphan*/  SiCallDeleteSession (TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StopSession (TYPE_1__*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

UINT StDeleteSession(ADMIN *a, RPC_DELETE_SESSION *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	HUB *h = NULL;
	UINT ret = ERR_NO_ERROR;
	char hubname[MAX_HUBNAME_LEN + 1];
	char name[MAX_SESSION_NAME_LEN + 1];
	SESSION *sess;

	if (IsEmptyStr(t->Name))
	{
		return ERR_INVALID_PARAMETER;
	}

	StrCpy(hubname, sizeof(hubname), t->HubName);
	StrCpy(name, sizeof(name), t->Name);

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

	if (a->ServerAdmin == false && GetHubAdminOption(h, "no_disconnect_session") != 0)
	{
		ReleaseHub(h);
		return ERR_NOT_ENOUGH_RIGHT;
	}

	sess = GetSessionByName(h, name);

	if (sess == NULL)
	{
		if (s->ServerType == SERVER_TYPE_FARM_CONTROLLER)
		{
			// Cluster controller
			UINT i;
			LockList(s->FarmMemberList);
			{
				for (i = 0;i < LIST_NUM(s->FarmMemberList);i++)
				{
					FARM_MEMBER *f = LIST_DATA(s->FarmMemberList, i);
					if (f->Me == false)
					{
						// Try to disconnect
						SiCallDeleteSession(s, f, t->HubName, t->Name);
					}
				}
			}
			UnlockList(s->FarmMemberList);
		}
		else
		{
			ret = ERR_OBJECT_NOT_FOUND;
		}
	}
	else
	{
		if (sess->LinkModeServer)
		{
			ret = ERR_LINK_CANT_DISCONNECT;
		}
		else if (sess->SecureNATMode)
		{
			ret = ERR_SNAT_CANT_DISCONNECT;
		}
		else if (sess->BridgeMode)
		{
			ret = ERR_BRIDGE_CANT_DISCONNECT;
		}
		else if (sess->L3SwitchMode)
		{
			ret = ERR_LAYER3_CANT_DISCONNECT;
		}
		else
		{
			StopSession(sess);
		}
		ReleaseSession(sess);
	}

	if (ret != ERR_NO_ERROR)
	{
		ALog(a, h, "LA_DELETE_SESSION", t->Name);
	}

	ReleaseHub(h);

	return ret;
}