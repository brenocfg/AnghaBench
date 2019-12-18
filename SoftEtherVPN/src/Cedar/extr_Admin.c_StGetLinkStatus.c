#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
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
struct TYPE_24__ {TYPE_3__* Server; } ;
struct TYPE_23__ {int /*<<< orphan*/  LinkList; } ;
struct TYPE_22__ {int Offline; int /*<<< orphan*/  lock; TYPE_2__* ClientSession; int /*<<< orphan*/  ref; TYPE_1__* Option; } ;
struct TYPE_21__ {char* HubName; int /*<<< orphan*/  Status; int /*<<< orphan*/ * AccountName; } ;
struct TYPE_20__ {scalar_t__ ServerType; int /*<<< orphan*/ * Cedar; } ;
struct TYPE_19__ {int /*<<< orphan*/  ref; } ;
struct TYPE_18__ {int /*<<< orphan*/  AccountName; } ;
typedef  TYPE_2__ SESSION ;
typedef  TYPE_3__ SERVER ;
typedef  TYPE_4__ RPC_LINK_STATUS ;
typedef  TYPE_5__ LINK ;
typedef  TYPE_6__ HUB ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_7__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_RIGHT ; 
 int /*<<< orphan*/  CiGetSessionStatus (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ ERR_HUB_NOT_FOUND ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_LINK_IS_OFFLINE ; 
 scalar_t__ ERR_NOT_SUPPORTED ; 
 scalar_t__ ERR_NO_ERROR ; 
 scalar_t__ ERR_OBJECT_NOT_FOUND ; 
 int /*<<< orphan*/  FreeRpcLinkStatus (TYPE_4__*) ; 
 TYPE_6__* GetHub (int /*<<< orphan*/ *,char*) ; 
 TYPE_5__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_ACCOUNT_NAME_LEN ; 
 int /*<<< orphan*/  MAX_HUBNAME_LEN ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_6__*) ; 
 int /*<<< orphan*/  ReleaseLink (TYPE_5__*) ; 
 int /*<<< orphan*/  ReleaseSession (TYPE_2__*) ; 
 scalar_t__ SERVER_TYPE_STANDALONE ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 scalar_t__ UniIsEmptyStr (int /*<<< orphan*/ *) ; 
 scalar_t__ UniStrCmpi (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_4__*,int) ; 

UINT StGetLinkStatus(ADMIN *a, RPC_LINK_STATUS *t)
{
	UINT i;
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	HUB *h;
	UINT ret = ERR_NO_ERROR;
	char hubname[MAX_HUBNAME_LEN + 1];
	wchar_t accountname[MAX_ACCOUNT_NAME_LEN + 1];
	LINK *k;
	SESSION *sess;

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

	StrCpy(hubname, sizeof(hubname), t->HubName);
	UniStrCpy(accountname, sizeof(accountname), t->AccountName);
	FreeRpcLinkStatus(t);
	Zero(t, sizeof(RPC_LINK_STATUS));
	StrCpy(t->HubName, sizeof(t->HubName), hubname);
	UniStrCpy(t->AccountName, sizeof(t->AccountName), accountname);

	k = NULL;

	// Find the link
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
		// Specified link is not found
		ReleaseHub(h);

		return ERR_OBJECT_NOT_FOUND;
	}

	// Get status information from session
	Lock(k->lock);
	{
		sess = k->ClientSession;
		if (sess != NULL)
		{
			AddRef(sess->ref);
		}
	}
	Unlock(k->lock);

	if (sess != NULL && k->Offline == false)
	{
		CiGetSessionStatus(&t->Status, sess);
	}
	else
	{
		ret = ERR_LINK_IS_OFFLINE;
	}
	ReleaseSession(sess);

	ReleaseLink(k);
	ReleaseHub(h);

	return ret;
}