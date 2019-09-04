#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int USHORT ;
typedef  int UINT ;
struct TYPE_11__ {int /*<<< orphan*/  DstPort; int /*<<< orphan*/  SrcPort; } ;
typedef  TYPE_3__ UDP_HEADER ;
typedef  int UCHAR ;
struct TYPE_13__ {scalar_t__ InitiatorCookie; scalar_t__ ResponderCookie; scalar_t__ ExchangeType; } ;
struct TYPE_10__ {TYPE_5__* IkeHeader; } ;
struct TYPE_9__ {TYPE_3__* UDPHeader; } ;
struct TYPE_12__ {int* Payload; int PayloadSize; scalar_t__ TypeL3; int /*<<< orphan*/  TypeL7; TYPE_2__ L7; TYPE_1__ L4; int /*<<< orphan*/  TypeL4; } ;
typedef  TYPE_4__ PKT ;
typedef  TYPE_5__ IKE_HEADER ;

/* Variables and functions */
 int Endian16 (int /*<<< orphan*/ ) ; 
 scalar_t__ IKE_EXCHANGE_TYPE_AGGRESSIVE ; 
 scalar_t__ IKE_EXCHANGE_TYPE_MAIN ; 
 int IsZero (int*,int) ; 
 scalar_t__ L3_IPV4 ; 
 int /*<<< orphan*/  L4_UDP ; 
 int /*<<< orphan*/  L7_IKECONN ; 
 int /*<<< orphan*/  L7_OPENVPNCONN ; 
 int /*<<< orphan*/  ParseDHCPv4 (TYPE_4__*,int*,int) ; 
 int /*<<< orphan*/  ParseDNS (TYPE_4__*,int*,int) ; 

bool ParseUDP(PKT *p, UCHAR *buf, UINT size)
{
	USHORT src_port, dst_port;
	// Validate arguments
	if (p == NULL || buf == NULL)
	{
		return false;
	}

	// Check the size
	if (size < sizeof(UDP_HEADER))
	{
		// Size is invalid
		return false;
	}

	// UDP header
	p->L4.UDPHeader = (UDP_HEADER *)buf;
	p->TypeL4 = L4_UDP;

	buf += sizeof(UDP_HEADER);
	size -= sizeof(UDP_HEADER);

	p->Payload = buf;
	p->PayloadSize = size;

	// Check the port number
	src_port = Endian16(p->L4.UDPHeader->SrcPort);
	dst_port = Endian16(p->L4.UDPHeader->DstPort);

	if ((src_port == 67 && dst_port == 68) ||
		(src_port == 68 && dst_port == 67))
	{
		if (p->TypeL3 == L3_IPV4)
		{
			// A DHCP packet is found
			ParseDHCPv4(p, buf, size);

			return true;
		}
	}
  
 	if (dst_port == 53)
	{
 		ParseDNS(p, buf, size);
 		return true;
 	}
 

	if (src_port == 500 || dst_port == 500 || src_port == 4500 || dst_port == 4500)
	{
		if (p->PayloadSize >= sizeof(IKE_HEADER))
		{
			IKE_HEADER *ike_header = (IKE_HEADER *)p->Payload;

			if (ike_header->InitiatorCookie != 0 && ike_header->ResponderCookie == 0 &&
				(ike_header->ExchangeType == IKE_EXCHANGE_TYPE_MAIN ||
				ike_header->ExchangeType == IKE_EXCHANGE_TYPE_AGGRESSIVE))
			{
				// the IKE connection request packet is found
				p->TypeL7 = L7_IKECONN;
				p->L7.IkeHeader = ike_header;
				return true;
			}
		}
	}

	// Determine whether it's an OpenVPN UDP packet
	if (size == 14)
	{
		if (buf[0] == 0x38)
		{
			if (IsZero(buf + 9, 5))
			{
				if (IsZero(buf + 1, 8) == false)
				{
					// An OpenVPN connection request packet is found
					p->TypeL7 = L7_OPENVPNCONN;
					return true;
				}
			}
		}
	}

	return true;
}