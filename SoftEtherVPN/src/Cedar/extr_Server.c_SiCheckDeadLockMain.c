#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_9__ ;
typedef  struct TYPE_36__   TYPE_8__ ;
typedef  struct TYPE_35__   TYPE_7__ ;
typedef  struct TYPE_34__   TYPE_6__ ;
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_13__ ;
typedef  struct TYPE_27__   TYPE_12__ ;
typedef  struct TYPE_26__   TYPE_11__ ;
typedef  struct TYPE_25__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_37__ {int /*<<< orphan*/ * lock; } ;
struct TYPE_36__ {int /*<<< orphan*/ * lock; } ;
struct TYPE_35__ {int /*<<< orphan*/ * lock; } ;
struct TYPE_34__ {int /*<<< orphan*/ * lock; } ;
struct TYPE_33__ {int /*<<< orphan*/ * lock; } ;
struct TYPE_32__ {int /*<<< orphan*/ * lock; } ;
struct TYPE_31__ {int /*<<< orphan*/ * lock; } ;
struct TYPE_30__ {int /*<<< orphan*/ * lock; } ;
struct TYPE_29__ {int /*<<< orphan*/ * lock; } ;
struct TYPE_28__ {TYPE_9__* L3SwList; TYPE_8__* LocalBridgeList; TYPE_7__* TrafficDiffList; int /*<<< orphan*/ * TrafficLock; TYPE_6__* CaList; TYPE_5__* ConnectionList; TYPE_12__* ListenerList; TYPE_4__* HubList; } ;
struct TYPE_27__ {int /*<<< orphan*/ * lock; } ;
struct TYPE_26__ {int /*<<< orphan*/  ref; } ;
struct TYPE_25__ {int /*<<< orphan*/ * TasksFromFarmControllerLock; int /*<<< orphan*/ * CapsCacheLock; TYPE_3__* HubCreateHistoryList; TYPE_2__* FarmMemberList; int /*<<< orphan*/ * lock; TYPE_1__* ServerListenerList; TYPE_13__* Cedar; } ;
typedef  TYPE_10__ SERVER ;
typedef  TYPE_11__ LISTENER ;
typedef  TYPE_12__ LIST ;
typedef  TYPE_13__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  Add (TYPE_12__*,TYPE_11__*) ; 
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CheckDeadLock (int /*<<< orphan*/ *,scalar_t__,char*) ; 
 TYPE_11__* LIST_DATA (TYPE_12__*,scalar_t__) ; 
 scalar_t__ LIST_NUM (TYPE_12__*) ; 
 int /*<<< orphan*/  LockList (TYPE_12__*) ; 
 TYPE_12__* NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (TYPE_12__*) ; 
 int /*<<< orphan*/  ReleaseListener (TYPE_11__*) ; 
 int /*<<< orphan*/  UnlockList (TYPE_12__*) ; 

void SiCheckDeadLockMain(SERVER *s, UINT timeout)
{
	CEDAR *cedar;
	// Validate arguments
	if (s == NULL)
	{
		return;
	}

	//Debug("SiCheckDeadLockMain Start.\n");


	cedar = s->Cedar;

	if (s->ServerListenerList != NULL)
	{
		CheckDeadLock(s->ServerListenerList->lock, timeout, "s->ServerListenerList->lock");
	}

	CheckDeadLock(s->lock, timeout, "s->lock");

	if (s->FarmMemberList != NULL)
	{
		CheckDeadLock(s->FarmMemberList->lock, timeout, "s->FarmMemberList->lock");
	}

	if (s->HubCreateHistoryList != NULL)
	{
		CheckDeadLock(s->HubCreateHistoryList->lock, timeout, "s->HubCreateHistoryList->lock");
	}

	CheckDeadLock(s->CapsCacheLock, timeout, "s->CapsCacheLock");

	CheckDeadLock(s->TasksFromFarmControllerLock, timeout, "s->TasksFromFarmControllerLock");

	if (cedar != NULL)
	{
		if (cedar->HubList != NULL)
		{
			CheckDeadLock(cedar->HubList->lock, timeout, "cedar->HubList->lock");
		}

		if (cedar->ListenerList != NULL)
		{
			UINT i;
			LIST *o = NewListFast(NULL);

			CheckDeadLock(cedar->ListenerList->lock, timeout, "cedar->ListenerList->lock");

			LockList(cedar->ListenerList);
			{
				for (i = 0;i < LIST_NUM(cedar->ListenerList);i++)
				{
					LISTENER *r = LIST_DATA(cedar->ListenerList, i);

					AddRef(r->ref);

					Add(o, r);
				}
			}
			UnlockList(cedar->ListenerList);

			for (i = 0;i < LIST_NUM(o);i++)
			{
				LISTENER *r = LIST_DATA(o, i);


				ReleaseListener(r);
			}

			ReleaseList(o);
		}

		if (cedar->ConnectionList != NULL)
		{
			CheckDeadLock(cedar->ConnectionList->lock, timeout, "cedar->ConnectionList->lock");
		}

		if (cedar->CaList != NULL)
		{
			CheckDeadLock(cedar->CaList->lock, timeout, "cedar->CaList->lock");
		}

		if (cedar->TrafficLock != NULL)
		{
			CheckDeadLock(cedar->TrafficLock, timeout, "cedar->TrafficLock");
		}

		if (cedar->TrafficDiffList != NULL)
		{
			CheckDeadLock(cedar->TrafficDiffList->lock, timeout, "cedar->TrafficDiffList->lock");
		}

		if (cedar->LocalBridgeList != NULL)
		{
			CheckDeadLock(cedar->LocalBridgeList->lock, timeout, "cedar->LocalBridgeList->lock");
		}

		if (cedar->L3SwList != NULL)
		{
			CheckDeadLock(cedar->L3SwList->lock, timeout, "cedar->L3SwList->lock");
		}
	}

	//Debug("SiCheckDeadLockMain Finish.\n");
}