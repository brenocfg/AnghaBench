#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_16__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hubname ;
typedef  scalar_t__ UINT ;
struct TYPE_23__ {int /*<<< orphan*/  AccountName; } ;
struct TYPE_22__ {TYPE_1__* Server; } ;
struct TYPE_21__ {int /*<<< orphan*/  LinkList; } ;
struct TYPE_20__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  ServerCert; int /*<<< orphan*/  CheckServerCert; TYPE_16__* Policy; int /*<<< orphan*/  Auth; TYPE_16__* Option; scalar_t__ Offline; int /*<<< orphan*/  ref; } ;
struct TYPE_19__ {char* HubName; int Online; int /*<<< orphan*/  ServerCert; int /*<<< orphan*/  CheckServerCert; TYPE_6__ Policy; int /*<<< orphan*/  ClientAuth; TYPE_6__* ClientOption; } ;
struct TYPE_18__ {scalar_t__ ServerType; int /*<<< orphan*/ * Cedar; } ;
struct TYPE_17__ {int /*<<< orphan*/  AccountName; } ;
typedef  TYPE_1__ SERVER ;
typedef  TYPE_2__ RPC_CREATE_LINK ;
typedef  int /*<<< orphan*/  POLICY ;
typedef  TYPE_3__ LINK ;
typedef  TYPE_4__ HUB ;
typedef  int /*<<< orphan*/  CLIENT_OPTION ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_5__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_RIGHT ; 
 int /*<<< orphan*/  CloneX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Copy (TYPE_6__*,TYPE_16__*,int) ; 
 int /*<<< orphan*/  CopyClientAuth (int /*<<< orphan*/ ) ; 
 scalar_t__ ERR_HUB_NOT_FOUND ; 
 scalar_t__ ERR_LINK_CANT_CREATE_ON_FARM ; 
 scalar_t__ ERR_NOT_SUPPORTED ; 
 scalar_t__ ERR_NO_ERROR ; 
 scalar_t__ ERR_OBJECT_NOT_FOUND ; 
 int /*<<< orphan*/  FreeRpcCreateLink (TYPE_2__*) ; 
 TYPE_4__* GetHub (int /*<<< orphan*/ *,char*) ; 
 TYPE_3__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_4__*) ; 
 int /*<<< orphan*/  ReleaseLink (TYPE_3__*) ; 
 scalar_t__ SERVER_TYPE_STANDALONE ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 scalar_t__ UniStrCmpi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 TYPE_6__* ZeroMalloc (int) ; 

UINT StGetLink(ADMIN *a, RPC_CREATE_LINK *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	HUB *h;
	UINT ret = ERR_NO_ERROR;
	UINT i;
	char hubname[MAX_SIZE];
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

	StrCpy(hubname, sizeof(hubname), t->HubName);
	FreeRpcCreateLink(t);
	Zero(t, sizeof(RPC_CREATE_LINK));
	StrCpy(t->HubName, sizeof(t->HubName), hubname);

	Lock(k->lock);
	{
		// Get configuration
		t->Online = k->Offline ? false : true;
		t->ClientOption = ZeroMalloc(sizeof(CLIENT_OPTION));
		Copy(t->ClientOption, k->Option, sizeof(CLIENT_OPTION));
		t->ClientAuth = CopyClientAuth(k->Auth);
		Copy(&t->Policy, k->Policy, sizeof(POLICY));

		t->CheckServerCert = k->CheckServerCert;
		t->ServerCert = CloneX(k->ServerCert);
	}
	Unlock(k->lock);

	ReleaseLink(k);
	ReleaseHub(h);

	return ret;
}