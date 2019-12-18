#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  MacAddress; } ;
struct TYPE_10__ {int BroadcastPacket; scalar_t__ TypeL3; int /*<<< orphan*/  PacketData; int /*<<< orphan*/  MacAddressDest; int /*<<< orphan*/  MacAddressSrc; } ;
typedef  TYPE_1__ PKT ;
typedef  TYPE_2__ L3IF ;

/* Variables and functions */
 scalar_t__ Cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreePacket (TYPE_1__*) ; 
 int /*<<< orphan*/  L3RecvArp (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  L3RecvIp (TYPE_2__*,TYPE_1__*,int) ; 
 scalar_t__ L3_ARPV4 ; 
 scalar_t__ L3_IPV4 ; 

void L3RecvL2(L3IF *f, PKT *p)
{
	// Validate arguments
	if (f == NULL || p == NULL)
	{
		return;
	}

	// Ignore any packets except a unicast packet which is at destination
	// or a packet which I sent
	if (Cmp(p->MacAddressSrc, f->MacAddress, 6) == 0 ||
		(p->BroadcastPacket == false && Cmp(p->MacAddressDest, f->MacAddress, 6) != 0))
	{
		// Release the packet
		Free(p->PacketData);
		FreePacket(p);
		return;
	}

	if (p->TypeL3 == L3_ARPV4)
	{
		// Received an ARP packet
		L3RecvArp(f, p);

		// Release the packet
		Free(p->PacketData);
		FreePacket(p);
	}
	else if (p->TypeL3 == L3_IPV4)
	{
		// Received an IP packet
		L3RecvIp(f, p, false);
	}
	else
	{
		// Release the packet
		Free(p->PacketData);
		FreePacket(p);
	}
}