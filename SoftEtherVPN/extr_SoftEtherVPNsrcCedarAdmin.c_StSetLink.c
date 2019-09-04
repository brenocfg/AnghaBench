#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_15__ ;
typedef  struct TYPE_18__   TYPE_14__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_24__ {int ServerAdmin; TYPE_1__* Server; } ;
struct TYPE_23__ {int /*<<< orphan*/  LinkList; } ;
struct TYPE_22__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * ServerCert; int /*<<< orphan*/  CheckServerCert; TYPE_14__* Option; TYPE_14__* Policy; int /*<<< orphan*/  Auth; int /*<<< orphan*/  ref; } ;
struct TYPE_19__ {int Ver3; int /*<<< orphan*/  AccountName; } ;
struct TYPE_21__ {int /*<<< orphan*/  ServerCert; int /*<<< orphan*/  CheckServerCert; TYPE_15__ Policy; int /*<<< orphan*/  ClientAuth; TYPE_15__* ClientOption; int /*<<< orphan*/  HubName; } ;
struct TYPE_20__ {scalar_t__ ServerType; int /*<<< orphan*/ * Cedar; } ;
struct TYPE_18__ {int RetryInterval; int NoRoutingTracking; int RequireBridgeRoutingMode; int RequireMonitorMode; int /*<<< orphan*/  NumRetry; int /*<<< orphan*/  DeviceName; int /*<<< orphan*/  AccountName; } ;
typedef  TYPE_1__ SERVER ;
typedef  TYPE_2__ RPC_CREATE_LINK ;
typedef  int /*<<< orphan*/  POLICY ;
typedef  TYPE_3__ LINK ;
typedef  TYPE_4__ HUB ;
typedef  int /*<<< orphan*/  CLIENT_OPTION ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_5__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ALog (TYPE_5__*,TYPE_4__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_RIGHT ; 
 int /*<<< orphan*/  CiFreeClientAuth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CloneX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Copy (TYPE_14__*,TYPE_15__*,int) ; 
 int /*<<< orphan*/  CopyClientAuth (int /*<<< orphan*/ ) ; 
 scalar_t__ ERR_HUB_NOT_FOUND ; 
 scalar_t__ ERR_LINK_CANT_CREATE_ON_FARM ; 
 scalar_t__ ERR_NOT_ENOUGH_RIGHT ; 
 scalar_t__ ERR_NOT_SUPPORTED ; 
 scalar_t__ ERR_NO_ERROR ; 
 scalar_t__ ERR_OBJECT_NOT_FOUND ; 
 int /*<<< orphan*/  FreeX (int /*<<< orphan*/ *) ; 
 TYPE_4__* GetHub (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ GetHubAdminOption (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  IncrementServerConfigRevision (TYPE_1__*) ; 
 int /*<<< orphan*/  LINK_DEVICE_NAME ; 
 TYPE_3__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int NUM_POLICY_ITEM_FOR_VER2 ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_4__*) ; 
 int /*<<< orphan*/  ReleaseLink (TYPE_3__*) ; 
 scalar_t__ SERVER_TYPE_STANDALONE ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ UniStrCmpi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

UINT StSetLink(ADMIN *a, RPC_CREATE_LINK *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	HUB *h;
	UINT ret = ERR_NO_ERROR;
	UINT i;
	LINK *k;


	if (s->ServerType != SERVER_TYPE_STANDALONE)
	{
		return ERR_NOT_SUPPORTED;
	}

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

	// Find the link
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

	if (k == NULL)
	{
		// The link is not found
		ReleaseHub(h);
		return ERR_OBJECT_NOT_FOUND;
	}

	ALog(a, h, "LA_SET_LINK", t->ClientOption->AccountName);

	Lock(k->lock);
	{
		// Update the configuration of the link
		if (k->ServerCert != NULL)
		{
			FreeX(k->ServerCert);
			k->ServerCert = NULL;
		}

		Copy(k->Option, t->ClientOption, sizeof(CLIENT_OPTION));
		StrCpy(k->Option->DeviceName, sizeof(k->Option->DeviceName), LINK_DEVICE_NAME);
		k->Option->NumRetry = INFINITE;
		k->Option->RetryInterval = 10;
		k->Option->NoRoutingTracking = true;
		CiFreeClientAuth(k->Auth);
		k->Auth = CopyClientAuth(t->ClientAuth);

		if (t->Policy.Ver3 == false)
		{
			Copy(k->Policy, &t->Policy, sizeof(UINT) * NUM_POLICY_ITEM_FOR_VER2);
		}
		else
		{
			Copy(k->Policy, &t->Policy, sizeof(POLICY));
		}

		k->Option->RequireBridgeRoutingMode = true;	// Enable Bridge / Routing mode
		k->Option->RequireMonitorMode = false;	// Disable monitor mode

		k->CheckServerCert = t->CheckServerCert;
		k->ServerCert = CloneX(t->ServerCert);
	}
	Unlock(k->lock);

	IncrementServerConfigRevision(s);

	ReleaseLink(k);
	ReleaseHub(h);

	return ret;
}