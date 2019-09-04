#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hubname ;
typedef  size_t UINT ;
struct TYPE_24__ {TYPE_3__* Server; } ;
struct TYPE_23__ {int /*<<< orphan*/  LinkList; } ;
struct TYPE_22__ {int /*<<< orphan*/  lock; TYPE_2__* ClientSession; scalar_t__ Offline; TYPE_1__* Option; } ;
struct TYPE_21__ {char* HubName; size_t NumLink; TYPE_4__* Links; } ;
struct TYPE_20__ {char* Hostname; char* HubName; int Online; int Connected; int /*<<< orphan*/  LastError; int /*<<< orphan*/  ConnectedTime; int /*<<< orphan*/  AccountName; } ;
struct TYPE_19__ {scalar_t__ ServerType; int /*<<< orphan*/ * Cedar; } ;
struct TYPE_18__ {scalar_t__ ClientStatus; int /*<<< orphan*/  Err; int /*<<< orphan*/  CurrentConnectionEstablishTime; } ;
struct TYPE_17__ {char* Hostname; char* HubName; int /*<<< orphan*/  AccountName; } ;
typedef  TYPE_3__ SERVER ;
typedef  TYPE_4__ RPC_ENUM_LINK_ITEM ;
typedef  TYPE_5__ RPC_ENUM_LINK ;
typedef  TYPE_6__ LINK ;
typedef  TYPE_7__ HUB ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_8__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_RIGHT ; 
 scalar_t__ CLIENT_STATUS_ESTABLISHED ; 
 size_t ERR_HUB_NOT_FOUND ; 
 size_t ERR_NOT_SUPPORTED ; 
 size_t ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeRpcEnumLink (TYPE_5__*) ; 
 TYPE_7__* GetHub (int /*<<< orphan*/ *,char*) ; 
 TYPE_6__* LIST_DATA (int /*<<< orphan*/ ,size_t) ; 
 size_t LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_HUBNAME_LEN ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_7__*) ; 
 scalar_t__ SERVER_TYPE_STANDALONE ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  TickToTime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_5__*,int) ; 
 TYPE_4__* ZeroMalloc (int) ; 

UINT StEnumLink(ADMIN *a, RPC_ENUM_LINK *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	HUB *h;
	char hubname[MAX_HUBNAME_LEN + 1];
	UINT i;

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
	FreeRpcEnumLink(t);
	Zero(t, sizeof(RPC_ENUM_LINK));
	StrCpy(t->HubName, sizeof(t->HubName), hubname);

	LockList(h->LinkList);
	{
		t->NumLink = LIST_NUM(h->LinkList);
		t->Links = ZeroMalloc(sizeof(RPC_ENUM_LINK_ITEM) * t->NumLink);

		for (i = 0;i < LIST_NUM(h->LinkList);i++)
		{
			LINK *k = LIST_DATA(h->LinkList, i);
			RPC_ENUM_LINK_ITEM *e = &t->Links[i];

			Lock(k->lock);
			{
				UniStrCpy(e->AccountName, sizeof(e->AccountName), k->Option->AccountName);
				StrCpy(e->Hostname, sizeof(e->Hostname), k->Option->Hostname);
				StrCpy(e->HubName, sizeof(e->HubName), k->Option->HubName);
				e->Online = k->Offline ? false : true;

				if (e->Online)
				{
					if (k->ClientSession != NULL)
					{
						e->ConnectedTime = TickToTime(k->ClientSession->CurrentConnectionEstablishTime);
						e->Connected = (k->ClientSession->ClientStatus == CLIENT_STATUS_ESTABLISHED);
						e->LastError = k->ClientSession->Err;
					}
				}
			}
			Unlock(k->lock);
		}
	}
	UnlockList(h->LinkList);

	ReleaseHub(h);

	return ERR_NO_ERROR;
}