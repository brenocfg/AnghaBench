#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_10__ {int Protocol; scalar_t__ IsFragment; int /*<<< orphan*/  PayloadSize; int /*<<< orphan*/ * Payload; int /*<<< orphan*/  IPv6Header; } ;
struct TYPE_8__ {int /*<<< orphan*/  IPv6Header; } ;
struct TYPE_9__ {TYPE_5__ IPv6HeaderPacketInfo; int /*<<< orphan*/  TypeL4; TYPE_1__ L3; int /*<<< orphan*/  TypeL3; } ;
typedef  TYPE_2__ PKT ;

/* Variables and functions */
#define  IP_PROTO_ICMPV6 130 
#define  IP_PROTO_TCP 129 
#define  IP_PROTO_UDP 128 
 int /*<<< orphan*/  L3_IPV6 ; 
 int /*<<< orphan*/  L4_FRAGMENT ; 
 int ParseICMPv6 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ParsePacketIPv6Header (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ParseTCP (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ParseUDP (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool ParsePacketIPv6(PKT *p, UCHAR *buf, UINT size)
{
	// Validate arguments
	if (p == NULL || buf == NULL)
	{
		return false;
	}

	if (ParsePacketIPv6Header(&p->IPv6HeaderPacketInfo, buf, size) == false)
	{
		return false;
	}

	p->TypeL3 = L3_IPV6;
	p->L3.IPv6Header = p->IPv6HeaderPacketInfo.IPv6Header;

	if (p->IPv6HeaderPacketInfo.Payload == NULL)
	{
		// No payload
		return true;
	}

	buf = p->IPv6HeaderPacketInfo.Payload;
	size = p->IPv6HeaderPacketInfo.PayloadSize;

	if (p->IPv6HeaderPacketInfo.IsFragment)
	{
		// This is a fragmented packet. Quit interpreting
		p->TypeL4 = L4_FRAGMENT;
		return true;
	}

	// Parse a L4 packet
	switch (p->IPv6HeaderPacketInfo.Protocol)
	{
	case IP_PROTO_ICMPV6:	// ICMPv6
		if (ParseICMPv6(p, buf, size) == false)
		{
			// Returns true also if it fails to parse ICMPv6
			return true;
		}
		else
		{
			return true;
		}

	case IP_PROTO_TCP:		// TCP
		return ParseTCP(p, buf, size);

	case IP_PROTO_UDP:		// UDP
		return ParseUDP(p, buf, size);

	default:				// Unknown
		return true;
	}

	return true;
}