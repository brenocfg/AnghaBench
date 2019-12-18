#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  void* UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_15__ {scalar_t__ Type; scalar_t__ SrcPort; int Size; void* Data; } ;
typedef  TYPE_1__ UDPPACKET ;
struct TYPE_16__ {int HostIPAddressListChanged; int /*<<< orphan*/  Event; int /*<<< orphan*/ * Interrupts; scalar_t__ Param; } ;
typedef  TYPE_2__ UDPLISTENER ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_19__ {int /*<<< orphan*/ * SendPacketList; void* Now; int /*<<< orphan*/ * SockEvent; int /*<<< orphan*/ * Interrupts; } ;
struct TYPE_18__ {int HostIPAddressListChanged; TYPE_5__* Ike; TYPE_3__* L2TP; int /*<<< orphan*/  OsServiceCheckThreadEvent; } ;
struct TYPE_17__ {int /*<<< orphan*/ * SendPacketList; void* Now; int /*<<< orphan*/ * SockEvent; int /*<<< orphan*/ * Interrupts; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_3__ L2TP_SERVER ;
typedef  TYPE_4__ IPSEC_SERVER ;
typedef  TYPE_5__ IKE_SERVER ;

/* Variables and functions */
 void* AddHead (void*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  DeleteAll (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (void*) ; 
 scalar_t__ IKE_UDP_TYPE_ESP ; 
 scalar_t__ IKE_UDP_TYPE_ISAKMP ; 
 scalar_t__ IPSEC_PORT_IPSEC_ESP_UDP ; 
 scalar_t__ IPSEC_PORT_IPSEC_ISAKMP ; 
 int /*<<< orphan*/  IPsecProcPacket (TYPE_4__*,TYPE_1__*) ; 
 int /*<<< orphan*/  L2TPProcessInterrupts (TYPE_3__*) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ProcessIKEInterrupts (TYPE_5__*) ; 
 int /*<<< orphan*/  Set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetIKEServerSockEvent (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetL2TPServerSockEvent (TYPE_3__*,int /*<<< orphan*/ ) ; 
 void* Tick64 () ; 
 int /*<<< orphan*/  UdpListenerSendPackets (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int ipsec_disable ; 

void IPsecServerUdpPacketRecvProc(UDPLISTENER *u, LIST *packet_list)
{
	UINT i;
	IPSEC_SERVER *s;
	L2TP_SERVER *l2tp;
	IKE_SERVER *ike;
	UINT64 now;
	static UCHAR zero8[8] = {0, 0, 0, 0, 0, 0, 0, 0, };
	// Validate arguments
	if (u == NULL || packet_list == NULL)
	{
		return;
	}
	s = (IPSEC_SERVER *)u->Param;
	if (s == NULL)
	{
		return;
	}

	if (u->HostIPAddressListChanged)
	{
		u->HostIPAddressListChanged = false;

		s->HostIPAddressListChanged = true;

		Set(s->OsServiceCheckThreadEvent);
	}

	now = Tick64();

	// Adjustment about L2TP server timing
	l2tp = s->L2TP;

	if (l2tp->Interrupts == NULL)
	{
		l2tp->Interrupts = u->Interrupts;
	}

	if (l2tp->SockEvent == NULL)
	{
		SetL2TPServerSockEvent(l2tp, u->Event);
	}

	l2tp->Now = now;

	// Adjustment about IKE server timing
	ike = s->Ike;

	if (ike->Interrupts == NULL)
	{
		ike->Interrupts = u->Interrupts;
	}

	if (ike->SockEvent == NULL)
	{
		SetIKEServerSockEvent(ike, u->Event);
	}

	ike->Now = now;

	if (ipsec_disable == false)
	{
		{
			// Process the received packet
			for (i = 0;i < LIST_NUM(packet_list);i++)
			{
				UDPPACKET *p = LIST_DATA(packet_list, i);

				IPsecProcPacket(s, p);
			}
		}
	}

	// Interrupt processing of L2TP server
	L2TPProcessInterrupts(l2tp);

	// L2TP packet transmission processing
	UdpListenerSendPackets(u, l2tp->SendPacketList);
	DeleteAll(l2tp->SendPacketList);

	// Interrupt processing of IKE server
	ProcessIKEInterrupts(ike);

	// UDP encapsulation process of IKE server packet scheduled for transmission
	for (i = 0;i < LIST_NUM(ike->SendPacketList);i++)
	{
		UDPPACKET *p = LIST_DATA(ike->SendPacketList, i);

		if (p->Type == IKE_UDP_TYPE_ISAKMP && p->SrcPort == IPSEC_PORT_IPSEC_ESP_UDP)
		{
			// Add the Non-ESP Marker
			void *old_data = p->Data;

			p->Data = AddHead(p->Data, p->Size, zero8, 4);
			p->Size += 4;

			Free(old_data);
		}
		else if (p->Type == IKE_UDP_TYPE_ESP && p->SrcPort == IPSEC_PORT_IPSEC_ISAKMP)
		{
			// Add the Non-IKE Marker
			void *old_data = p->Data;

			p->Data = AddHead(p->Data, p->Size, zero8, 8);
			p->Size += 8;

			Free(old_data);
		}
	}

	// IKE server packet transmission processing
	UdpListenerSendPackets(u, ike->SendPacketList);
	DeleteAll(ike->SendPacketList);
}