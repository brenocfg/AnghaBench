#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_14__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_27__ {int ServerAdmin; TYPE_2__* Server; } ;
struct TYPE_26__ {int /*<<< orphan*/  LinkList; } ;
struct TYPE_25__ {int Offline; int /*<<< orphan*/  ServerCert; int /*<<< orphan*/  CheckServerCert; int /*<<< orphan*/  lock; int /*<<< orphan*/  ref; TYPE_1__* Option; } ;
struct TYPE_24__ {int /*<<< orphan*/  ServerCert; int /*<<< orphan*/  CheckServerCert; int /*<<< orphan*/  Policy; int /*<<< orphan*/  ClientAuth; TYPE_14__* ClientOption; int /*<<< orphan*/  HubName; } ;
struct TYPE_23__ {scalar_t__ ServerType; int /*<<< orphan*/ * Cedar; } ;
struct TYPE_22__ {int /*<<< orphan*/  AccountName; } ;
struct TYPE_21__ {int /*<<< orphan*/  AccountName; } ;
typedef  TYPE_2__ SERVER ;
typedef  TYPE_3__ RPC_CREATE_LINK ;
typedef  TYPE_4__ LINK ;
typedef  TYPE_5__ HUB ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_6__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ALog (TYPE_6__*,TYPE_5__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_RIGHT ; 
 int /*<<< orphan*/  CloneX (int /*<<< orphan*/ ) ; 
 scalar_t__ ERR_HUB_NOT_FOUND ; 
 scalar_t__ ERR_INTERNAL_ERROR ; 
 scalar_t__ ERR_LINK_ALREADY_EXISTS ; 
 scalar_t__ ERR_LINK_CANT_CREATE_ON_FARM ; 
 scalar_t__ ERR_NOT_ENOUGH_RIGHT ; 
 scalar_t__ ERR_NO_ERROR ; 
 TYPE_5__* GetHub (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ GetHubAdminOption (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  IncrementServerConfigRevision (TYPE_2__*) ; 
 TYPE_4__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 TYPE_4__* NewLink (int /*<<< orphan*/ *,TYPE_5__*,TYPE_14__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_5__*) ; 
 int /*<<< orphan*/  ReleaseLink (TYPE_4__*) ; 
 scalar_t__ SERVER_TYPE_STANDALONE ; 
 int /*<<< orphan*/  SetLinkOffline (TYPE_4__*) ; 
 scalar_t__ UniStrCmpi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

UINT StCreateLink(ADMIN *a, RPC_CREATE_LINK *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	HUB *h;
	UINT ret = ERR_NO_ERROR;
	UINT i;
	LINK *k;

	CHECK_RIGHT;


	if (s->ServerType != SERVER_TYPE_STANDALONE)
	{
		return ERR_LINK_CANT_CREATE_ON_FARM;
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

	if (a->ServerAdmin == false && GetHubAdminOption(h, "no_cascade") != 0)
	{
		ReleaseHub(h);
		return ERR_NOT_ENOUGH_RIGHT;
	}

	k = NULL;

	// Check for existing a link which has same name
	LockList(h->LinkList);
	{
		for (i = 0;i < LIST_NUM(h->LinkList);i++)
		{
			LINK *kk = LIST_DATA(h->LinkList, i);
			Lock(kk->lock);
			{
				if (UniStrCmpi(kk->Option->AccountName, t->ClientOption->AccountName) == 0)
				{
					k = kk;
					AddRef(kk->ref);
				}
			}
			Unlock(kk->lock);

			if (k != NULL)
			{
				break;
			}
		}
	}
	UnlockList(h->LinkList);

	if (k != NULL)
	{
		// There is a link which has same name
		ReleaseLink(k);
		ReleaseHub(h);
		return ERR_LINK_ALREADY_EXISTS;
	}

	ALog(a, h, "LA_CREATE_LINK", t->ClientOption->AccountName);

	// Create a new link
	k = NewLink(c, h, t->ClientOption, t->ClientAuth, &t->Policy);

	if (k == NULL)
	{
		// Link creation failed
		ret = ERR_INTERNAL_ERROR;
	}
	else
	{
		// setting of verifying server certification
		// 
		k->CheckServerCert = t->CheckServerCert;
		k->ServerCert = CloneX(t->ServerCert);

		// stay this off-line
		k->Offline = false;
		SetLinkOffline(k);
		ReleaseLink(k);

		IncrementServerConfigRevision(s);
	}

	ReleaseHub(h);

	return ret;
}