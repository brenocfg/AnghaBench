#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_14__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_21__ {int ServerAdmin; TYPE_1__* Server; } ;
struct TYPE_20__ {int /*<<< orphan*/  CurrentVersion; int /*<<< orphan*/  AccessList; } ;
struct TYPE_17__ {int /*<<< orphan*/  DestUsername; int /*<<< orphan*/  SrcUsername; scalar_t__ Loss; scalar_t__ Delay; scalar_t__ Jitter; } ;
struct TYPE_19__ {TYPE_14__ Access; int /*<<< orphan*/  HubName; } ;
struct TYPE_18__ {scalar_t__ ServerType; int /*<<< orphan*/ * Cedar; } ;
typedef  TYPE_1__ SERVER ;
typedef  TYPE_2__ RPC_ADD_ACCESS ;
typedef  TYPE_3__ HUB ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_4__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ACCESS_LIST_EXCLUDED_PREFIX ; 
 int /*<<< orphan*/  ACCESS_LIST_INCLUDED_PREFIX ; 
 int /*<<< orphan*/  ALog (TYPE_4__*,TYPE_3__*,char*) ; 
 int /*<<< orphan*/  AddAccessList (TYPE_3__*,TYPE_14__*) ; 
 int /*<<< orphan*/  CHECK_RIGHT ; 
 int /*<<< orphan*/  ClearStr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ERR_HUB_NOT_FOUND ; 
 int /*<<< orphan*/  ERR_NOT_ENOUGH_RIGHT ; 
 int /*<<< orphan*/  ERR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  ERR_TOO_MANY_ACCESS_LIST ; 
 TYPE_3__* GetHub (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int GetHubAdminOption (TYPE_3__*,char*) ; 
 int GetServerCapsInt (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  IncrementServerConfigRevision (TYPE_1__*) ; 
 int LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NO_SUPPORT_FOR_BRIDGE ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_3__*) ; 
 scalar_t__ SERVER_TYPE_FARM_MEMBER ; 
 int /*<<< orphan*/  SiHubUpdateProc (TYPE_3__*) ; 
 scalar_t__ StartWith (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockHubList (int /*<<< orphan*/ *) ; 

UINT StAddAccess(ADMIN *a, RPC_ADD_ACCESS *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	HUB *h;
	bool no_jitter = false;
	bool no_include = false;


	NO_SUPPORT_FOR_BRIDGE;
	if (s->ServerType == SERVER_TYPE_FARM_MEMBER)
	{
		return ERR_NOT_SUPPORTED;
	}

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

	no_jitter = GetHubAdminOption(h, "no_delay_jitter_packet_loss");
	no_include = GetHubAdminOption(h, "no_access_list_include_file");

	if (a->ServerAdmin == false && GetHubAdminOption(h, "no_change_access_list") != 0)
	{
		ReleaseHub(h);
		return ERR_NOT_ENOUGH_RIGHT;
	}

	if ((LIST_NUM(h->AccessList) >= GetServerCapsInt(a->Server, "i_max_access_lists") ||
		(GetHubAdminOption(h, "max_accesslists") != 0) && (LIST_NUM(h->AccessList) >= GetHubAdminOption(h, "max_accesslists"))))
	{
		ReleaseHub(h);
		return ERR_TOO_MANY_ACCESS_LIST;
	}

	ALog(a, h, "LA_ADD_ACCESS");

	if (no_jitter)
	{
		t->Access.Jitter = t->Access.Delay = t->Access.Loss = 0;
	}

	if (no_include)
	{
		if (StartWith(t->Access.SrcUsername, ACCESS_LIST_INCLUDED_PREFIX) ||
			StartWith(t->Access.SrcUsername, ACCESS_LIST_EXCLUDED_PREFIX))
		{
			ClearStr(t->Access.SrcUsername, sizeof(t->Access.SrcUsername));
		}

		if (StartWith(t->Access.DestUsername, ACCESS_LIST_INCLUDED_PREFIX) ||
			StartWith(t->Access.DestUsername, ACCESS_LIST_EXCLUDED_PREFIX))
		{
			ClearStr(t->Access.DestUsername, sizeof(t->Access.DestUsername));
		}
	}

	AddAccessList(h, &t->Access);

	h->CurrentVersion++;
	SiHubUpdateProc(h);

	ReleaseHub(h);

	IncrementServerConfigRevision(s);

	return ERR_NO_ERROR;
}