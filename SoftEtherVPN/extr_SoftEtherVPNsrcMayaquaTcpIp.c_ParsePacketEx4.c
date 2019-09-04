#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int USHORT ;
typedef  scalar_t__ UINT ;
typedef  int UCHAR ;
struct TYPE_24__ {int /*<<< orphan*/  OpCode; } ;
struct TYPE_21__ {TYPE_5__* TCPHeader; } ;
struct TYPE_20__ {TYPE_2__* BpduHeader; } ;
struct TYPE_23__ {int* PacketData; scalar_t__ TypeL3; scalar_t__ TypeL4; int PayloadSize; scalar_t__ TypeL7; int /*<<< orphan*/  DhcpOpCode; int /*<<< orphan*/  HttpLog; TYPE_4__ L4; TYPE_3__ L3; int /*<<< orphan*/  MacAddressSrc; TYPE_1__* MacHeader; int /*<<< orphan*/  MacAddressDest; scalar_t__ PacketSize; scalar_t__ VlanTypeID; } ;
struct TYPE_22__ {int DstPort; int Flag; } ;
struct TYPE_19__ {int /*<<< orphan*/  BridgeMacAddress; } ;
struct TYPE_18__ {int /*<<< orphan*/  DestAddress; int /*<<< orphan*/  SrcAddress; } ;
typedef  TYPE_5__ TCP_HEADER ;
typedef  TYPE_6__ PKT ;
typedef  TYPE_7__ DHCPV4_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  CorrectChecksum (TYPE_6__*) ; 
 int Endian16 (int) ; 
 int /*<<< orphan*/  FreeDHCPv4Data (TYPE_7__*) ; 
 int /*<<< orphan*/  FreePacket (TYPE_6__*) ; 
 scalar_t__ L3_BPDU ; 
 scalar_t__ L3_IPV4 ; 
 scalar_t__ L3_IPV6 ; 
 scalar_t__ L4_TCP ; 
 scalar_t__ L4_UDP ; 
 scalar_t__ L7_DHCPV4 ; 
 scalar_t__ MAC_PROTO_TAGVLAN ; 
 TYPE_7__* ParseDHCPv4Data (TYPE_6__*) ; 
 int /*<<< orphan*/  ParseHttpAccessLog (TYPE_6__*) ; 
 int /*<<< orphan*/  ParseHttpsAccessLog (TYPE_6__*) ; 
 int ParsePacketL2Ex (TYPE_6__*,int*,scalar_t__,int) ; 
 int READ_USHORT (int*) ; 
 int TCP_FIN ; 
 int TCP_RST ; 
 int TCP_SYN ; 
 TYPE_6__* ZeroMallocFast (int) ; 

