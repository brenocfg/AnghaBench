#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int SendStateChanged; int /*<<< orphan*/  Lock; TYPE_1__* HaltTube; int /*<<< orphan*/  RecvQueue; } ;
struct TYPE_9__ {int /*<<< orphan*/  Ref; } ;
typedef  TYPE_1__ TUBE ;
typedef  int /*<<< orphan*/  PKT ;
typedef  TYPE_2__ NATIVE_NAT ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreePacketWithData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetNext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NnDeleteOldSessions (TYPE_2__*) ; 
 int /*<<< orphan*/  NnLayer2 (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NnPollingIpCombine (TYPE_2__*) ; 
 int /*<<< orphan*/  ReleaseTube (TYPE_1__*) ; 
 int /*<<< orphan*/  TubeFlushEx (TYPE_1__*,int) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockQueue (int /*<<< orphan*/ ) ; 

void NnPoll(NATIVE_NAT *t)
{
	// Validate arguments
	if (t == NULL)
	{
		return;
	}

	LockQueue(t->RecvQueue);
	{
		while (true)
		{
			PKT *pkt = GetNext(t->RecvQueue);

			if (pkt == NULL)
			{
				break;
			}

			NnLayer2(t, pkt);

			FreePacketWithData(pkt);
		}
	}
	UnlockQueue(t->RecvQueue);

	if (t->SendStateChanged)
	{
		TUBE *halt_tube = NULL;

		Lock(t->Lock);
		{
			if (t->HaltTube != NULL)
			{
				halt_tube = t->HaltTube;

				AddRef(halt_tube->Ref);
			}
		}
		Unlock(t->Lock);

		if (halt_tube != NULL)
		{
			TubeFlushEx(halt_tube, true);

			t->SendStateChanged = false;

			ReleaseTube(halt_tube);
		}
	}

	NnPollingIpCombine(t);

	NnDeleteOldSessions(t);
}