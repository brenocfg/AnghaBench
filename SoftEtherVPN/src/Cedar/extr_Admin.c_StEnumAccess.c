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
typedef  int /*<<< orphan*/  hubname ;
typedef  size_t UINT ;
struct TYPE_18__ {int /*<<< orphan*/  UniqueId; } ;
struct TYPE_17__ {TYPE_1__* Server; } ;
struct TYPE_16__ {int /*<<< orphan*/  AccessList; } ;
struct TYPE_15__ {char* HubName; size_t NumAccess; TYPE_5__* Accesses; } ;
struct TYPE_14__ {scalar_t__ ServerType; int /*<<< orphan*/ * Cedar; } ;
typedef  TYPE_1__ SERVER ;
typedef  TYPE_2__ RPC_ENUM_ACCESS_LIST ;
typedef  TYPE_3__ HUB ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_4__ ADMIN ;
typedef  TYPE_5__ ACCESS ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_RIGHT ; 
 int /*<<< orphan*/  Copy (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 size_t ERR_HUB_NOT_FOUND ; 
 size_t ERR_NOT_SUPPORTED ; 
 size_t ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeRpcEnumAccessList (TYPE_2__*) ; 
 TYPE_3__* GetHub (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  HashPtrToUINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_DATA (int /*<<< orphan*/ ,size_t) ; 
 size_t LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_HUBNAME_LEN ; 
 int /*<<< orphan*/  NO_SUPPORT_FOR_BRIDGE ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_3__*) ; 
 scalar_t__ SERVER_TYPE_FARM_MEMBER ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  UnlockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 TYPE_5__* ZeroMalloc (int) ; 

UINT StEnumAccess(ADMIN *a, RPC_ENUM_ACCESS_LIST *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	HUB *h;
	UINT i;
	char hubname[MAX_HUBNAME_LEN + 1];

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

	StrCpy(hubname, sizeof(hubname), t->HubName);
	FreeRpcEnumAccessList(t);
	Zero(t, sizeof(RPC_ENUM_ACCESS_LIST));
	StrCpy(t->HubName, sizeof(t->HubName), hubname);

	LockList(h->AccessList);
	{
		t->NumAccess = LIST_NUM(h->AccessList);
		t->Accesses = ZeroMalloc(sizeof(ACCESS) * t->NumAccess);

		for (i = 0;i < LIST_NUM(h->AccessList);i++)
		{
			ACCESS *a = &t->Accesses[i];
			Copy(a, LIST_DATA(h->AccessList, i), sizeof(ACCESS));
			a->UniqueId = HashPtrToUINT(LIST_DATA(h->AccessList, i));
		}
	}
	UnlockList(h->AccessList);

	ReleaseHub(h);

	return ERR_NO_ERROR;
}