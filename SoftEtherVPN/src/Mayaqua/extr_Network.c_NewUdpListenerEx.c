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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UDPLISTENER_RECV_PROC ;
struct TYPE_5__ {int /*<<< orphan*/  Thread; int /*<<< orphan*/  Interrupts; void* SendPacketList; int /*<<< orphan*/ * RecvProc; int /*<<< orphan*/  ListenIP; int /*<<< orphan*/  Event; void* PortList; int /*<<< orphan*/  PacketType; void* Param; } ;
typedef  TYPE_1__ UDPLISTENER ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  NewInterruptManager () ; 
 void* NewList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NewSockEvent () ; 
 int /*<<< orphan*/  NewThread (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  UdpListenerThread ; 
 TYPE_1__* ZeroMalloc (int) ; 

UDPLISTENER *NewUdpListenerEx(UDPLISTENER_RECV_PROC *recv_proc, void *param, IP *listen_ip, UINT packet_type)
{
	UDPLISTENER *u;
	// Validate arguments
	if (recv_proc == NULL)
	{
		return NULL;
	}
	
	u = ZeroMalloc(sizeof(UDPLISTENER));

	u->Param = param;
	u->PacketType = packet_type;

	u->PortList = NewList(NULL);
	u->Event = NewSockEvent();

	if (listen_ip)
	{
		Copy(&u->ListenIP, listen_ip, sizeof(IP));
	}

	u->RecvProc = recv_proc;
	u->SendPacketList = NewList(NULL);

	u->Interrupts = NewInterruptManager();

	u->Thread = NewThread(UdpListenerThread, u);

	return u;
}