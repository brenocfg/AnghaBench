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
typedef  int /*<<< orphan*/  VH ;
struct TYPE_9__ {int HardwareSize; int ProtocolSize; int /*<<< orphan*/  Operation; int /*<<< orphan*/  SrcAddress; int /*<<< orphan*/  ProtocolType; int /*<<< orphan*/  HardwareType; } ;
struct TYPE_7__ {TYPE_3__* ARPv4Header; } ;
struct TYPE_8__ {int /*<<< orphan*/  MacAddressSrc; TYPE_1__ L3; } ;
typedef  TYPE_2__ PKT ;
typedef  TYPE_3__ ARPV4_HEADER ;

/* Variables and functions */
 int ARP_HARDWARE_TYPE_ETHERNET ; 
#define  ARP_OPERATION_REQUEST 129 
#define  ARP_OPERATION_RESPONSE 128 
 scalar_t__ Cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int Endian16 (int /*<<< orphan*/ ) ; 
 int MAC_PROTO_IPV4 ; 
 int /*<<< orphan*/  VirtualArpResponseReceived (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  VirtualArpResponseRequest (int /*<<< orphan*/ *,TYPE_2__*) ; 

void VirtualArpReceived(VH *v, PKT *packet)
{
	ARPV4_HEADER *arp;
	// Validate arguments
	if (v == NULL || packet == NULL)
	{
		return;
	}

	arp = packet->L3.ARPv4Header;

	if (Endian16(arp->HardwareType) != ARP_HARDWARE_TYPE_ETHERNET)
	{
		// Ignore if hardware type is other than Ethernet
		return;
	}
	if (Endian16(arp->ProtocolType) != MAC_PROTO_IPV4)
	{
		// Ignore if the protocol type is a non-IPv4
		return;
	}
	if (arp->HardwareSize != 6 || arp->ProtocolSize != 4)
	{
		// Ignore because the size of protocol address or hardware address is invalid
		return;
	}
	// Check the source MAC address
	if (Cmp(arp->SrcAddress, packet->MacAddressSrc, 6) != 0)
	{
		// MAC address in the MAC header and the MAC address of the ARP packet are different
		return;
	}

	switch (Endian16(arp->Operation))
	{
	case ARP_OPERATION_REQUEST:		// ARP request
		VirtualArpResponseRequest(v, packet);
		break;

	case ARP_OPERATION_RESPONSE:	// ARP response
		VirtualArpResponseReceived(v, packet);
		break;
	}
}