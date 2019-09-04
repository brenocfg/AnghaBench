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
typedef  int /*<<< orphan*/  VH ;
struct TYPE_7__ {int /*<<< orphan*/  SrcAddress; int /*<<< orphan*/  SrcIP; } ;
struct TYPE_5__ {TYPE_3__* ARPv4Header; } ;
struct TYPE_6__ {TYPE_1__ L3; } ;
typedef  TYPE_2__ PKT ;
typedef  TYPE_3__ ARPV4_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  ArpIpWasKnown (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void VirtualArpResponseReceived(VH *v, PKT *packet)
{
	ARPV4_HEADER *arp;
	// Validate arguments
	if (v == NULL || packet == NULL)
	{
		return;
	}

	arp = packet->L3.ARPv4Header;

	// Regard this information as known information
	ArpIpWasKnown(v, arp->SrcIP, arp->SrcAddress);
}