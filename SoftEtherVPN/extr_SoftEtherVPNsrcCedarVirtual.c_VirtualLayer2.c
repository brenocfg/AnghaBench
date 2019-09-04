#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  MacAddress; scalar_t__ UseDhcp; } ;
typedef  TYPE_1__ VH ;
struct TYPE_14__ {int TypeL3; scalar_t__ TypeL4; scalar_t__ TypeL7; int /*<<< orphan*/  MacAddressDest; scalar_t__ BroadcastPacket; } ;
typedef  TYPE_2__ PKT ;

/* Variables and functions */
 scalar_t__ Cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
#define  L3_ARPV4 129 
#define  L3_IPV4 128 
 scalar_t__ L4_UDP ; 
 scalar_t__ L7_DHCPV4 ; 
 int /*<<< orphan*/  VirtualArpReceived (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  VirtualDhcpServer (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  VirtualIpReceived (TYPE_1__*,TYPE_2__*) ; 
 int VirtualLayer2Filter (TYPE_1__*,TYPE_2__*) ; 

void VirtualLayer2(VH *v, PKT *packet)
{
	bool ok;
	// Validate arguments
	if (packet == NULL || v == NULL)
	{
		return;
	}

	// Packet filter
	if (VirtualLayer2Filter(v, packet) == false)
	{
		// Packet was ignored
		return;
	}

	ok = false;
	if (packet->TypeL3 == L3_IPV4 && packet->TypeL4 == L4_UDP && packet->TypeL7 == L7_DHCPV4)
	{
		if (v->UseDhcp)
		{
			// A special treatment on the DHCP packet
			if (packet->BroadcastPacket || Cmp(packet->MacAddressDest, v->MacAddress, 6) == 0)
			{
				// Virtual DHCP server processing
				VirtualDhcpServer(v, packet);
				ok = true;
			}
		}
	}

	if (ok == false)
	{
		// The process for each supported protocol
		switch (packet->TypeL3)
		{
		case L3_ARPV4:	// ARPv4
			VirtualArpReceived(v, packet);
			break;

		case L3_IPV4:	// IPv4
			VirtualIpReceived(v, packet);
			break;
		}
	}
}