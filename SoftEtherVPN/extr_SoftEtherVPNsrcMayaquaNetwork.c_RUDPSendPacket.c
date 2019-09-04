#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_8__ {scalar_t__ Type; } ;
typedef  TYPE_2__ UDPPACKET ;
struct TYPE_9__ {scalar_t__ Protocol; int /*<<< orphan*/  SendPacketList; TYPE_1__* UdpSock; } ;
struct TYPE_7__ {int /*<<< orphan*/  LocalPort; int /*<<< orphan*/  LocalIP; } ;
typedef  TYPE_3__ RUDP_STACK ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  Clone (void*,scalar_t__) ; 
 TYPE_2__* NewUdpPacket (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ RUDP_PROTOCOL_DNS ; 
 scalar_t__ RUDP_PROTOCOL_ICMP ; 

void RUDPSendPacket(RUDP_STACK *r, IP *dest_ip, UINT dest_port, void *data, UINT size, UINT icmp_type)
{
	UDPPACKET *p;
	// Validate arguments
	if (r == NULL || dest_ip == NULL || dest_port == 0 || data == NULL || size == 0)
	{
		return;
	}

	p = NewUdpPacket(&r->UdpSock->LocalIP, r->UdpSock->LocalPort,
		dest_ip, dest_port,
		Clone(data, size), size);

	if (r->Protocol == RUDP_PROTOCOL_ICMP || r->Protocol == RUDP_PROTOCOL_DNS)
	{
		// ICMP Type / DNS Tran ID
		p->Type = icmp_type;
	}

	Add(r->SendPacketList, p);
}