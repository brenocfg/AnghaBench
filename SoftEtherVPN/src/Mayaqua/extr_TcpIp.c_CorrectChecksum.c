#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ USHORT ;
struct TYPE_18__ {scalar_t__ Checksum; int /*<<< orphan*/  PacketLength; } ;
typedef  TYPE_3__ UDP_HEADER ;
struct TYPE_22__ {int Checksum; int /*<<< orphan*/  DstIP; int /*<<< orphan*/  SrcIP; } ;
struct TYPE_21__ {int /*<<< orphan*/  DestAddress; int /*<<< orphan*/  SrcAddress; } ;
struct TYPE_20__ {int IsFragment; scalar_t__ PayloadSize; int /*<<< orphan*/ * FragmentHeader; } ;
struct TYPE_17__ {TYPE_3__* UDPHeader; TYPE_3__* TCPHeader; } ;
struct TYPE_16__ {TYPE_7__* IPv6Header; TYPE_8__* IPv4Header; } ;
struct TYPE_19__ {scalar_t__ TypeL3; scalar_t__ TypeL4; scalar_t__ IPv4PayloadSize; TYPE_2__ L4; TYPE_6__ IPv6HeaderPacketInfo; TYPE_1__ L3; } ;
typedef  TYPE_3__ TCP_HEADER ;
typedef  TYPE_5__ PKT ;
typedef  TYPE_6__ IPV6_HEADER_PACKET_INFO ;
typedef  TYPE_7__ IPV6_HEADER ;
typedef  TYPE_8__ IPV4_HEADER ;

/* Variables and functions */
 void* CalcChecksumForIPv4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,scalar_t__,scalar_t__) ; 
 void* CalcChecksumForIPv6 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,scalar_t__,scalar_t__) ; 
 scalar_t__ Endian16 (int /*<<< orphan*/ ) ; 
 int IPV4_GET_FLAGS (TYPE_8__*) ; 
 int IPV4_GET_HEADER_LEN (TYPE_8__*) ; 
 scalar_t__ IPV4_GET_OFFSET (TYPE_8__*) ; 
 int IPV6_FRAGMENT_HEADER_FLAG_MORE_FRAGMENTS ; 
 int IPV6_GET_FLAGS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IP_PROTO_TCP ; 
 int /*<<< orphan*/  IP_PROTO_UDP ; 
 int IpChecksum (TYPE_8__*,int) ; 
 scalar_t__ L3_IPV4 ; 
 scalar_t__ L3_IPV6 ; 
 scalar_t__ L4_TCP ; 
 scalar_t__ L4_UDP ; 

