#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_15__ {int /*<<< orphan*/  AllList; } ;
struct TYPE_14__ {int Halt; TYPE_7__* NatTableForRecv; TYPE_7__* NatTableForSend; int /*<<< orphan*/  Cancel; int /*<<< orphan*/  SendQueue; int /*<<< orphan*/  RecvQueue; TYPE_1__* HaltTube3; TYPE_1__* HaltTube2; int /*<<< orphan*/  HaltEvent; int /*<<< orphan*/  CancelLock; int /*<<< orphan*/  Lock; int /*<<< orphan*/  Thread; TYPE_1__* HaltTube; } ;
struct TYPE_13__ {int /*<<< orphan*/  Ref; } ;
typedef  TYPE_1__ TUBE ;
typedef  TYPE_2__ NATIVE_NAT_ENTRY ;
typedef  TYPE_2__ NATIVE_NAT ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_2__*) ; 
 int /*<<< orphan*/  INFINITE ; 
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NnClearQueue (TYPE_2__*) ; 
 int /*<<< orphan*/  NnFreeIpCombineList (TYPE_2__*) ; 
 int /*<<< orphan*/  ReleaseCancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseHashList (TYPE_7__*) ; 
 int /*<<< orphan*/  ReleaseQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseTube (TYPE_1__*) ; 
 int /*<<< orphan*/  Set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SleepThread (int) ; 
 int /*<<< orphan*/  TubeDisconnect (TYPE_1__*) ; 
 int /*<<< orphan*/  TubeFlushEx (TYPE_1__*,int) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void FreeNativeNat(NATIVE_NAT *t)
{
	TUBE *tube;
	UINT i;
	// Validate arguments
	if (t == NULL)
	{
		return;
	}

	t->Halt = true;

	Lock(t->Lock);
	{
		tube = t->HaltTube;

		if (tube != NULL)
		{
			AddRef(tube->Ref);
		}
	}
	Unlock(t->Lock);

	if (tube != NULL)
	{
		TubeFlushEx(tube, true);

		SleepThread(100);

		TubeDisconnect(tube);

		ReleaseTube(tube);
	}

	TubeDisconnect(t->HaltTube2);
	TubeDisconnect(t->HaltTube3);

	Set(t->HaltEvent);

	WaitThread(t->Thread, INFINITE);

	ReleaseThread(t->Thread);

	DeleteLock(t->Lock);

	DeleteLock(t->CancelLock);

	ReleaseEvent(t->HaltEvent);

	ReleaseTube(t->HaltTube2);
	ReleaseTube(t->HaltTube3);

	NnClearQueue(t);

	ReleaseQueue(t->RecvQueue);
	ReleaseQueue(t->SendQueue);

	ReleaseCancel(t->Cancel);

	// Release the NAT table
	for (i = 0;i < LIST_NUM(t->NatTableForSend->AllList);i++)
	{
		NATIVE_NAT_ENTRY *e = LIST_DATA(t->NatTableForSend->AllList, i);

		Free(e);
	}

	ReleaseHashList(t->NatTableForSend);
	ReleaseHashList(t->NatTableForRecv);

	NnFreeIpCombineList(t);

	Free(t);
}