#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_22__ {int ServerAdmin; TYPE_2__* Server; } ;
struct TYPE_21__ {int /*<<< orphan*/  LinkList; } ;
struct TYPE_20__ {TYPE_1__* Option; int /*<<< orphan*/  lock; int /*<<< orphan*/  ref; } ;
struct TYPE_19__ {int /*<<< orphan*/  NewAccountName; int /*<<< orphan*/  OldAccountName; int /*<<< orphan*/  HubName; } ;
struct TYPE_18__ {scalar_t__ ServerType; int /*<<< orphan*/ * Cedar; } ;
struct TYPE_17__ {int /*<<< orphan*/  AccountName; } ;
typedef  TYPE_2__ SERVER ;
typedef  TYPE_3__ RPC_RENAME_LINK ;
typedef  TYPE_4__ LINK ;
typedef  TYPE_5__ HUB ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_6__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ALog (TYPE_6__*,TYPE_5__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_RIGHT ; 
 scalar_t__ ERR_HUB_NOT_FOUND ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_LINK_ALREADY_EXISTS ; 
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
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_5__*) ; 
 int /*<<< orphan*/  ReleaseLink (TYPE_4__*) ; 
 scalar_t__ SERVER_TYPE_STANDALONE ; 
 scalar_t__ UniIsEmptyStr (int /*<<< orphan*/ ) ; 
 scalar_t__ UniStrCmpi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

UINT StRenameLink(ADMIN *a, RPC_RENAME_LINK *t)
{
	UINT i;
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	HUB *h;
	UINT ret = ERR_NO_ERROR;
	LINK *k;
	bool exists = false;

	if (UniIsEmptyStr(t->OldAccountName) || UniIsEmptyStr(t->NewAccountName))
	{
		return ERR_INVALID_PARAMETER;
	}

	if (s->ServerType != SERVER_TYPE_STANDALONE)
	{
		return ERR_NOT_SUPPORTED;
	}

	CHECK_RIGHT;

	if (UniStrCmpi(t->NewAccountName, t->OldAccountName) == 0)
	{
		// Noop if new name is same to old name
		return ERR_NO_ERROR;
	}

	h = GetHub(c, t->HubName);

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

	// Find specified link
	LockList(h->LinkList);
	{
		for (i = 0;i < LIST_NUM(h->LinkList);i++)
		{
			LINK *kk = LIST_DATA(h->LinkList, i);
			Lock(kk->lock);
			{
				if (UniStrCmpi(kk->Option->AccountName, t->OldAccountName) == 0)
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

		exists = false;

		if (k != NULL)
		{
			// Check whether the new link name is same to other links 
			for (i = 0;i < LIST_NUM(h->LinkList);i++)
			{
				LINK *kk = LIST_DATA(h->LinkList, i);
				Lock(kk->lock);
				{
					if (UniStrCmpi(kk->Option->AccountName, t->NewAccountName) == 0)
					{
						// duplicated
						exists = true;
					}
				}
				Unlock(kk->lock);
			}

			if (exists)
			{
				// Already same name exists
				ret = ERR_LINK_ALREADY_EXISTS;
			}
			else
			{
				// Do rename
				UniStrCpy(k->Option->AccountName, sizeof(k->Option->AccountName), t->NewAccountName);

				ALog(a, h, "LA_RENAME_LINK", t->OldAccountName, t->NewAccountName);

				IncrementServerConfigRevision(s);
			}
		}
	}
	UnlockList(h->LinkList);

	if (k == NULL)
	{
		// specified link is not found
		ReleaseHub(h);
		return ERR_OBJECT_NOT_FOUND;
	}

	ReleaseLink(k);

	ReleaseHub(h);

	return ret;
}