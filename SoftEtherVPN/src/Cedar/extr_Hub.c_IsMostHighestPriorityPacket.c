#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* TCPHeader; } ;
struct TYPE_7__ {scalar_t__ TypeL3; scalar_t__ TypeL4; scalar_t__ TypeL7; TYPE_2__ L4; } ;
struct TYPE_5__ {int Flag; } ;
typedef  int /*<<< orphan*/  SESSION ;
typedef  TYPE_3__ PKT ;

/* Variables and functions */
 scalar_t__ L3_ARPV4 ; 
 scalar_t__ L3_IPV4 ; 
 scalar_t__ L4_ICMPV4 ; 
 scalar_t__ L4_TCP ; 
 scalar_t__ L4_UDP ; 
 scalar_t__ L7_DHCPV4 ; 
 int TCP_FIN ; 
 int TCP_RST ; 
 int TCP_SYN ; 

bool IsMostHighestPriorityPacket(SESSION *s, PKT *p)
{
	// Validate arguments
	if (s == NULL || p == NULL)
	{
		return false;
	}

	if (p->TypeL3 == L3_ARPV4)
	{
		// ARP packets
		return true;
	}

	if (p->TypeL3 == L3_IPV4)
	{
		if (p->TypeL4 == L4_ICMPV4)
		{
			// ICMP packets
			return true;
		}

		if (p->TypeL4 == L4_TCP)
		{
			if ((p->L4.TCPHeader->Flag & TCP_SYN) || (p->L4.TCPHeader->Flag & TCP_FIN)
				|| (p->L4.TCPHeader->Flag & TCP_RST))
			{
				// SYN, FIN, RST packet
				return true;
			}
		}

		if (p->TypeL4 == L4_UDP)
		{
			if (p->TypeL7 == L7_DHCPV4)
			{
				// DHCP packets
				return true;
			}
		}
	}

	return false;
}