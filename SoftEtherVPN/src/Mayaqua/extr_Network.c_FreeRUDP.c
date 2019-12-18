#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UDPPACKET ;
struct TYPE_5__ {int Halt; int NoNatTRegister; size_t RandPortId; int /*<<< orphan*/  Lock; int /*<<< orphan*/ * TargetConnectedSock; int /*<<< orphan*/  NewSockConnectEvent; int /*<<< orphan*/  TargetConnectedEvent; int /*<<< orphan*/  HaltEvent; int /*<<< orphan*/  SockEvent; int /*<<< orphan*/ * UdpSock; int /*<<< orphan*/  Interrupt; int /*<<< orphan*/  SendPacketList; int /*<<< orphan*/  NewSockQueue; int /*<<< orphan*/  NatT_SourceIpList; int /*<<< orphan*/  SessionList; int /*<<< orphan*/ * Thread; int /*<<< orphan*/ * IpQueryThread; scalar_t__ ServerMode; } ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  TYPE_1__ RUDP_STACK ;
typedef  TYPE_1__ RUDP_SOURCE_IP ;
typedef  int /*<<< orphan*/  RUDP_SESSION ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeInterruptManager (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeUdpPacket (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetNext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INFINITE ; 
 void* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RUDPFreeSession (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseSockEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetSockEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__* rand_port_numbers ; 

void FreeRUDP(RUDP_STACK *r)
{
	UINT i;
	// Validate arguments
	if (r == NULL)
	{
		return;
	}

	r->Halt = true;
	Set(r->HaltEvent);
	SetSockEvent(r->SockEvent);

	if (r->ServerMode && r->NoNatTRegister == false)
	{
		if (r->IpQueryThread != NULL)
		{
			WaitThread(r->IpQueryThread, INFINITE);
			ReleaseThread(r->IpQueryThread);
		}
	}

	WaitThread(r->Thread, INFINITE);
	ReleaseThread(r->Thread);

	for (i = 0;i < LIST_NUM(r->SessionList);i++)
	{
		RUDP_SESSION *se = LIST_DATA(r->SessionList, i);

		RUDPFreeSession(se);
	}

	ReleaseList(r->SessionList);

	for (i = 0;i < LIST_NUM(r->SendPacketList);i++)
	{
		UDPPACKET *p = LIST_DATA(r->SendPacketList, i);

		FreeUdpPacket(p);
	}

	while (true)
	{
		SOCK *s = GetNext(r->NewSockQueue);
		if (s == NULL)
		{
			break;
		}

		Disconnect(s);
		ReleaseSock(s);
	}

	for (i = 0;i < LIST_NUM(r->NatT_SourceIpList);i++)
	{
		RUDP_SOURCE_IP *sip = (RUDP_SOURCE_IP *)LIST_DATA(r->NatT_SourceIpList, i);

		Free(sip);
	}

	ReleaseList(r->NatT_SourceIpList);

	ReleaseQueue(r->NewSockQueue);

	ReleaseList(r->SendPacketList);

	FreeInterruptManager(r->Interrupt);

	Disconnect(r->UdpSock);
	ReleaseSock(r->UdpSock);
	ReleaseSockEvent(r->SockEvent);
	ReleaseEvent(r->HaltEvent);
	ReleaseEvent(r->TargetConnectedEvent);

	ReleaseEvent(r->NewSockConnectEvent);

	Disconnect(r->TargetConnectedSock);
	ReleaseSock(r->TargetConnectedSock);

	DeleteLock(r->Lock);

	if (r->RandPortId != 0)
	{
		rand_port_numbers[r->RandPortId] = 0;
	}

	Free(r);
}