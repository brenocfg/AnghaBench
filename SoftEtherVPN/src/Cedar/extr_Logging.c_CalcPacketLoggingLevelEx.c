#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_10__ {int /*<<< orphan*/ * PacketLogConfig; } ;
struct TYPE_8__ {TYPE_1__* TCPHeader; } ;
struct TYPE_9__ {int TypeL3; int /*<<< orphan*/ * HttpLog; int /*<<< orphan*/  TypeL7; TYPE_2__ L4; int /*<<< orphan*/  TypeL4; } ;
struct TYPE_7__ {int Flag; } ;
typedef  TYPE_3__ PKT ;
typedef  TYPE_4__ HUB_LOG ;

/* Variables and functions */
#define  L3_ARPV4 138 
#define  L3_IPV4 137 
#define  L3_IPV6 136 
#define  L4_ICMPV4 135 
#define  L4_ICMPV6 134 
#define  L4_TCP 133 
#define  L4_UDP 132 
#define  L7_DHCPV4 131 
#define  L7_DNS 130 
#define  L7_IKECONN 129 
#define  L7_OPENVPNCONN 128 
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t PACKET_LOG_ARP ; 
 size_t PACKET_LOG_DHCP ; 
 size_t PACKET_LOG_ETHERNET ; 
 size_t PACKET_LOG_ICMP ; 
 size_t PACKET_LOG_IP ; 
 int /*<<< orphan*/  PACKET_LOG_NONE ; 
 size_t PACKET_LOG_TCP ; 
 size_t PACKET_LOG_TCP_CONN ; 
 size_t PACKET_LOG_UDP ; 
 int TCP_FIN ; 
 int TCP_RST ; 
 int TCP_SYN ; 

UINT CalcPacketLoggingLevelEx(HUB_LOG *g, PKT *packet)
{
	UINT ret = 0;
	// Validate arguments
	if (g == NULL || packet == NULL)
	{
		return PACKET_LOG_NONE;
	}

	// Ethernet log
	ret = MAX(ret, g->PacketLogConfig[PACKET_LOG_ETHERNET]);

	switch (packet->TypeL3)
	{
	case L3_ARPV4:
		// ARP
		ret = MAX(ret, g->PacketLogConfig[PACKET_LOG_ARP]);
		break;

	case L3_IPV4:
		// IPv4
		ret = MAX(ret, g->PacketLogConfig[PACKET_LOG_IP]);

		switch (packet->TypeL4)
		{
		case L4_ICMPV4:
			// ICMPv4
			ret = MAX(ret, g->PacketLogConfig[PACKET_LOG_ICMP]);
			break;

		case L4_TCP:
			// TCPv4
			ret = MAX(ret, g->PacketLogConfig[PACKET_LOG_TCP]);

			if (packet->L4.TCPHeader->Flag & TCP_SYN ||
				packet->L4.TCPHeader->Flag & TCP_RST ||
				packet->L4.TCPHeader->Flag & TCP_FIN)
			{
				// TCP SYN LOG
				ret = MAX(ret, g->PacketLogConfig[PACKET_LOG_TCP_CONN]);
			}

			break;

		case L4_UDP:
			// UDPv4
			ret = MAX(ret, g->PacketLogConfig[PACKET_LOG_UDP]);

			switch (packet->TypeL7)
			{
			case L7_DHCPV4:
				// DHCPv4
				ret = MAX(ret, g->PacketLogConfig[PACKET_LOG_DHCP]);
				break;

			case L7_IKECONN:
				// IKE connection request
				ret = MAX(ret, g->PacketLogConfig[PACKET_LOG_TCP_CONN]);
				break;

			case L7_OPENVPNCONN:
				// OpenVPN connection request
				ret = MAX(ret, g->PacketLogConfig[PACKET_LOG_TCP_CONN]);
				break;

 			case L7_DNS:
 				// DNS request
 				ret = MAX(ret, g->PacketLogConfig[PACKET_LOG_TCP_CONN]);
 				break;
			}

			break;
		}

		break;

	case L3_IPV6:
		// IPv6
		ret = MAX(ret, g->PacketLogConfig[PACKET_LOG_IP]);

		switch (packet->TypeL4)
		{
		case L4_ICMPV6:
			// ICMPv6
			ret = MAX(ret, g->PacketLogConfig[PACKET_LOG_ICMP]);
			break;

		case L4_TCP:
			// TCPv6
			ret = MAX(ret, g->PacketLogConfig[PACKET_LOG_TCP]);

			if (packet->L4.TCPHeader->Flag & TCP_SYN ||
				packet->L4.TCPHeader->Flag & TCP_RST ||
				packet->L4.TCPHeader->Flag & TCP_FIN)
			{
				// TCP SYN LOG
				ret = MAX(ret, g->PacketLogConfig[PACKET_LOG_TCP_CONN]);
			}

			break;

		case L4_UDP:
			// UDPv6
			ret = MAX(ret, g->PacketLogConfig[PACKET_LOG_UDP]);

			switch (packet->TypeL7)
			{
			case L7_IKECONN:
				// IKE connection request
				ret = MAX(ret, g->PacketLogConfig[PACKET_LOG_TCP_CONN]);
				break;

			case L7_OPENVPNCONN:
				// OpenVPN connection request
				ret = MAX(ret, g->PacketLogConfig[PACKET_LOG_TCP_CONN]);
				break;

 			case L7_DNS:
 				// DNS request
 				ret = MAX(ret, g->PacketLogConfig[PACKET_LOG_TCP_CONN]);
 				break;
			}

			break;
		}

		break;
	}

	if (packet->HttpLog != NULL)
	{
		// HTTP Connect Log
		ret = MAX(ret, g->PacketLogConfig[PACKET_LOG_TCP_CONN]);
	}

	return ret;
}