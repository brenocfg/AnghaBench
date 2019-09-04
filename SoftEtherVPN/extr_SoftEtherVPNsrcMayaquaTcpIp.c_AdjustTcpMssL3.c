#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int USHORT ;
typedef  int UINT ;
typedef  int UCHAR ;
struct TYPE_15__ {scalar_t__ Protocol; int TotalLength; int /*<<< orphan*/  DstIP; int /*<<< orphan*/  SrcIP; } ;
struct TYPE_14__ {int /*<<< orphan*/  DestAddress; int /*<<< orphan*/  SrcAddress; } ;
struct TYPE_13__ {scalar_t__ Protocol; int PayloadSize; scalar_t__ Payload; int /*<<< orphan*/ * FragmentHeader; scalar_t__ IsFragment; TYPE_3__* IPv6Header; } ;
struct TYPE_12__ {int Flag; scalar_t__ Checksum; } ;
typedef  TYPE_1__ TCP_HEADER ;
typedef  TYPE_2__ IPV6_HEADER_PACKET_INFO ;
typedef  TYPE_3__ IPV6_HEADER ;
typedef  TYPE_4__ IPV4_HEADER ;

/* Variables and functions */
 scalar_t__ CalcChecksumForIPv4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ CalcChecksumForIPv6 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int IPV4_GET_FLAGS (TYPE_4__*) ; 
 int IPV4_GET_HEADER_LEN (TYPE_4__*) ; 
 scalar_t__ IPV4_GET_OFFSET (TYPE_4__*) ; 
 int IPV6_FRAGMENT_HEADER_FLAG_MORE_FRAGMENTS ; 
 int IPV6_GET_FLAGS (int /*<<< orphan*/ *) ; 
 scalar_t__ IP_PROTO_TCP ; 
 int MAX (int,int) ; 
 int ParsePacketIPv6Header (TYPE_2__*,int*,int) ; 
 int READ_USHORT (int*) ; 
 int TCP_GET_HEADER_SIZE (TYPE_1__*) ; 
 int TCP_PSH ; 
 int TCP_RST ; 
 int TCP_SYN ; 
 int TCP_URG ; 
 int /*<<< orphan*/  WRITE_USHORT (int*,int) ; 

bool AdjustTcpMssL3(UCHAR *src, UINT src_size, UINT mss)
{
	UCHAR ip_ver;
	TCP_HEADER *tcp = NULL;
	UINT tcp_size = 0;
	UINT tcp_header_size;
	UCHAR *options;
	UINT options_size;
	IPV4_HEADER *ip = NULL;
	IPV6_HEADER *ip6 = NULL;
	// Validate arguments
	if (src == NULL || src_size == 0 || mss == 0)
	{
		return false;
	}

	// Get the IP version number
	ip_ver = (src[0] >> 4) & 0x0f;

	if (ip_ver == 4)
	{
		UINT ip_header_size;
		UINT ip_total_length;
		// IPv4
		if (src_size < sizeof(IPV4_HEADER))
		{
			// No IPv4 header
			return false;
		}

		ip = (IPV4_HEADER *)src;

		if (ip->Protocol != IP_PROTO_TCP)
		{
			// Non-TCP
			return false;
		}

		if (IPV4_GET_OFFSET(ip) != 0)
		{
			// It is the second or later packet of fragmented packet
			return false;
		}

		if (IPV4_GET_FLAGS(ip) & 0x01)
		{
			// Fragmented packet
			return false;
		}

		ip_header_size = IPV4_GET_HEADER_LEN(ip) * 4;
		if (ip_header_size < sizeof(IPV4_HEADER))
		{
			// Header size is invalid
			return false;
		}

		if (src_size < ip_header_size)
		{
			// No IPv4 header
			return false;
		}

		ip_total_length = READ_USHORT(&ip->TotalLength);

		if (ip_total_length < ip_header_size)
		{
			// Invalid total length
			return false;
		}

		if (src_size < ip_total_length)
		{
			// No total length
			return false;
		}

		src += ip_header_size;
		src_size = ip_total_length - ip_header_size;

		if (src_size < sizeof(TCP_HEADER))
		{
			// No TCP header
			return false;
		}

		tcp = (TCP_HEADER *)src;
		tcp_size = src_size;
	}
	else if (ip_ver == 6)
	{
		// IPv6
		IPV6_HEADER_PACKET_INFO v6;

		if (ParsePacketIPv6Header(&v6, src, src_size) == false)
		{
			// IPv6 analysis failure
			return false;
		}

		ip6 = v6.IPv6Header;
		if (ip6 == NULL)
		{
			return false;
		}

		if (v6.Protocol != IP_PROTO_TCP)
		{
			// Non-TCP
			return false;
		}

		if (v6.IsFragment)
		{
			// It is the second or later packet of fragmented packet
			return false;
		}

		if (v6.FragmentHeader != NULL)
		{
			if (IPV6_GET_FLAGS(v6.FragmentHeader) & IPV6_FRAGMENT_HEADER_FLAG_MORE_FRAGMENTS)
			{
				// Fragmented packet
				return false;
			}
		}

		tcp = (TCP_HEADER *)v6.Payload;
		tcp_size = v6.PayloadSize;
	}
	else
	{
		// This isn't either IPv4, IPv6
		return false;
	}

	// Processing of the TCP header
	if (tcp == NULL || tcp_size < sizeof(TCP_HEADER))
	{
		return false;
	}

	tcp_header_size = TCP_GET_HEADER_SIZE(tcp) * 4;
	if (tcp_header_size < sizeof(TCP_HEADER))
	{
		// TCP header size is invalid
		return false;
	}

	if (tcp_size < tcp_header_size)
	{
		// Packet length shortage
		return false;
	}

	if (((tcp->Flag & TCP_SYN) == false) ||
		((tcp->Flag & TCP_RST) ||
		(tcp->Flag & TCP_PSH) ||
		(tcp->Flag & TCP_URG)))
	{
		// Not a SYN packet
		return false;
	}

	// Get the option field
	options = ((UCHAR *)tcp) + sizeof(TCP_HEADER);
	options_size = tcp_header_size - sizeof(TCP_HEADER);

	if (ip6 != NULL)
	{
		// Reduce MSS by 20 since an IP header for IPv6 is 20 bytes larger than IPv4
		if (mss >= 20)
		{
			mss -= 20;
		}
	}

	// MSS should be at least 64
	mss = MAX(mss, 64);

	if (options_size >= 4 && options[0] == 0x02 && options[1] == 0x04)
	{
		// MSS option of TCP is added
		USHORT current_mss = READ_USHORT(((UCHAR *)options) + 2);

		if (current_mss <= mss)
		{
			// if the value of the MSS is smaller than the specified size
			// from the beginning, it doesn't need to be rewritten
			return false;
		}
		else
		{
			WRITE_USHORT(((UCHAR *)options) + 2, mss);

			// Clear the checksum
			tcp->Checksum = 0;

			if (ip != NULL)
			{
				// Calculate the TCPv4 checksum
				tcp->Checksum = CalcChecksumForIPv4(ip->SrcIP, ip->DstIP, IP_PROTO_TCP, tcp, tcp_size, 0);
			}
			else
			{
				// Calculate the TCPv6 checksum
				tcp->Checksum = CalcChecksumForIPv6(&ip6->SrcAddress, &ip6->DestAddress,
					IP_PROTO_TCP, tcp, tcp_size, 0);
			}

			return true;
		}
	}
	else
	{
		// MSS option of TCP is not added
		return false;
	}
}