PKT *ParsePacketEx4(UCHAR *buf, UINT size, bool no_l3, UINT vlan_type_id, bool bridge_id_as_mac_address, bool no_http, bool correct_checksum)
{
	PKT *p;
	USHORT vlan_type_id_16;
	// Validate arguments
	if (buf == NULL || size == 0)
	{
		return NULL;
	}

	if (vlan_type_id == 0)
	{
		vlan_type_id = MAC_PROTO_TAGVLAN;
	}

	vlan_type_id_16 = Endian16((USHORT)vlan_type_id);

	p = ZeroMallocFast(sizeof(PKT));

	p->VlanTypeID = vlan_type_id;

	// If there is garbage after the payload in IPv4 and IPv6 packets, eliminate it
	if (size >= 24)
	{
		if (buf[12] == 0x08 && buf[13] == 0x00)
		{
			USHORT ip_total_size2 = READ_USHORT(&buf[16]);
			UINT mac_packet_size;

			if (ip_total_size2 >= 1)
			{
				mac_packet_size = (UINT)ip_total_size2 + 14;

				if (size > mac_packet_size)
				{
					size = mac_packet_size;
				}
			}
		}
		else if (buf[12] == 0x86 && buf[13] == 0xdd)
		{
			USHORT ip_payload_size_2 = READ_USHORT(&buf[18]);
			UINT mac_packet_size;

			if (ip_payload_size_2 >= 1)
			{
				mac_packet_size = (UINT)ip_payload_size_2 + 14 + 40;

				if (size > mac_packet_size)
				{
					size = mac_packet_size;
				}
			}
		}
		else if (buf[12] == ((UCHAR *)&vlan_type_id_16)[0] && buf[13] == ((UCHAR *)&vlan_type_id_16)[1])
		{
			if (buf[16] == 0x08 && buf[17] == 0x00)
			{
				USHORT ip_total_size2 = READ_USHORT(&buf[20]);
				UINT mac_packet_size;

				if (ip_total_size2 >= 1)
				{
					mac_packet_size = (UINT)ip_total_size2 + 14 + 4;

					if (size > mac_packet_size)
					{
						size = mac_packet_size;
					}
				}
			}
			else if (buf[16] == 0x86 && buf[17] == 0xdd)
			{
				USHORT ip_payload_size_2 = READ_USHORT(&buf[22]);
				UINT mac_packet_size;

				if (ip_payload_size_2 >= 1)
				{
					mac_packet_size = (UINT)ip_payload_size_2 + 14 + 40 + 4;

					if (size > mac_packet_size)
					{
						size = mac_packet_size;
					}
				}
			}
		}
	}

	// Do parse
	if (ParsePacketL2Ex(p, buf, size, no_l3) == false)
	{
		// Parsing failure
		FreePacket(p);
		return NULL;
	}

	p->PacketData = buf;
	p->PacketSize = size;

	p->MacAddressSrc = p->MacHeader->SrcAddress;
	p->MacAddressDest = p->MacHeader->DestAddress;

	if (bridge_id_as_mac_address)
	{
		if (p->TypeL3 == L3_BPDU)
		{
			if (p->L3.BpduHeader != NULL)
			{
				p->MacAddressSrc = p->L3.BpduHeader->BridgeMacAddress;
			}
		}
	}

	if (no_http == false)
	{
		USHORT port_raw = Endian16(80);
		USHORT port_raw2 = Endian16(8080);
		USHORT port_raw3 = Endian16(443);
		USHORT port_raw4 = Endian16(3128);

		// Analyze if the packet is a part of HTTP
		if ((p->TypeL3 == L3_IPV4 || p->TypeL3 == L3_IPV6) && p->TypeL4 == L4_TCP)
		{
			TCP_HEADER *tcp = p->L4.TCPHeader;
			if (tcp != NULL && (tcp->DstPort == port_raw || tcp->DstPort == port_raw2 || tcp->DstPort == port_raw4) &&
				(!((tcp->Flag & TCP_SYN) || (tcp->Flag & TCP_RST) || (tcp->Flag & TCP_FIN))))
			{
				if (p->PayloadSize >= 1)
				{
					p->HttpLog = ParseHttpAccessLog(p);
				}
			}
			if (tcp != NULL && tcp->DstPort == port_raw3 &&
				(!((tcp->Flag & TCP_SYN) || (tcp->Flag & TCP_RST) || (tcp->Flag & TCP_FIN))))
			{
				if (p->PayloadSize >= 1)
				{
					p->HttpLog = ParseHttpsAccessLog(p);
				}
			}
		}
	}

	if (p->TypeL3 == L3_IPV4 && p->TypeL4 == L4_UDP && p->TypeL7 == L7_DHCPV4)
	{
		// Get the DHCP opcode
		DHCPV4_DATA *d = ParseDHCPv4Data(p);

		if (d != NULL)
		{
			p->DhcpOpCode = d->OpCode;

			FreeDHCPv4Data(d);
		}
	}

	if (correct_checksum)
	{
		// Correct the checksum of the UDP, IP and TCP
		CorrectChecksum(p);
	}

	// Parsing success
	return p;
}