void CorrectChecksum(PKT *p)
{
	// Validate arguments
	if (p == NULL)
	{
		return;
	}

	if (p->TypeL3 == L3_IPV4)
	{
		IPV4_HEADER *v4 = p->L3.IPv4Header;

		if (v4 != NULL)
		{
			if (v4->Checksum == 0x0000)
			{
				v4->Checksum = IpChecksum(v4, IPV4_GET_HEADER_LEN(v4) * 4);
			}

			if (p->TypeL4 == L4_TCP)
			{
				// Recalculate the TCP checksum
				if (IPV4_GET_OFFSET(v4) == 0 && (IPV4_GET_FLAGS(v4) & 0x01) == 0)
				{
					// TCP checksuming doesn't target fragmented IP packets
					TCP_HEADER *tcp = p->L4.TCPHeader;

					if (tcp != NULL)
					{
						USHORT tcp_offloading_checksum1 = CalcChecksumForIPv4(v4->SrcIP, v4->DstIP, IP_PROTO_TCP, NULL, 0, p->IPv4PayloadSize);
						USHORT tcp_offloading_checksum2 = ~tcp_offloading_checksum1;

						if (tcp->Checksum == 0 || tcp->Checksum == tcp_offloading_checksum1 || tcp->Checksum == tcp_offloading_checksum2)
						{
							tcp->Checksum = 0;
							tcp->Checksum = CalcChecksumForIPv4(v4->SrcIP, v4->DstIP, IP_PROTO_TCP, tcp, p->IPv4PayloadSize, 0);
						}
					}
				}
			}

			if (p->TypeL4 == L4_UDP)
			{
				// Recalculation of the UDP checksum
				if (IPV4_GET_OFFSET(v4) == 0 || (IPV4_GET_FLAGS(v4) & 0x01) == 0)
				{
					// If it is not divided, or it is divided but it is the first fragment of the UDP packet
					UDP_HEADER *udp = p->L4.UDPHeader;

					if (udp != NULL && udp->Checksum != 0)
					{
						USHORT udp_len = Endian16(udp->PacketLength);
						USHORT udp_offloading_checksum1 = CalcChecksumForIPv4(v4->SrcIP, v4->DstIP, IP_PROTO_UDP, NULL, 0, udp_len);
						USHORT udp_offloading_checksum2 = ~udp_offloading_checksum1;

						if (udp->Checksum == udp_offloading_checksum1 || udp->Checksum == udp_offloading_checksum2)
						{
							udp->Checksum = 0;

							if ((IPV4_GET_FLAGS(v4) & 0x01) == 0 && (p->IPv4PayloadSize >= udp_len))
							{
								// Calculate the checksum correctly based on the data in case of a non-fragmented packet
								udp->Checksum = CalcChecksumForIPv4(v4->SrcIP, v4->DstIP, IP_PROTO_UDP, udp, udp_len, 0);
							}
							else
							{
								// In case of the first fragment of the packet, set the checksum to 0
								// because there isn't entire data of the packet
								udp->Checksum = 0;
							}
						}
					}
				}
			}
		}
	}
	else if (p->TypeL3 == L3_IPV6)
	{
		IPV6_HEADER *v6 = p->L3.IPv6Header;
		IPV6_HEADER_PACKET_INFO *v6info = &p->IPv6HeaderPacketInfo;

		if (v6 != NULL)
		{
			if (p->TypeL4 == L4_TCP)
			{
				// Recalculate the TCP checksum
				if (v6info->IsFragment == false)
				{
					if (v6info->FragmentHeader == NULL || ((IPV6_GET_FLAGS(v6info->FragmentHeader) & IPV6_FRAGMENT_HEADER_FLAG_MORE_FRAGMENTS) == 0))
					{
						// TCP checksuming doesn't target fragmented packets
						TCP_HEADER *tcp = p->L4.TCPHeader;

						if (tcp != NULL)
						{
							USHORT tcp_offloading_checksum1 = CalcChecksumForIPv6(&v6->SrcAddress, &v6->DestAddress, IP_PROTO_TCP, NULL, 0, v6info->PayloadSize);
							USHORT tcp_offloading_checksum2 = ~tcp_offloading_checksum1;

							if (tcp->Checksum == 0 || tcp->Checksum == tcp_offloading_checksum1 || tcp->Checksum == tcp_offloading_checksum2)
							{
								tcp->Checksum = 0;
								tcp->Checksum = CalcChecksumForIPv6(&v6->SrcAddress, &v6->DestAddress, IP_PROTO_TCP, tcp, v6info->PayloadSize, 0);
							}
						}
					}
				}
			}
			else if (p->TypeL4 == L4_UDP)
			{
				// Recalculation of the UDP checksum
				if (v6info->IsFragment == false)
				{
					UDP_HEADER *udp = p->L4.UDPHeader;

					if (udp != NULL && udp->Checksum != 0)
					{
						USHORT udp_len = Endian16(udp->PacketLength);
						USHORT udp_offloading_checksum1 = CalcChecksumForIPv6(&v6->SrcAddress, &v6->DestAddress, IP_PROTO_UDP, NULL, 0, udp_len);
						USHORT udp_offloading_checksum2 = ~udp_offloading_checksum1;

						if (udp->Checksum == 0 || udp->Checksum == udp_offloading_checksum1 || udp->Checksum == udp_offloading_checksum2)
						{
							udp->Checksum = 0;

							if ((v6info->FragmentHeader == NULL || ((IPV6_GET_FLAGS(v6info->FragmentHeader) & IPV6_FRAGMENT_HEADER_FLAG_MORE_FRAGMENTS) == 0)) && (v6info->PayloadSize >= udp_len))
							{
								// If the packet is not fragmented, recalculate the checksum
								udp->Checksum = CalcChecksumForIPv6(&v6->SrcAddress, &v6->DestAddress, IP_PROTO_UDP, udp, udp_len, 0);
							}
							else
							{
								// Don't do (can't do) anything in the case of fragmented packet
							}
						}
					}
				}
			}
		}
	}
}