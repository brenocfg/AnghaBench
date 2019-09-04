#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_17__ {int ServerAdmin; TYPE_1__* Server; } ;
struct TYPE_16__ {int /*<<< orphan*/  CurrentVersion; int /*<<< orphan*/  Name; int /*<<< orphan*/  lock; int /*<<< orphan*/  Option; } ;
struct TYPE_15__ {scalar_t__ NumItem; int /*<<< orphan*/  HubName; } ;
struct TYPE_14__ {scalar_t__ ServerType; int /*<<< orphan*/ * Cedar; } ;
typedef  TYPE_1__ SERVER ;
typedef  TYPE_2__ RPC_ADMIN_OPTION ;
typedef  TYPE_3__ HUB ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_4__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ALog (TYPE_4__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_RIGHT ; 
 int /*<<< orphan*/  DataToHubOptionStruct (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ERR_HUB_NOT_FOUND ; 
 int /*<<< orphan*/  ERR_NOT_ENOUGH_RIGHT ; 
 int /*<<< orphan*/  ERR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  ERR_TOO_MANT_ITEMS ; 
 TYPE_3__* GetHub (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ GetHubAdminOption (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  IncrementServerConfigRevision (TYPE_1__*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHubList (int /*<<< orphan*/ *) ; 
 scalar_t__ MAX_HUB_ADMIN_OPTIONS ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_3__*) ; 
 scalar_t__ SERVER_TYPE_FARM_MEMBER ; 
 int /*<<< orphan*/  SiHubUpdateProc (TYPE_3__*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockHubList (int /*<<< orphan*/ *) ; 

UINT StSetHubExtOptions(ADMIN *a, RPC_ADMIN_OPTION *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	HUB *h;

	bool not_server_admin = false;

	if (t->NumItem > MAX_HUB_ADMIN_OPTIONS)
	{
		return ERR_TOO_MANT_ITEMS;
	}

	if (s->ServerType == SERVER_TYPE_FARM_MEMBER)
	{
		return ERR_NOT_SUPPORTED;
	}


	CHECK_RIGHT;

	if (a->ServerAdmin == false)
	{
		not_server_admin = true;
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

	if (GetHubAdminOption(h, "deny_hub_admin_change_ext_option") && not_server_admin)
	{
		// Insufficient permission
		ReleaseHub(h);

		return ERR_NOT_ENOUGH_RIGHT;
	}

	// Update setting
	Lock(h->lock);
	{
		DataToHubOptionStruct(h->Option, t);
	}
	Unlock(h->lock);

	ALog(a, NULL, "LA_SET_HUB_EXT_OPTION", h->Name);

	h->CurrentVersion++;
	SiHubUpdateProc(h);

	ReleaseHub(h);

	IncrementServerConfigRevision(s);

	return ERR_NO_ERROR;
}