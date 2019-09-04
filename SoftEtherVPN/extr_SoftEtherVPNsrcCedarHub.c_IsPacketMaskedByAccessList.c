#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_15__ ;
typedef  struct TYPE_24__   TYPE_14__ ;
typedef  struct TYPE_23__   TYPE_13__ ;
typedef  struct TYPE_22__   TYPE_12__ ;
typedef  struct TYPE_21__   TYPE_11__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ UINT64 ;
typedef  int UINT ;
struct TYPE_32__ {int /*<<< orphan*/  DstPort; int /*<<< orphan*/  SrcPort; } ;
typedef  TYPE_7__ UDP_HEADER ;
struct TYPE_34__ {int NormalClient; TYPE_14__* Hub; TYPE_1__* PacketAdapter; } ;
struct TYPE_33__ {int Flag; int /*<<< orphan*/  DstPort; int /*<<< orphan*/  SrcPort; } ;
struct TYPE_31__ {TYPE_8__* TCPHeader; TYPE_7__* UDPHeader; } ;
struct TYPE_30__ {scalar_t__ Protocol; } ;
struct TYPE_29__ {int AccessListIncludeFileCacheLifetime; scalar_t__ ApplyIPv4AccessListOnArpPacket; } ;
struct TYPE_28__ {TYPE_2__* ARPv4Header; TYPE_11__* IPv6Header; TYPE_12__* IPv4Header; } ;
struct TYPE_27__ {int HardwareSize; int ProtocolSize; int SrcIP; int TargetIP; int /*<<< orphan*/  ProtocolType; int /*<<< orphan*/  HardwareType; } ;
struct TYPE_26__ {scalar_t__ Param; } ;
struct TYPE_25__ {int Active; int CheckSrcMac; int* SrcMacAddress; int* SrcMacMask; int CheckDstMac; int* DstMacAddress; int* DstMacMask; scalar_t__ SrcUsernameHash; int IsSrcUsernameIncludeOrExclude; scalar_t__ DestUsernameHash; int IsDestUsernameIncludeOrExclude; int IsIPv6; int SrcIpAddress; int SrcSubnetMask; int DestIpAddress; int DestSubnetMask; scalar_t__ Protocol; scalar_t__ SrcPortStart; scalar_t__ DestPortStart; scalar_t__ SrcPortEnd; scalar_t__ DestPortEnd; int CheckTcpState; int Established; int /*<<< orphan*/  DestSubnetMask6; int /*<<< orphan*/  DestIpAddress6; int /*<<< orphan*/  SrcSubnetMask6; int /*<<< orphan*/  SrcIpAddress6; int /*<<< orphan*/  DestUsername; int /*<<< orphan*/  SrcUsername; } ;
struct TYPE_24__ {TYPE_4__* Option; int /*<<< orphan*/ * UserList; } ;
struct TYPE_23__ {scalar_t__ UsernameHash; scalar_t__ UsernameHashSimple; scalar_t__ GroupnameHash; } ;
struct TYPE_22__ {int SrcIP; int DstIP; scalar_t__ Protocol; } ;
struct TYPE_21__ {int /*<<< orphan*/  DestAddress; int /*<<< orphan*/  SrcAddress; } ;
struct TYPE_20__ {int* MacAddressSrc; int* MacAddressDest; scalar_t__ TypeL3; scalar_t__ TypeL4; TYPE_6__ L4; TYPE_5__ IPv6HeaderPacketInfo; TYPE_3__ L3; } ;
typedef  TYPE_8__ TCP_HEADER ;
typedef  TYPE_9__ SESSION ;
typedef  TYPE_10__ PKT ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_11__ IPV6_HEADER ;
typedef  TYPE_12__ IPV4_HEADER ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_13__ HUB_PA ;
typedef  TYPE_14__ HUB ;
typedef  TYPE_15__ ACCESS ;

