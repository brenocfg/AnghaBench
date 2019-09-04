#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USHORT ;
typedef  int UINT ;
struct TYPE_3__ {int /*<<< orphan*/  SrcPort; int /*<<< orphan*/  DstPort; } ;
typedef  TYPE_1__ UDP_HEADER ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_4__ {scalar_t__ Protocol; } ;
typedef  TYPE_2__ IPV4_HEADER ;

/* Variables and functions */
 scalar_t__ Cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Debug (char*) ; 
 int Endian16 (int /*<<< orphan*/ ) ; 
 int GetIpHeaderSize (int /*<<< orphan*/ *,int) ; 
 scalar_t__ IP_PROTO_UDP ; 
 scalar_t__ IsZero (int /*<<< orphan*/ *,int) ; 
 scalar_t__ MAC_PROTO_IPV4 ; 
 scalar_t__ READ_USHORT (int /*<<< orphan*/ *) ; 

bool IsDhcpPacketForSpecificMac(UCHAR *data, UINT size, UCHAR *mac_address)
{
	USHORT *us;
	IPV4_HEADER *ip;
	UDP_HEADER *udp;
	UINT ip_header_size;
	bool is_send = false, is_recv = false;
	// Validate arguments
	if (data == NULL || mac_address == NULL || IsZero(mac_address, 6))
	{
		return false;
	}

	// Whether the src or the dest matches
	if (size < 14)
	{
		return false;
	}

	// Destination MAC address
	if (Cmp(data, mac_address, 6) == 0)
	{
		is_recv = true;
	}
	size -= 6;
	data += 6;

	// Source MAC address
	if (Cmp(data, mac_address, 6) == 0)
	{
		is_send = true;
	}
	size -= 6;
	data += 6;

	if (is_send == false && is_recv == false)
	{
		return false;
	}
	if (is_send && is_recv)
	{
		return false;
	}

	// TPID
	us = (USHORT *)data;
	size -= 2;
	data += 2;

	if (READ_USHORT(us) != MAC_PROTO_IPV4)
	{
		// Other than IPv4
		return false;
	}

	// IP header
	ip_header_size = GetIpHeaderSize(data, size);
	if (ip_header_size == 0)
	{
		// IPv4 header analysis failure
		return false;
	}

	ip = (IPV4_HEADER *)data;
	data += ip_header_size;
	size -= ip_header_size;

	if (ip->Protocol != IP_PROTO_UDP)
	{
		// Not an UDP packet
		return false;
	}

	// UDP header
	if (size < sizeof(UDP_HEADER))
	{
		return false;
	}
	udp = (UDP_HEADER *)data;
	data += sizeof(UDP_HEADER);
	size -= sizeof(UDP_HEADER);

	if (is_send)
	{
		// Detect whether it's a DHCP Request packet
		if (Endian16(udp->DstPort) == 67)
		{
			Debug("IsDhcpPacketForSpecificMac: DHCP Request Packet is Detected.\n");
			return true;
		}
	}
	else if (is_recv)
	{
		// Detect whether it's a DHCP Response packet
		if (Endian16(udp->SrcPort) == 67)
		{
			Debug("IsDhcpPacketForSpecificMac: DHCP Response Packet is Detected.\n");
			return true;
		}
	}

	return false;
}