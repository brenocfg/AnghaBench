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
struct TYPE_12__ {int /*<<< orphan*/  SrcIP; int /*<<< orphan*/  SrcAddress; int /*<<< orphan*/  TargetIP; } ;
struct TYPE_11__ {int /*<<< orphan*/  IpAddress; } ;
struct TYPE_9__ {TYPE_4__* ARPv4Header; } ;
struct TYPE_10__ {TYPE_1__ L3; } ;
typedef  TYPE_2__ PKT ;
typedef  TYPE_3__ L3IF ;
typedef  TYPE_4__ ARPV4_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  L3KnownArp (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L3SendArpResponseNow (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void L3RecvArpRequest(L3IF *f, PKT *p)
{
	ARPV4_HEADER *a;
	// Validate arguments
	if (f == NULL || p == NULL)
	{
		return;
	}

	a = p->L3.ARPv4Header;

	L3KnownArp(f, a->SrcIP, a->SrcAddress);

	if (a->TargetIP == f->IpAddress)
	{
		// Respond only if the ARP packet addressed to myself
		L3SendArpResponseNow(f, a->SrcAddress, a->SrcIP, f->IpAddress);
	}
}