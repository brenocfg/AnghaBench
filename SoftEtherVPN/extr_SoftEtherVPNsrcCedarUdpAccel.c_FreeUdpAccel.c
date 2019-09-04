#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int NatT_Halt; TYPE_2__* Cedar; int /*<<< orphan*/  NatT_Lock; int /*<<< orphan*/  NatT_HaltEvent; int /*<<< orphan*/ * NatT_GetIpThread; int /*<<< orphan*/  MyPort; scalar_t__ IsInCedarPortList; int /*<<< orphan*/  UdpSock; int /*<<< orphan*/  RecvBlockQueue; } ;
typedef  TYPE_1__ UDP_ACCEL ;
struct TYPE_6__ {int /*<<< orphan*/  UdpPortList; } ;
typedef  int /*<<< orphan*/  BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  DelInt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeBlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetNext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseCedar (TYPE_2__*) ; 
 int /*<<< orphan*/  ReleaseEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void FreeUdpAccel(UDP_ACCEL *a)
{
	// Validate arguments
	if (a == NULL)
	{
		return;
	}

	while (true)
	{
		BLOCK *b = GetNext(a->RecvBlockQueue);

		if (b == NULL)
		{
			break;
		}

		FreeBlock(b);
	}

	ReleaseQueue(a->RecvBlockQueue);

	ReleaseSock(a->UdpSock);

	if (a->IsInCedarPortList)
	{
		LockList(a->Cedar->UdpPortList);
		{
			DelInt(a->Cedar->UdpPortList, a->MyPort);
		}
		UnlockList(a->Cedar->UdpPortList);
	}

	// Release of NAT-T related
	a->NatT_Halt = true;
	Set(a->NatT_HaltEvent);

	if (a->NatT_GetIpThread != NULL)
	{
		WaitThread(a->NatT_GetIpThread, INFINITE);
		ReleaseThread(a->NatT_GetIpThread);
	}

	ReleaseEvent(a->NatT_HaltEvent);
	DeleteLock(a->NatT_Lock);

	ReleaseCedar(a->Cedar);

	Free(a);
}