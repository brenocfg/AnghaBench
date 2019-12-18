#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_6__ {scalar_t__ Type; } ;
typedef  TYPE_1__ UDPPACKET ;
struct TYPE_7__ {int /*<<< orphan*/  SendPacketList; } ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_2__ IKE_SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* NewUdpPacket (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,scalar_t__,void*,scalar_t__) ; 

void IkeSendUdpPacket(IKE_SERVER *ike, UINT type, IP *server_ip, UINT server_port, IP *client_ip, UINT client_port, void *data, UINT size)
{
	UDPPACKET *p;
	// Validate arguments
	if (ike == NULL || server_ip == NULL || client_ip == NULL || server_port == 0 || client_port == 0 || data == NULL || size == 0)
	{
		return;
	}

	p = NewUdpPacket(server_ip, server_port, client_ip, client_port, data, size);

	p->Type = type;

	Add(ike->SendPacketList, p);
}