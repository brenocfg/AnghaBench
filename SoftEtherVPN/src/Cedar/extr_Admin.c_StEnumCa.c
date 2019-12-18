#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hubname ;
struct TYPE_18__ {int /*<<< orphan*/  notAfter; int /*<<< orphan*/  issuer_name; int /*<<< orphan*/  subject_name; } ;
typedef  TYPE_2__ X ;
typedef  size_t UINT ;
struct TYPE_23__ {TYPE_3__* Server; } ;
struct TYPE_22__ {TYPE_1__* HubDb; } ;
struct TYPE_21__ {char* HubName; int NumCa; TYPE_4__* Ca; } ;
struct TYPE_20__ {int /*<<< orphan*/  Expires; int /*<<< orphan*/  IssuerName; int /*<<< orphan*/  SubjectName; int /*<<< orphan*/  Key; } ;
struct TYPE_19__ {scalar_t__ ServerType; int /*<<< orphan*/ * Cedar; } ;
struct TYPE_17__ {int /*<<< orphan*/ * RootCertList; } ;
typedef  TYPE_3__ SERVER ;
typedef  TYPE_4__ RPC_HUB_ENUM_CA_ITEM ;
typedef  TYPE_5__ RPC_HUB_ENUM_CA ;
typedef  TYPE_6__ HUB ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_7__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_RIGHT ; 
 size_t ERR_HUB_NOT_FOUND ; 
 size_t ERR_NOT_FARM_CONTROLLER ; 
 size_t ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeRpcHubEnumCa (TYPE_5__*) ; 
 int /*<<< orphan*/  GetAllNameFromNameEx (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_6__* GetHub (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ *,size_t) ; 
 int LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_HUBNAME_LEN ; 
 int /*<<< orphan*/  NO_SUPPORT_FOR_BRIDGE ; 
 int /*<<< orphan*/  POINTER_TO_KEY (TYPE_2__*) ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_6__*) ; 
 scalar_t__ SERVER_TYPE_FARM_MEMBER ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  UnlockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Zero (TYPE_5__*,int) ; 
 TYPE_4__* ZeroMalloc (int) ; 

UINT StEnumCa(ADMIN *a, RPC_HUB_ENUM_CA *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	HUB *h;
	char hubname[MAX_HUBNAME_LEN + 1];
	UINT i;

	if (s->ServerType == SERVER_TYPE_FARM_MEMBER)
	{
		return ERR_NOT_FARM_CONTROLLER;
	}

	NO_SUPPORT_FOR_BRIDGE;

	StrCpy(hubname, sizeof(hubname), t->HubName);

	FreeRpcHubEnumCa(t);
	Zero(t, sizeof(RPC_HUB_ENUM_CA));

	StrCpy(t->HubName, sizeof(t->HubName), hubname);
	CHECK_RIGHT;

	LockHubList(c);
	{
		h = GetHub(c, hubname);
	}
	UnlockHubList(c);

	if (h == NULL)
	{
		return ERR_HUB_NOT_FOUND;
	}

	Zero(t, sizeof(RPC_HUB_ENUM_CA));
	StrCpy(t->HubName, sizeof(t->HubName), hubname);

	if (h->HubDb->RootCertList != NULL)
	{
		LockList(h->HubDb->RootCertList);
		{
			t->NumCa = LIST_NUM(h->HubDb->RootCertList);
			t->Ca = ZeroMalloc(sizeof(RPC_HUB_ENUM_CA_ITEM) * t->NumCa);

			for (i = 0;i < t->NumCa;i++)
			{
				RPC_HUB_ENUM_CA_ITEM *e = &t->Ca[i];
				X *x = LIST_DATA(h->HubDb->RootCertList, i);

				e->Key = POINTER_TO_KEY(x);
				GetAllNameFromNameEx(e->SubjectName, sizeof(e->SubjectName), x->subject_name);
				GetAllNameFromNameEx(e->IssuerName, sizeof(e->IssuerName), x->issuer_name);
				e->Expires = x->notAfter;
			}
		}
		UnlockList(h->HubDb->RootCertList);
	}

	ReleaseHub(h);

	return ERR_NO_ERROR;
}