#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ HostIP; } ;
typedef  TYPE_2__ VH ;
struct TYPE_12__ {scalar_t__ TargetIP; int /*<<< orphan*/  SrcIP; int /*<<< orphan*/  SrcAddress; } ;
struct TYPE_9__ {TYPE_4__* ARPv4Header; } ;
struct TYPE_11__ {TYPE_1__ L3; } ;
typedef  TYPE_3__ PKT ;
typedef  TYPE_4__ ARPV4_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  ArpIpWasKnown (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VirtualArpSendResponse (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

void VirtualArpResponseRequest(VH *v, PKT *packet)
{
	ARPV4_HEADER *arp;
	// Validate arguments
	if (v == NULL || packet == NULL)
	{
		return;
	}

	arp = packet->L3.ARPv4Header;

	// Memory the information of the host IP address and the MAC address of the other party
	ArpIpWasKnown(v, arp->SrcIP, arp->SrcAddress);

	// Search whether it matches with the IP address of this host
	if (v->HostIP == arp->TargetIP)
	{
		// Respond since the match
		VirtualArpSendResponse(v, arp->SrcAddress, arp->SrcIP, v->HostIP);
		return;
	}
	// Do nothing if it doesn't match
}