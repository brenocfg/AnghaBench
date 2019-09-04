#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * IPv4Header; } ;
struct TYPE_8__ {int TypeL4; int /*<<< orphan*/  TypeL3; TYPE_1__ L3; } ;
typedef  TYPE_2__ PKT ;

/* Variables and functions */
 int /*<<< orphan*/  FreePacketICMPv4 (TYPE_2__*) ; 
 int /*<<< orphan*/  FreePacketTCPv4 (TYPE_2__*) ; 
 int /*<<< orphan*/  FreePacketUDPv4 (TYPE_2__*) ; 
 int /*<<< orphan*/  L3_UNKNOWN ; 
#define  L4_ICMPV4 130 
#define  L4_TCP 129 
#define  L4_UDP 128 

void FreePacketIPv4(PKT *p)
{
	// Validate arguments
	if (p == NULL)
	{
		return;
	}

	switch (p->TypeL4)
	{
	case L4_ICMPV4:
		FreePacketICMPv4(p);
		break;

	case L4_TCP:
		FreePacketTCPv4(p);
		break;

	case L4_UDP:
		FreePacketUDPv4(p);
		break;
	}

	p->L3.IPv4Header = NULL;
	p->TypeL3 = L3_UNKNOWN;
}