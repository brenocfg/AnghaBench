#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UDPPACKET ;
struct TYPE_4__ {int Halt; int /*<<< orphan*/  Interrupts; int /*<<< orphan*/  SendPacketList; int /*<<< orphan*/  PortList; int /*<<< orphan*/  Event; int /*<<< orphan*/  Thread; } ;
typedef  TYPE_1__ UDPLISTENER ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeInterruptManager (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeUdpPacket (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseIntList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSockEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetSockEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void FreeUdpListener(UDPLISTENER *u)
{
	UINT i;
	// Validate arguments
	if (u == NULL)
	{
		return;
	}

	u->Halt = true;
	SetSockEvent(u->Event);

	WaitThread(u->Thread, INFINITE);
	ReleaseThread(u->Thread);
	ReleaseSockEvent(u->Event);

	ReleaseIntList(u->PortList);

	for (i = 0;i < LIST_NUM(u->SendPacketList);i++)
	{
		UDPPACKET *p = LIST_DATA(u->SendPacketList, i);

		FreeUdpPacket(p);
	}

	ReleaseList(u->SendPacketList);

	FreeInterruptManager(u->Interrupts);

	Free(u);
}