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
struct TYPE_4__ {int /*<<< orphan*/  FlushList; int /*<<< orphan*/  Cedar; int /*<<< orphan*/  HaltCompletedEvent; int /*<<< orphan*/  SockEvent; int /*<<< orphan*/  TunnelList; int /*<<< orphan*/  SendPacketList; int /*<<< orphan*/  ThreadList; } ;
typedef  int /*<<< orphan*/  L2TP_TUNNEL ;
typedef  TYPE_1__ L2TP_SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeL2TPTunnel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeThreadList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeTubeFlushList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeUdpPacket (int /*<<< orphan*/ *) ; 
 void* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseCedar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSockEvent (int /*<<< orphan*/ ) ; 

void FreeL2TPServer(L2TP_SERVER *l2tp)
{
	UINT i;
	// Validate arguments
	if (l2tp == NULL)
	{
		return;
	}

	FreeThreadList(l2tp->ThreadList);

	for (i = 0;i < LIST_NUM(l2tp->SendPacketList);i++)
	{
		UDPPACKET *p = LIST_DATA(l2tp->SendPacketList, i);

		FreeUdpPacket(p);
	}

	ReleaseList(l2tp->SendPacketList);

	for (i = 0;i < LIST_NUM(l2tp->TunnelList);i++)
	{
		L2TP_TUNNEL *t = LIST_DATA(l2tp->TunnelList, i);

		FreeL2TPTunnel(t);
	}

	ReleaseList(l2tp->TunnelList);

	ReleaseSockEvent(l2tp->SockEvent);

	ReleaseEvent(l2tp->HaltCompletedEvent);

	ReleaseCedar(l2tp->Cedar);

	FreeTubeFlushList(l2tp->FlushList);

	Free(l2tp);
}