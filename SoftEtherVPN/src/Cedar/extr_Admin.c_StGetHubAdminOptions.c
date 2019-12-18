#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_18__ {TYPE_1__* Server; } ;
struct TYPE_17__ {int /*<<< orphan*/  Name; int /*<<< orphan*/  Descrption; int /*<<< orphan*/  Value; } ;
struct TYPE_16__ {int /*<<< orphan*/  AdminOptionList; int /*<<< orphan*/  Name; } ;
struct TYPE_15__ {int NumItem; TYPE_4__* Items; int /*<<< orphan*/  HubName; } ;
struct TYPE_14__ {scalar_t__ ServerType; int /*<<< orphan*/ * Cedar; } ;
typedef  TYPE_1__ SERVER ;
typedef  TYPE_2__ RPC_ADMIN_OPTION ;
typedef  TYPE_3__ HUB ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_4__ ADMIN_OPTION ;
typedef  TYPE_5__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_RIGHT ; 
 size_t ERR_HUB_NOT_FOUND ; 
 size_t ERR_NOT_SUPPORTED ; 
 size_t ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeRpcAdminOption (TYPE_2__*) ; 
 TYPE_3__* GetHub (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetHubAdminOptionHelpString (int /*<<< orphan*/ ) ; 
 TYPE_4__* LIST_DATA (int /*<<< orphan*/ ,size_t) ; 
 int LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NO_SUPPORT_FOR_BRIDGE ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_3__*) ; 
 scalar_t__ SERVER_TYPE_FARM_MEMBER ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 TYPE_4__* ZeroMalloc (int) ; 

UINT StGetHubAdminOptions(ADMIN *a, RPC_ADMIN_OPTION *t)
{
	UINT i;
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	HUB *h;

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

	FreeRpcAdminOption(t);
	Zero(t, sizeof(RPC_ADMIN_OPTION));

	StrCpy(t->HubName, sizeof(t->HubName), h->Name);

	LockList(h->AdminOptionList);
	{
		t->NumItem = LIST_NUM(h->AdminOptionList);
		t->Items = ZeroMalloc(sizeof(ADMIN_OPTION) * t->NumItem);

		for (i = 0;i < t->NumItem;i++)
		{
			ADMIN_OPTION *a = LIST_DATA(h->AdminOptionList, i);
			ADMIN_OPTION *e = &t->Items[i];

			StrCpy(e->Name, sizeof(e->Name), a->Name);
			e->Value = a->Value;
			UniStrCpy(e->Descrption, sizeof(e->Descrption), GetHubAdminOptionHelpString(e->Name));
		}
	}
	UnlockList(h->AdminOptionList);

	ReleaseHub(h);

	return ERR_NO_ERROR;
}