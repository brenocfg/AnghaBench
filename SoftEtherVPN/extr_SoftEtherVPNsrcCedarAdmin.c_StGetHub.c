#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_17__ {TYPE_3__* Server; } ;
struct TYPE_16__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  Type; TYPE_2__* Option; scalar_t__ Offline; int /*<<< orphan*/  Name; } ;
struct TYPE_12__ {int /*<<< orphan*/  NoEnum; int /*<<< orphan*/  MaxSession; } ;
struct TYPE_15__ {int Online; int /*<<< orphan*/  HubType; TYPE_1__ HubOption; int /*<<< orphan*/  HubName; } ;
struct TYPE_14__ {scalar_t__ ServerType; int /*<<< orphan*/ * Cedar; } ;
struct TYPE_13__ {int /*<<< orphan*/  NoEnum; int /*<<< orphan*/  MaxSession; } ;
typedef  TYPE_3__ SERVER ;
typedef  TYPE_4__ RPC_CREATE_HUB ;
typedef  TYPE_5__ HUB ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_6__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_RIGHT ; 
 int /*<<< orphan*/  ERR_HUB_NOT_FOUND ; 
 int /*<<< orphan*/  ERR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERR_NOT_FARM_CONTROLLER ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 TYPE_5__* GetHub (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IsEmptyStr (int /*<<< orphan*/ ) ; 
 int IsSafeStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NO_SUPPORT_FOR_BRIDGE ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_5__*) ; 
 scalar_t__ SERVER_TYPE_FARM_MEMBER ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Zero (TYPE_4__*,int) ; 

UINT StGetHub(ADMIN *a, RPC_CREATE_HUB *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	UINT ret = ERR_NO_ERROR;
	HUB *h;

	if (s->ServerType == SERVER_TYPE_FARM_MEMBER)
	{
		return ERR_NOT_FARM_CONTROLLER;
	}

	if (IsEmptyStr(t->HubName) || IsSafeStr(t->HubName) == false)
	{
		return ERR_INVALID_PARAMETER;
	}

	if (s->ServerType == SERVER_TYPE_FARM_MEMBER)
	{
		return ERR_NOT_FARM_CONTROLLER;
	}

	NO_SUPPORT_FOR_BRIDGE;
	CHECK_RIGHT;

	LockHubList(c);
	{
		h = GetHub(c, t->HubName);
	}
	UnlockHubList(c);

	Zero(t, sizeof(RPC_CREATE_HUB));

	if (h == NULL)
	{
		return ERR_HUB_NOT_FOUND;
	}

	Lock(h->lock);
	{
		StrCpy(t->HubName, sizeof(t->HubName), h->Name);
		t->Online = h->Offline ? false : true;
		t->HubOption.MaxSession = h->Option->MaxSession;
		t->HubOption.NoEnum = h->Option->NoEnum;
		t->HubType = h->Type;
	}
	Unlock(h->lock);

	ReleaseHub(h);

	return ret;
}