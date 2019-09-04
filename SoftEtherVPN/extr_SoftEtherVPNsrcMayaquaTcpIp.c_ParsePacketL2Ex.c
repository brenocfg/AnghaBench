#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int USHORT ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_12__ {scalar_t__ Dsap; scalar_t__ Ssap; } ;
struct TYPE_11__ {int* DestAddress; int* SrcAddress; int /*<<< orphan*/  Protocol; } ;
struct TYPE_10__ {int BroadcastPacket; int InvalidSourcePacket; int VlanTypeID; TYPE_2__* MacHeader; } ;
typedef  TYPE_1__ PKT ;
typedef  TYPE_2__ MAC_HEADER ;
typedef  TYPE_3__ LLC_HEADER ;

/* Variables and functions */
 int Endian16 (int /*<<< orphan*/ ) ; 
 scalar_t__ LLC_DSAP_BPDU ; 
 scalar_t__ LLC_SSAP_BPDU ; 
#define  MAC_PROTO_ARPV4 130 
#define  MAC_PROTO_IPV4 129 
#define  MAC_PROTO_IPV6 128 
 int ParsePacketARPv4 (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int ParsePacketBPDU (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int ParsePacketIPv4 (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int ParsePacketIPv6 (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int ParsePacketTAGVLAN (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ memcmp (int*,int*,int) ; 

bool ParsePacketL2Ex(PKT *p, UCHAR *buf, UINT size, bool no_l3)
{
	UINT i;
	bool b1, b2;
	USHORT type_id_16;
	// Validate arguments
	if (p == NULL || buf == NULL)
	{
		return false;
	}

	// Check the size
	if (size < sizeof(MAC_HEADER))
	{
		return false;
	}

	// MAC header
	p->MacHeader = (MAC_HEADER *)buf;

	buf += sizeof(MAC_HEADER);
	size -= sizeof(MAC_HEADER);

	// Analysis of the MAC header
	p->BroadcastPacket = true;
	b1 = true;
	b2 = true;
	for (i = 0;i < 6;i++)
	{
		if (p->MacHeader->DestAddress[i] != 0xff)
		{
			p->BroadcastPacket = false;
		}
		if (p->MacHeader->SrcAddress[i] != 0xff)
		{
			b1 = false;
		}
		if (p->MacHeader->SrcAddress[i] != 0x00)
		{
			b2 = false;
		}
	}
	if (b1 || b2 || (memcmp(p->MacHeader->SrcAddress, p->MacHeader->DestAddress, 6) == 0))
	{
		p->InvalidSourcePacket = true;
	}
	else
	{
		p->InvalidSourcePacket = false;
	}

	if (p->MacHeader->DestAddress[0] & 0x01)
	{
		p->BroadcastPacket = true;
	}

	// Parse L3 packet
	type_id_16 = Endian16(p->MacHeader->Protocol);

	if (type_id_16 > 1500)
	{
		// Ordinary Ethernet frame
		switch (type_id_16)
		{
		case MAC_PROTO_ARPV4:	// ARPv4
			if (no_l3)
			{
				return true;
			}

			return ParsePacketARPv4(p, buf, size);

		case MAC_PROTO_IPV4:	// IPv4
			if (no_l3)
			{
				return true;
			}

			return ParsePacketIPv4(p, buf, size);

		case MAC_PROTO_IPV6:	// IPv6
			if (no_l3)
			{
				return true;
			}

			return ParsePacketIPv6(p, buf, size);

		default:				// Unknown
			if (type_id_16 == p->VlanTypeID)
			{
				// VLAN
				return ParsePacketTAGVLAN(p, buf, size);
			}
			else
			{
				return true;
			}
		}
	}
	else
	{
		// Old IEEE 802.3 frame (payload length of the packet is written in the header)
		// (It has been used in the BPDU, etc.) 
		UINT length = (UINT)type_id_16;
		LLC_HEADER *llc;

		// Check whether the length is remaining
		if (size < length || size < sizeof(LLC_HEADER))
		{
			return true;
		}

		// Read an LLC header
		llc = (LLC_HEADER *)buf;
		buf += sizeof(LLC_HEADER);
		size -= sizeof(LLC_HEADER);

		// Determine the protocol by the value of DSAP and SSAP
		if (llc->Dsap == LLC_DSAP_BPDU && llc->Ssap == LLC_SSAP_BPDU)
		{
			// This is a BPDU (Spanning Tree)
			return ParsePacketBPDU(p, buf, size);
		}
		else
		{
			// Unknown protocol
			return true;
		}
	}
}