/* Variables and functions */
 int ARP_HARDWARE_TYPE_ETHERNET ; 
 scalar_t__ CmpIpAddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int Endian16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPAnd6 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPv6AddrToIP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IsHubIpAddress32 (int) ; 
 scalar_t__ IsHubMacAddress (int*) ; 
 int IsUserMatchInUserListWithCacheExpiresAcl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int IsZeroIP6Addr (int /*<<< orphan*/ *) ; 
 scalar_t__ L3_ARPV4 ; 
 scalar_t__ L3_IPV4 ; 
 scalar_t__ L3_IPV6 ; 
 scalar_t__ L4_TCP ; 
 scalar_t__ L4_UDP ; 
 int MAKEBOOL (int) ; 
 int TCP_ACK ; 
 int TCP_SYN ; 

bool IsPacketMaskedByAccessList(SESSION *s, PKT *p, ACCESS *a, UINT64 dest_username, UINT64 dest_groupname, SESSION *dest_session)
{
	UINT64 src_username;
	UINT64 src_username_simple;
	UINT64 src_groupname;
	HUB_PA *pa;
	IPV4_HEADER *ip = NULL;
	IPV6_HEADER *ip6 = NULL;
	bool is_ipv4_packet = false;
	bool is_ipv6_packet = false;
	bool is_arp_packet = false;
	// Validate arguments
	if (s == NULL || p == NULL || a == NULL)
	{
		return false;
	}
	if (a->Active == false)
	{
		// Access list is inactive
		return false;
	}

	pa = (HUB_PA *)s->PacketAdapter->Param;

	// Hash of the source user name
	src_username = pa->UsernameHash;
	src_username_simple = pa->UsernameHashSimple;
	src_groupname = pa->GroupnameHash;

	// Determine the source and destination MAC address
	if (a->CheckSrcMac != false)
	{
		UINT i;
		for (i = 0; i < 6; i++)
		{
			if((a->SrcMacAddress[i] & a->SrcMacMask[i]) != (a->SrcMacMask[i] & p->MacAddressSrc[i]))
			{
				return false;
			}
		}
	}

	if (a->CheckDstMac != false)
	{
		UINT i;
		for (i = 0; i < 6; i++)
		{
			if ((a->DstMacAddress[i] & a->DstMacMask[i]) != (a->DstMacMask[i] & p->MacAddressDest[i]))
			{
				return false;
			}
		}
	}

	// Check the source user name / group name
	if (a->SrcUsernameHash != 0)
	{
		if (a->IsSrcUsernameIncludeOrExclude == false)
		{
			// It is specified as a regular user name
			if ((a->SrcUsernameHash != src_username) && (a->SrcUsernameHash != src_groupname))
			{
				return false;
			}
		}
		else
		{
			// It is specified in the form of a exclude:FILENAME or include:FILENAME
			HUB *hub = s->Hub;

			if (hub != NULL)
			{
				LIST *o = hub->UserList;

				if (s->NormalClient == false)
				{
					// The internal session don't become target for format exclude: or include:
					return false;
				}

				if (IsUserMatchInUserListWithCacheExpiresAcl(o, a->SrcUsername, src_username,
					hub->Option->AccessListIncludeFileCacheLifetime * 1000) == false)
				{
					return false;
				}
			}
		}
	}

	// Check the destination user name / group name
	if (a->DestUsernameHash != 0)
	{
		if (a->IsDestUsernameIncludeOrExclude == false)
		{
			// It is specified as a regular user name
			if ((a->DestUsernameHash != dest_username) && (a->DestUsernameHash != dest_groupname))
			{
				return false;
			}
		}
		else
		{
			// It is specified in the form of a exclude:FILENAME or include:FILENAME
			HUB *hub = s->Hub;

			if (hub != NULL)
			{
				LIST *o = hub->UserList;

				if (dest_session != NULL && dest_session->NormalClient == false)
				{
					// The internal session don't become target for format exclude: or include:
					return false;
				}

				if (IsUserMatchInUserListWithCacheExpiresAcl(o, a->DestUsername, dest_username,
					hub->Option->AccessListIncludeFileCacheLifetime * 1000) == false)
				{
					return false;
				}
			}
		}
	}

	// Determine of the IP packet
	if (p->TypeL3 != L3_IPV4)
	{
		is_ipv4_packet = false;
	}
	else
	{
		is_ipv4_packet = true;
	}

	if (p->TypeL3 != L3_IPV6)
	{
		is_ipv6_packet = false;
	}
	else
	{
		is_ipv6_packet = true;
	}

	if (p->TypeL3 == L3_ARPV4)
	{
		is_arp_packet = true;
	}

	if (is_ipv4_packet)
	{
		ip = p->L3.IPv4Header;
	}

	if (is_ipv6_packet)
	{
		ip6 = p->L3.IPv6Header;
	}

	if (a->IsIPv6 == false)
	{
		// IPv4

		// Check the source IP address
		if (a->SrcIpAddress != 0 || a->SrcSubnetMask != 0)
		{
			if (is_ipv4_packet == false)
			{
				if (p->TypeL3 == L3_ARPV4)
				{
					bool arp_match = false;
					if (p->L3.ARPv4Header->HardwareSize == 6 &&
						Endian16(p->L3.ARPv4Header->HardwareType) == ARP_HARDWARE_TYPE_ETHERNET &&
						p->L3.ARPv4Header->ProtocolSize == 4 &&
						Endian16(p->L3.ARPv4Header->ProtocolType) == 0x0800)
					{
						UINT uint_ip = p->L3.ARPv4Header->SrcIP;

						if (uint_ip != 0 && uint_ip != 0xffffffff && !(IsHubIpAddress32(uint_ip) && IsHubMacAddress(p->MacAddressSrc)))
						{
							if ((uint_ip & a->SrcSubnetMask) != (a->SrcIpAddress & a->SrcSubnetMask))
							{
							}
							else
							{
								arp_match = true;
							}
						}
					}

					if (arp_match == false)
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			else
			{
				if ((ip->SrcIP & a->SrcSubnetMask) != (a->SrcIpAddress & a->SrcSubnetMask))
				{
					return false;
				}
			}
		}

		// Check the destination IP address
		if (a->DestIpAddress != 0 || a->DestSubnetMask != 0)
		{
			if (is_ipv4_packet == false)
			{
				if (p->TypeL3 == L3_ARPV4)
				{
					bool arp_match = false;
					if (p->L3.ARPv4Header->HardwareSize == 6 &&
						Endian16(p->L3.ARPv4Header->HardwareType) == ARP_HARDWARE_TYPE_ETHERNET &&
						p->L3.ARPv4Header->ProtocolSize == 4 &&
						Endian16(p->L3.ARPv4Header->ProtocolType) == 0x0800)
					{
						UINT uint_ip = p->L3.ARPv4Header->TargetIP;

						if (uint_ip != 0 && uint_ip != 0xffffffff && !(IsHubIpAddress32(uint_ip) && IsHubMacAddress(p->MacAddressSrc)))
						{
							if ((uint_ip & a->DestSubnetMask) != (a->DestIpAddress & a->DestSubnetMask))
							{
							}
							else
							{
								arp_match = true;
							}
						}
					}

					if (arp_match == false)
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			else
			{
				if ((ip->DstIP & a->DestSubnetMask) != (a->DestIpAddress & a->DestSubnetMask))
				{
					return false;
				}
			}
		}
	}
	else
	{
		// IPv6

		// Check the source IP address
		if (IsZeroIP6Addr(&a->SrcIpAddress6) == false ||
			IsZeroIP6Addr(&a->SrcSubnetMask6) == false)
		{
			if (is_ipv6_packet == false)
			{
				return false;
			}
			else
			{
				IP a_ip, a_subnet, p_ip;
				IP and1, and2;

				IPv6AddrToIP(&a_ip, &a->SrcIpAddress6);
				IPv6AddrToIP(&a_subnet, &a->SrcSubnetMask6);
				IPv6AddrToIP(&p_ip, &ip6->SrcAddress);

				IPAnd6(&and1, &a_ip, &a_subnet);
				IPAnd6(&and2, &p_ip, &a_subnet);

				if (CmpIpAddr(&and1, &and2) != 0)
				{
					return false;
				}
			}
		}

		// Check the destination IP address
		if (IsZeroIP6Addr(&a->DestIpAddress6) == false ||
			IsZeroIP6Addr(&a->DestSubnetMask6) == false)
		{
			if (is_ipv6_packet == false)
			{
				return false;
			}
			else
			{
				IP a_ip, a_subnet, p_ip;
				IP and1, and2;

				IPv6AddrToIP(&a_ip, &a->DestIpAddress6);
				IPv6AddrToIP(&a_subnet, &a->DestSubnetMask6);
				IPv6AddrToIP(&p_ip, &ip6->DestAddress);

				IPAnd6(&and1, &a_ip, &a_subnet);
				IPAnd6(&and2, &p_ip, &a_subnet);

				if (CmpIpAddr(&and1, &and2) != 0)
				{
					return false;
				}
			}
		}
	}

	// Don't match the packet of non-IPv4 and non-IPv6
	if (is_arp_packet)
	{
		if (s->Hub != NULL && s->Hub->Option != NULL && s->Hub->Option->ApplyIPv4AccessListOnArpPacket)
		{
			// Match the ARP only if ApplyIPv4AccessListOnArpPacket option is enabled
		}
		else
		{
			return false;
		}
	}

	// Check the protocol number
	if (a->Protocol != 0)
	{
		if (a->IsIPv6 == false)
		{
			if (is_ipv4_packet == false)
			{
				return false;
			}
			else
			{
				if (ip->Protocol != a->Protocol)
				{
					return false;
				}
			}
		}
		else
		{
			if (is_ipv6_packet == false)
			{
				return false;
			}
			else
			{
				if (p->IPv6HeaderPacketInfo.Protocol != a->Protocol)
				{
					return false;
				}
			}
		}
	}

	// Check the port number
	if (a->SrcPortStart != 0 || a->DestPortStart != 0 ||
		a->SrcPortEnd != 0 || a->DestPortEnd != 0)
	{
		if ((a->IsIPv6 == false && is_ipv4_packet == false) ||
			(a->IsIPv6 && is_ipv6_packet == false))
		{
			return false;
		}
		else
		{
			if (p->TypeL4 == L4_TCP)
			{
				TCP_HEADER *tcp = p->L4.TCPHeader;
				// Check the source port
				if (a->SrcPortStart != 0 || a->SrcPortEnd != 0)
				{
					UINT src_port = Endian16(tcp->SrcPort);
					if (src_port < a->SrcPortStart || src_port > a->SrcPortEnd)
					{
						return false;
					}
				}

				// Check the destination port number
				if (a->DestPortStart != 0 || a->DestPortEnd != 0)
				{
					UINT dest_port = Endian16(tcp->DstPort);
					if (dest_port < a->DestPortStart || dest_port > a->DestPortEnd)
					{
						return false;
					}
				}
			}
			else if (p->TypeL4 == L4_UDP)
			{
				UDP_HEADER *udp = p->L4.UDPHeader;
				// Check the source port
				if (a->SrcPortStart != 0 || a->SrcPortEnd != 0)
				{
					UINT src_port = Endian16(udp->SrcPort);
					if (src_port < a->SrcPortStart || src_port > a->SrcPortEnd)
					{
						return false;
					}
				}

				// Check the destination port number
				if (a->DestPortStart != 0 || a->DestPortEnd != 0)
				{
					UINT dest_port = Endian16(udp->DstPort);
					if (dest_port < a->DestPortStart || dest_port > a->DestPortEnd)
					{
						return false;
					}
				}
			}
			else
			{
				// When the port number is specified in the access list,
				// The rule is applied only for UDP or TCP packets
				return false;
			}
		}
	}

	// Check the status of the TCP connection
	if (a->CheckTcpState != false)
	{
		if ((a->IsIPv6 == false && is_ipv4_packet == false) ||
			(a->IsIPv6 && is_ipv6_packet == false))
		{
			return false;
		}
		else
		{
			if(p->TypeL4 == L4_TCP)
			{
				// by shimizu
				TCP_HEADER *tcp = p->L4.TCPHeader;
				bool est = true;

				if ((tcp->Flag & TCP_SYN) && (!(tcp->Flag & TCP_ACK)))
				{
					est = false;
				}

				if((MAKEBOOL(a->Established) ^ MAKEBOOL(est)))
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
	}

	return true;
}