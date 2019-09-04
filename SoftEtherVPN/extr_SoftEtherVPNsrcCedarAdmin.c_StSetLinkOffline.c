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

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  hubname ;
typedef  int /*<<< orphan*/  accountname ;
typedef  scalar_t__ UINT ;
struct TYPE_23__ {int ServerAdmin; TYPE_2__* Server; } ;
struct TYPE_22__ {int /*<<< orphan*/  LinkList; } ;
struct TYPE_21__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  ref; TYPE_1__* Option; } ;
struct TYPE_20__ {int /*<<< orphan*/  AccountName; int /*<<< orphan*/  HubName; } ;
struct TYPE_19__ {scalar_t__ ServerType; int /*<<< orphan*/ * Cedar; } ;
struct TYPE_18__ {int /*<<< orphan*/  AccountName; } ;
typedef  TYPE_2__ SERVER ;
typedef  TYPE_3__ RPC_LINK ;
typedef  TYPE_4__ LINK ;
typedef  TYPE_5__ HUB ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_6__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ALog (TYPE_6__*,TYPE_5__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_RIGHT ; 
 scalar_t__ ERR_HUB_NOT_FOUND ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NOT_ENOUGH_RIGHT ; 
 scalar_t__ ERR_NOT_SUPPORTED ; 
 scalar_t__ ERR_NO_ERROR ; 
 scalar_t__ ERR_OBJECT_NOT_FOUND ; 
 TYPE_5__* GetHub (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ GetHubAdminOption (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  IncrementServerConfigRevision (TYPE_2__*) ; 
 TYPE_4__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_ACCOUNT_NAME_LEN ; 
 int /*<<< orphan*/  MAX_HUBNAME_LEN ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_5__*) ; 
 int /*<<< orphan*/  ReleaseLink (TYPE_4__*) ; 
 scalar_t__ SERVER_TYPE_STANDALONE ; 
 int /*<<< orphan*/  SetLinkOffline (TYPE_4__*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ UniIsEmptyStr (int /*<<< orphan*/ ) ; 
 scalar_t__ UniStrCmpi (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

UINT StSetLinkOffline(ADMIN *a, RPC_LINK *t)
{
	UINT i;
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	HUB *h;
	UINT ret = ERR_NO_ERROR;
	char hubname[MAX_HUBNAME_LEN + 1];
	wchar_t accountname[MAX_ACCOUNT_NAME_LEN + 1];
	LINK *k;


	if (UniIsEmptyStr(t->AccountName))
	{
		return ERR_INVALID_PARAMETER;
	}

	if (s->ServerType != SERVER_TYPE_STANDALONE)
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

	if (a->ServerAdmin == false && GetHubAdminOption(h, "no_cascade") != 0)
	{
		ReleaseHub(h);
		return ERR_NOT_ENOUGH_RIGHT;
	}

	StrCpy(hubname, sizeof(hubname), t->HubName);
	UniStrCpy(accountname, sizeof(accountname), t->AccountName);
	k = NULL;

	// Find specified link
	LockList(h->LinkList);
	{
		for (i = 0;i < LIST_NUM(h->LinkList);i++)
		{
			LINK *kk = LIST_DATA(h->LinkList, i);
			Lock(kk->lock);
			{
				if (UniStrCmpi(kk->Option->AccountName, accountname) == 0)
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
		// Link is not found
		ReleaseHub(h);

		return ERR_OBJECT_NOT_FOUND;
	}

	ALog(a, h, "LA_SET_LINK_OFFLINE", t->AccountName);

	SetLinkOffline(k);

	IncrementServerConfigRevision(s);

	ReleaseLink(k);
	ReleaseHub(h);

	return ret;
}