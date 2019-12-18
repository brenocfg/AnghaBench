#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  MacAddress; } ;
typedef  TYPE_1__ VH ;
struct TYPE_6__ {int /*<<< orphan*/  MacAddressDest; int /*<<< orphan*/  MacAddressSrc; scalar_t__ BroadcastPacket; } ;
typedef  TYPE_2__ PKT ;

/* Variables and functions */
 scalar_t__ Cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

bool VirtualLayer2Filter(VH *v, PKT *packet)
{
	// Validate arguments
	if (v == NULL || packet == NULL)
	{
		return false;
	}

	// Pass through if broadcast packet
	if (packet->BroadcastPacket)
	{
		return true;
	}

	// Ignore if the sender of the packet is myself
	if (Cmp(packet->MacAddressSrc, v->MacAddress, 6) == 0)
	{
		return false;
	}
	// Pass through in the case of a packet addressed to me
	if (Cmp(packet->MacAddressDest, v->MacAddress, 6) == 0)
	{
		return true;
	}

	// Discard if the other packets
	return false;
}