#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_22__ {int ServerAdmin; TYPE_1__* Server; } ;
struct TYPE_21__ {int /*<<< orphan*/  Value; int /*<<< orphan*/  Name; } ;
struct TYPE_20__ {int /*<<< orphan*/  CurrentVersion; int /*<<< orphan*/  Name; int /*<<< orphan*/  AdminOptionList; } ;
struct TYPE_19__ {scalar_t__ NumItem; TYPE_4__* Items; int /*<<< orphan*/  HubName; } ;
struct TYPE_18__ {scalar_t__ ServerType; int /*<<< orphan*/ * Cedar; } ;
typedef  TYPE_1__ SERVER ;
typedef  TYPE_2__ RPC_ADMIN_OPTION ;
typedef  TYPE_3__ HUB ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_4__ ADMIN_OPTION ;
typedef  TYPE_5__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ALog (TYPE_5__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AddHubAdminOptionsDefaults (TYPE_3__*,int) ; 
 int /*<<< orphan*/  CHECK_RIGHT ; 
 int /*<<< orphan*/  DeleteAllHubAdminOption (TYPE_3__*,int) ; 
 size_t ERR_HUB_NOT_FOUND ; 
 size_t ERR_NOT_ENOUGH_RIGHT ; 
 size_t ERR_NOT_SUPPORTED ; 
 size_t ERR_NO_ERROR ; 
 size_t ERR_TOO_MANT_ITEMS ; 
 TYPE_3__* GetHub (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int GetHubAdminOption (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  IncrementServerConfigRevision (TYPE_1__*) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  LockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 scalar_t__ MAX_HUB_ADMIN_OPTIONS ; 
 int /*<<< orphan*/  NO_SUPPORT_FOR_BRIDGE ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_3__*) ; 
 scalar_t__ SERVER_TYPE_FARM_MEMBER ; 
 int /*<<< orphan*/  SiHubUpdateProc (TYPE_3__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 TYPE_4__* ZeroMalloc (int) ; 

UINT StSetHubAdminOptions(ADMIN *a, RPC_ADMIN_OPTION *t)
{
	UINT i;
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	HUB *h;

	bool not_server_admin = false;


	if (t->NumItem > MAX_HUB_ADMIN_OPTIONS)
	{
		return ERR_TOO_MANT_ITEMS;
	}

	NO_SUPPORT_FOR_BRIDGE;
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

	if (GetHubAdminOption(h, "allow_hub_admin_change_option") == false
		&& not_server_admin)
	{
		// Insufficient permission
		ReleaseHub(h);

		return ERR_NOT_ENOUGH_RIGHT;
	}

	LockList(h->AdminOptionList);
	{
		DeleteAllHubAdminOption(h, false);

		for (i = 0;i < t->NumItem;i++)
		{
			ADMIN_OPTION *e = &t->Items[i];
			ADMIN_OPTION *a = ZeroMalloc(sizeof(ADMIN_OPTION));

			StrCpy(a->Name, sizeof(a->Name), e->Name);
			a->Value = e->Value;

			Insert(h->AdminOptionList, a);
		}

		AddHubAdminOptionsDefaults(h, false);
	}
	UnlockList(h->AdminOptionList);

	ALog(a, NULL, "LA_SET_HUB_ADMIN_OPTION", h->Name);

	h->CurrentVersion++;
	SiHubUpdateProc(h);

	ReleaseHub(h);

	IncrementServerConfigRevision(s);

	return ERR_NO_ERROR;
}